"""
Rotate dataset before applying isolation forest
"""
import numpy as np

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
    def __init__(self):
        pass
    def train_forest(self,...):
        """ Train forest"""
        pass
    def test_forest(self,...):
        """"  Rotate and score   """"
        pass

