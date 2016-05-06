from pyForest import PyForest
from unittest import main, TestCase
import numpy as np
import pandas as pd
class TestPyForest(TestCase):

  def setUp(self):
      self.ff =  PyForest()
      #self.w = np.arange(30).reshape(10,3)

      #set for dataset
      filename ='../synth2d.csv'
      pd_data = pd.read_csv(filename,header=0)

      #Forest configuration initialization
      self.np_data = pd_data.as_matrix()
      self.ntree,self.nsample,self.maxheight =10,10,0
      self.rotate=self.adaptive=self.rangecheck=False
      self.rho,self.stoplimit =0.1,5
      self.ff.trainForest(self.np_data,self.ntree,self.nsample,
              self.maxheight,self.adaptive,self.rotate,self.rangecheck,
              self.rho,self.stoplimit)
      self.ff.testForest(self.np_data)

  def test_factorial(self):
      self.assertEqual(self.ff.factorial(6),6*120)
  def test_factorial_again(self):
      self.assertGreater(self.ff.factorial(2),0)
  def test_pyForest_avgDepth(self):
      avg_depth = self.ff.averageDepth()
      self.assertEqual(len(avg_depth),self.np_data.shape[0])
  def test_pyForest_score(self):
      self.assertEqual(len(self.ff.getScore()),self.np_data.shape[0])
  def test_pyForest_getNTree(self):
      self.assertEqual(self.ff.getNTree(),self.ntree)

  def test_pyForest_getNSample(self):
      self.assertEqual(self.ff.getNSample(),self.nsample)
  def test_pyForest_getMaxDepth(self):
      self.assertEqual(self.ff.getMaxDepth(),self.maxheight)
  def test_pyForest_isAdaptive(self):
      self.assertTrue(self.adaptive==self.ff.isAdaptive())
  def test_pyForest_isRangCheck(self):
      self.assertTrue(self.rangecheck==self.ff.isRangeCheck())
  def test_pyForest_isRotate(self):
      self.assertTrue(self.rotate==self.ff.isRotate())







if __name__ == "__main__":
    main()

