import pyad as pft
import numpy as np

dt = np.loadtxt('synthetic5d34.csv',skiprows=1,delimiter=',')
ff = pft.IsolationForest(dt,ntree=10000,nsample=100)
sc = ff.score(dt)
print sc[2]

print ff.explanation(dt[2,:])
print dt[2,:]
print ("Check model save")
ff.save("iforest.if")
xf = pft.IsolationForest()
xf.load("iforest.if")
print xf.score(dt)[2],sc[2]

