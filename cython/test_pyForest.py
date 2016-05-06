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
      self.np_data = pd_data.as_matrix()
      self.ff.trainForest(self.np_data,10,10,0,False,False,False,0.01,1)
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

if __name__ == "__main__":
    main()

