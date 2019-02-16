#%%
import pyad as pft
import numpy as np

dt = np.random.randn(1000,3)
ff = pft.IsolationForest(dt,ntree=10,nsample=100)
d_score = dt.copy()
d_score[2,2] = d_score[2,2]*-5
sc = ff.score(dt)
print(sc[2])
print("Feature explanation")
print (ff.explanation(dt[2,:]))
print(dt[2,:])
print ("Check model save")
ff.save("iforest.if")
xf = pft.IsolationForest.load("iforest.if")
print (xf.score(dt)[2],sc[2])
