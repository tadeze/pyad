import pyad as pft
from pyiForest import IsolationTree
import pandas as pd
import sklearn.metrics as mt
import numpy as np

class RotationForest(object):
    """
    Build Rotation Forest based on Isolation Trees
    """

    def __init__(self, traindf=None, ntree=100, nsample=512,
                 maxheight=0, adaptive=False, rangecheck=True, sparsity=False):
        self.nsample = nsample
        self.ntree = ntree
        self.rangecheck = rangecheck
        self.adaptive = adaptive
        self.maxheight = maxheight
        self.sparsity = sparsity
        self.sample_rotation = []
        self.rot_trees = []

    @staticmethod
    def random_rotation_matrix(n, m=None):
        if m is None:
            m = n
        A = np.random.normal(size=[n, m])
        Q, R = np.linalg.qr(A)
        M = Q.dot(np.diag(np.sign(np.diag(R))))
        if np.linalg.det(M) < 0:
            M[:, 0] = -M[:, 0]
        return M

    def train(self, traindf):
        """ Train forest"""
        assert isinstance(traindf, np.ndarray)
        nrow, ncol = traindf.shape
        r = ncol
        if self.sparsity and ncol > 3:
            r = int(np.ceil((2 + np.sqrt(ncol) / 2)))
        for tree in xrange(self.ntree):
            self.sample_rotation = np.random.choice(ncol, r, False)
            rotMat = RotationForest.random_rotation_matrix(ncol)
            rotated_data = np.dot(traindf, rotMat)
            if self.nsample > nrow:
                self.nsample = nrow
            sample_index = np.random.choice(nrow, self.nsample, False)
            itree = IsolationTree()
            if len(self.sample_rotation) > 0:
                rotated_data = rotated_data[:, self.sample_rotation]

            itree.iTree(sample_index, rotated_data, 0, self.maxheight)
            self.rot_trees.append(
                {"rotmat": rotMat, "tree": itree, "dim": self.sample_rotation})
        return self.ntree

    def depth(self, testdf):
        depth = []

        for rottree in self.rot_trees:
            rot_mat = rottree["rotmat"]
            tree = rottree["tree"]
            dim = np.sort(rottree["dim"])
            # print dim
            # rotate data
            # print testdf.shape, rot_mat.shape
            rotated_dt = np.dot(testdf, rot_mat)

            depth.append(tree.path_length(rotated_dt[dim]))
        return depth

    def average_depth(self, testdf):
        assert isinstance(testdf, np.ndarray)
        # if len(self.sample_rotation)>0:
        #   testdf = testdf[:,self.sample_rotation]
        avg_depth = [np.mean(self.depth(row)) for row in testdf]
        return np.array(avg_depth)

    def score(self, testdf):
        # score of allpoints
        def bst(n): return 0.0 if (n - 1) <= 0 else (2.0 *
                                                     np.log(n - 1) + 0.5772156649) - 2.0 * (n - 1) / n
        avg_depth = self.average_depth(testdf)
        scores = np.power(2, (-1 * avg_depth / bst(self.nsample)))
        return scores

    #@staticmethod
    def save(self, model_name):
        # First save trees and rotation matrix.
        cPickle.dump(self, open(model_name, 'w'))

    def load(self, model_name):
        return cPickle.load(open(model_name, "r"))


def metric(label, score):
    auc = mt.roc_auc_score(label, score)
    ap = mt.average_precision_score(label, score)
    return [auc, ap]

dataset = '~/projects/'
dt = pd.read_csv('synthetic_hard_100.csv')

train_df = dt.ix[:, 1:].as_matrix()
print train_df.shape
ff = pft.IsolationForest()
ff.train(traindf=train_df, ntree=100, nsample=256)
# ff.load('firstmodel.if
sc = ff.score(train_df)
# print sc[1:10]
# ff.save("firstmodel.if")
# print ff.get_ntree()
print metric(dt.ix[:, 0].as_matrix(), sc)

# Scoring using rotation forest
rf = RotationForest(sparsity=True, ntree=100, nsample=256)
rf.train(traindf=train_df)
scr = rf.score(train_df)
print metric(dt.ix[:, 0].as_matrix(), scr)

# TODO: The rotation forest with random dimension reduction, in similar to the LODA approach.
# It works well for hight dimensional dataset and limit the number of trees.
