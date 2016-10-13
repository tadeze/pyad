"""
Rotate dataset before applying isolation forest
"""
import numpy as np
import pyiForest as pf
#from _pyForest import FacadeForest
def random_rotation_matrix(n):
    A = np.random.normal(size=[n,n])
    Q,R = np.linalg.qr(A)
    M = Q.dot(np.diag(np.sign(np.diag(R))))
    if np.linalg.det(M)<0:
        M[:,0] = -M[:,0]
    return M

class RotationForest(object):
    """
    Build Rotation Forest based on Isolation Trees
    """
    rot_trees=[]

    def __init__(self,_traindf=None,_ntree=100,_nsample=512,_maxheight=0,_adaptive=False,_rangecheck=True):
        self.nsample= _nsample
        self.ntree= _ntree
        self.rangecheck = _rangecheck
        self.adaptive = _adaptive
        self.maxheight =_maxheight


    def train_forest(self,traindf):
        """ Train forest"""
        assert isinstance(traindf,np.ndarray)
        nrow,ncol = traindf.shape

        for tree in range(self.ntree):
            # generate rotation matrix
            rotMat = random_rotation_matrix(ncol)
            rotated_data = np.dot(traindf,rotMat)
            sample_index = np.random.choice(nrow,self.nsample,False)
            itree = pf.IsolationTree()
            itree.iTree(sample_index,rotated_data,0,self.maxheight)
            self.rot_trees.append({"rotmat":rotMat,"tree":itree})

    def depth_forest(self,_testdf):
        depth=[]

        for rottree in self.rot_trees:
            rot_mat = rottree["rotmat"]
            tree = rottree["tree"]
            #rotate data
            rotated_dt = np.dot(_testdf,rot_mat)
            depth.append(tree.path_length(rotated_dt))
        return depth

    def average_depth(self,_testdf):
        assert isinstance(_testdf, np.ndarray)
        avg_depth = [np.mean(self.depth_forest(row)) for row in _testdf]
        return np.array(avg_depth)


    def score_forest(self,_testdf):
        #score of allpoints
        bst=lambda n: 0.0 if (n-1)<=0 else (2.0*np.log(n-1) +0.5772156649) - 2.0*(n-1)/n
        avg_depth =self.average_depth(_testdf)
        scores = np.power(2, (-1*avg_depth / bst(self.nsample)))
        return scores

if __name__ == '__main__':
    import pandas as pd
    df = pd.read_csv('../test/synth2d.dt')
    rf = RotationForest(_ntree=10,_nsample=50)
    rf.train_forest(df.as_matrix())
    print rf.score_forest(df.as_matrix()).shape

    #print df.head(5)