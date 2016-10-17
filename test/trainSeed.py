import numpy as np
#import random
import pandas as pd
import argparse
import sklearn.metrics as metric
def performance(label,score):
    #precision and recall

    ap = metric.average_precision_score(label,score)
    auc_score = metric.roc_auc_score(label,score)
    return ap,auc_score
def testForest(traindata,testdata,forest_name):
   # np.random.seed(99)
    #random.seed(999)
    from pyiForest import IsolationForest
    ff = IsolationForest()
    ff.trainForest(traindata,10,traindata.shape[0])
    ff.testForest(testdata)
    ff.save(forest_name+".json")
    sc = ff.getScore()
    pd.DataFrame.to_csv(pd.DataFrame(sc,columns=["score"]),forest_name+".sc",index=False)
    del ff
    return sc


if __name__ == '__main__':
    parser =  argparse.ArgumentParser(description="Type training type")
    parser.add_argument("-t","--traintype",action="store_false",help="True for contaminated training")
    args = parser.parse_args()
    isclean = args.traintype

    df = pd.read_csv('results/synthetic_hard_100.csv')
    dt_unclean = df.ix[:,1:].as_matrix()
    class_label = df["class"]
   # assert(dt_clean.shape[0]!=dt_unclean.shape[0])
   # assert(dt_clean.shape[1]==dt_unclean.shape[1])
    #print("Unclea finished")
    #Unclean data
    #isclean=False
    if isclean:
        dfclean = pd.read_csv('results/clean_synthetic_hard_100.csv')
        dt_clean = dfclean.ix[:,1:].as_matrix()
        scr = testForest(dt_clean,dt_unclean,"results/clean")
        print("Clean finished AP and AUC ")
        print performance(class_label,np.array(scr))
    else:
        scr=testForest(dt_unclean,dt_unclean,"results/contaminated")
        print ("Contaminated,, AP and AUC ")
        print performance(class_label,np.array(scr))
