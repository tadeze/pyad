import numpy as np
import sklearn.metrics as mt
import pyada


# data
N, D = 400, 5
w = np.random.randn(N, D)
w_score = w.copy()

# Train anomaly detectors
loda = pyada.Loda()
loda.train(w)
iforest = pyada.IsolationForest()
iforest.train(w)

# Add anomalies
w_score[:3, 2:5] = np.random.randn(3, 3) * 5
w_score[3:6, 1:3] = np.random.randn(3, 2) * -5
label = np.zeros(N)
label[:6] = 1.0  # label as anomalies
# score
loda_score = loda.score(w_score)
iforest_score = iforest.score(w_score)

# Metrics
print(
    "AUC(loda): {}, AUC(iForest): {}".format(
        mt.roc_auc_score(label, loda_score), mt.roc_auc_score(label, iforest_score)
    )
)
