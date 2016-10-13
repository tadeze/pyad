import os
import sys
sys.path.insert(0,os.path.abspath('..'))
from pyiForest import IsolationForest,IsolationTree
from unittest import main, TestCase
import numpy as np
import pandas as pd
from src.RotationForest import RotationForest


class TestRotationForest(TestCase):
    def setUp(self):
        filename = 'synth2d.dt'
        pd_data = pd.read_csv(filename, header=0)
        # Forest configuration initialization
        self.np_data = pd_data.as_matrix()
        self.ntree, self.nsample, self.maxheight = 10, 10, 0
        self.rotate = self.adaptive = self.rangecheck = False
        self.rho, self.stoplimit = 0.1, 5

        self.rf = RotationForest(_ntree=self.ntree, _nsample=self.nsample, _maxheight=self.maxheight)
        # self.w = np.arange(30).reshape(10,3)

        self.rf.train_forest(self.np_data)  #

    def test_train_forest(self):
        self.fail()

    def test_depth_forest(self):
        avg_depth = self.rf.average_depth(self.np_data)
        self.assertEqual(len(avg_depth), self.np_data.shape[0])

    def test_average_depth(self):
        pass

    def test_score_forest(self):
        self.assertEqual(len(self.rf.score_forest(self.np_data)), self.np_data.shape[0])
if __name__ == '__main__':

