import os
import sys
sys.path.insert(0,os.path.abspath('..'))
from pyiForest import IsolationForest
from unittest import main, TestCase
import numpy as np
import pandas as pd
class TestPyForest(TestCase):

  def setUp(self):
      self.ff =  IsolationForest()
      #self.w = np.arange(30).reshape(10,3)

      #set for dataset
      filename ='synth2d.dt'
      pd_data = pd.read_csv(filename,header=0)

      #Forest configuration initialization
      self.np_data = pd_data.as_matrix()
      self.ntree,self.nsample,self.maxheight =10,10,0
      self.rotate=self.adaptive=self.rangecheck=False
      self.rho,self.stoplimit =0.1,5

      self.ff.train_forest(self.np_data,self.ntree,self.nsample,
              self.maxheight,self.rotate,self.adaptive,self.rangecheck,
              self.rho,self.stoplimit)
      self.ff.test_forest(self.np_data)

  def test_pyForest_avgDepth(self):
      avg_depth = self.ff.average_depth()
      self.assertEqual(len(avg_depth),self.np_data.shape[0])
  def test_pyForest_score(self):
      self.assertEqual(len(self.ff.anomaly_score()),self.np_data.shape[0])
  def test_pyForest_getNTree(self):
      self.assertEqual(self.ff.get_ntree(),self.ntree)

  def test_pyForest_getNSample(self):
      self.assertEqual(self.ff.get_nsample(),self.nsample)
  def test_pyForest_getMaxDepth(self):
      self.assertEqual(self.ff.get_max_depth(),self.maxheight)
  def test_pyForest_isAdaptive(self):
      self.assertFalse(self.ff.is_adaptive())

  def test_pyForest_isRangCheck(self):
      self.assertTrue(self.rangecheck==self.ff.is_range_check())
  def test_pyForest_isRotate(self):
      self.assertTrue(self.rotate==self.ff.is_rotate())






if __name__ == "__main__":
    main()

