import pandas as pd
import loda
import numpy as np
import time
NA = np.nan
data_path = "synthetic100.csv"
df = pd.read_csv(data_path)
train_data = df.ix[:,1:8].as_matrix()
test_data = train_data.copy()
start = time.time()
ld = loda.Loda()
ld.train(train_x=train_data)
score = ld.score(test_data)
print (time.time() - start)



