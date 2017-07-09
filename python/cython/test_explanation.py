import pyiForest as pft 
import numpy as np 

dt = np.loadtxt('../../test/unittest/synthetic5d34.csv',skiprows=1,delimiter=',')
ff = pft.IForest(dt,ntree=100,nsample=100)
sc = ff.score(dt)
print ff.explanation(dt[2,:])
print sc[2]
print dt[2,:]

 
