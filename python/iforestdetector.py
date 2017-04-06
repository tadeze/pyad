
from sensordx.adi.absad import AbstractAnomalyDetector
import pyiForest as pf

class PyForest(AbstractAnomalyDetector):
    """Wrapper for the Isolation forest code
    """


    iff = None

    def __init__(self):
        """Initialize iForest configuration
        """
        self.iff = pf.IsolationForest()

    def train(self, train_data, n_tree=100, sample_size=100 ,max_height=0, adaptive=False,
              rotate=False, range_check=True, rho=0.01, stop_limit=False):
        """
        Train forest
        :param train_data:
        :param n_tree:
        :param sample_size:
        :param max_height:
        :param adaptive:
        :param rotate:
        :param range_check:
        :param rho:
        :param stop_limit:
        :return:
        """
        #train_data = train_data.as_matrix()
        if train_data is None:
            return

        self.iff.train(train_df=train_data, ntree=n_tree, nsample=sample_size, maxheight=max_height,
                       adaptive=adaptive, rotate=rotate, rangecheck=range_check,
                       rho=rho)


    def score(self, test_data):
        if test_data is None:
            return
        return self.iff.score(test_data)
        #return self.get_score()
    def save_model(self, model_name):
        self.iff.save(model_name)


    def load_model(self, model_name):
        self.iff.load(model_name)


    def test(self, test_data):
        """

        :param test_data: test data
        :return:
        """
        #test_data = test_data.as_matrix()
        self.iff.test_forest(test_data)

    def get_score(self):
        return self.iff.anomaly_score()

    def get_depth(self):
        return self.iff.average_depth()


import sklearn.metrics as mt

if __name__ == '__main__':
    import pandas as pd
    import timeit
    import os
   #  df = pd.read_csv('test/synth2d.dt')
   #  train_data = df.ix[:,0:].as_matrix()
   #  lbl = df.ix[:,0]#.aslist()
   #  fx = pf.IsolationForest(ntree=100,nsample=100)
   #  fx.train(train_data)
   #  sc = fx.score(train_data)
   # # print "auc score, {0:f}\n".format(mt.roc_auc_score(lbl, sc))
   #  print sc


    


    dd = "/media/tadeze/kofo/Research/Dataset/benchmark/shuttle/"
    ##dd = "/nfs/guille/bugid/adams/meta_analysis/benchmarks/shuttle/"


    listfiles = os.listdir(dd)[0:10]
    print len(listfiles)
    start = timeit.default_timer()
    for ff in listfiles:

        data = pd.read_csv(os.path.join(dd,ff))#'test/synthetic_hard_100.csv')
        #print data.ix[:,0]
        train_data = data.ix[:,6:15]
        #print train_data.columns
        train_data = train_data.as_matrix()
        #lbl = data.ix[:,0]#.aslist()
        lbl = (data['ground.truth'] == "anomaly").tolist()
        #print lbl
        #ff = PyForest()
        fx = pf.IForest(ntree=100,nsample=1024)
        fx.train(train_data)
        sc = fx.score(train_data)
        #print sc
        # if sc[0]==nan:
        #     continue
        #print sc[0]
        print "auc score, {0:s} - {1:f}\n".format(ff,mt.roc_auc_score(lbl,sc))
    fx.save('iforest.hf')
    print (timeit.default_timer()-start)
    #ff.save_model("syth2d.json")
    #print(ff.get_score())
    #print(ff.iff.get_nsample())

#     print ff.iff.getNSample()
