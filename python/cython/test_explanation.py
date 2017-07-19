import pyiForest as pft
import numpy as np

dt = np.loadtxt('../../test/unittest/synth2d.dt',skiprows=1,delimiter=',')
ff = pft.IsolationForest(dt,ntree=100,nsample=100)
sc = ff.score(dt)
ff.save("sxx.json")
print ff.explanation(dt[2,:])
print sc[2]
print dt[2,:]


