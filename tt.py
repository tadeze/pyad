import numpy as np
import cPickle
from pyiForest import IsolationTree
def random_rotation_matrix(n,m=None):
    if m is None: m=n
    A = np.random.normal(size=[n,m])
    Q,R = np.linalg.qr(A)
    M = Q.dot(np.diag(np.sign(np.diag(R))))
    if np.linalg.det(M)<0:
        M[:,0] = -M[:,0]
    return M

def metric(label,score):
    import sklearn.metrics as mt
    auc = mt.roc_auc_score(label,score)
    ap = mt.average_precision_score(label,score)
    return auc,ap

class RotationForest(object):
    """
    Build Rotation Forest based on Isolation Trees
    """
    rot_trees = []

    def __init__(self, _traindf=None, _ntree=100, _nsample=512,
                 _maxheight=0, _adaptive=False, _rangecheck=True, reduce_dim=False):
        self.nsample = _nsample
        self.ntree = _ntree
        self.rangecheck = _rangecheck
        self.adaptive = _adaptive
        self.maxheight = _maxheight
        self.reduce_dim = reduce_dim
        self.sample_rotation= []

    def train_forest(self, traindf):
        """ Train forest"""
        assert isinstance(traindf, np.ndarray)
        nrow, ncol = traindf.shape
        if self.reduce_dim and ncol > 3:
            r = np.ceil((2 + np.sqrt(ncol) / 2))
            self.sample_rotation = np.random.choice(ncol, r, False)

        for tree in range(self.ntree):
            # generate rotation matrix
            rotMat = random_rotation_matrix(ncol)
            rotated_data = np.dot(traindf, rotMat)
            sample_index = np.random.choice(nrow, self.nsample, False)
            itree = IsolationTree()
            if len(self.sample_rotation) > 0:
                rotated_data = rotated_data[:, self.sample_rotation]

            itree.iTree(sample_index, rotated_data, 0, self.maxheight)
            self.rot_trees.append({"rotmat": rotMat, "tree": itree})

    def depth_forest(self, _testdf):
        depth = []

        for rottree in self.rot_trees:
            rot_mat = rottree["rotmat"]
            tree = rottree["tree"]
            # rotate data
            rotated_dt = np.dot(_testdf, rot_mat)
            if len(self.sample_rotation) > 0:
                rotated_dt = rotated_dt[self.sample_rotation]
            depth.append(tree.path_length(rotated_dt))
        return depth

    def average_depth(self, _testdf):
        assert isinstance(_testdf, np.ndarray)

        avg_depth = [np.mean(self.depth_forest(row)) for row in _testdf]
        return np.array(avg_depth)

    def score_forest(self, _testdf):
        # score of allpoints
        bst = lambda n: 0.0 if (n - 1) <= 0 else (2.0 * np.log(n - 1) + 0.5772156649) - 2.0 * (n - 1) / n
        avg_depth = self.average_depth(_testdf)
        scores = np.power(2, (-1 * avg_depth / bst(self.nsample)))
        return scores

    # @staticmethod
    def save_model(self, model_name):
        # First save trees and rotation matrix.
        cPickle.dump(self, open(model_name, 'w'))

    def load_model(self, model_name):
        return cPickle.load(open(model_name, "r"))


if __name__ == '__main__':
    n=100
    d=10
    #traindf = np.random.randn(n,d)
    #rotMat= random_rotation_matrix(d)
    #rd = np.ceil((np.sqrt(n)))
    #print rd,traindf
    #rotated_data = np.dot(traindf, rotMat)
    #sample_index = np.random.choice(nrow, self.nsample, False)
    #print ,#np.linalg.det(xx)
    import pandas as pd
    df = pd.read_csv('/media/tadeze/kofo/Research/Dataset/benchmark/yearp/yearp_benchmark_0230.csv')
    traindf = df.ix[:,6:95].as_matrix()
    lbl =map(int,df.ix[:,5]=='anomaly')
    rf = RotationForest(traindf,_ntree=100,_nsample=256,reduce_dim=True)
    rf.train_forest(traindf)
    sc = rf.score_forest(traindf)
    print metric(lbl,sc)

    # rf = RotationForest(traindf, _ntree=10, _nsample=50, reduce_dim=False)
    # rf.train_forest(traindf)
    # sc = rf.score_forest(traindf)
    # print metric(df.ix[:, 0], sc)
