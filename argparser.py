import argparse
import numpy as np
import pandas as pd
import itertools
from pyiForest import IsolationForest
def iForest(ntree,nsample,train_data,test_data,max_height=0,stop_height=0):
      iff = IsolationForest()
      iff.trainForest(train_data,ntree,nsample,max_height)
      iff.testForest(test_data)
      return iff




def main():

    parser = argparse.ArgumentParser(description="iForest usage switches")
    parser.add_argument('-t','--ntree',type=int,help="Required for number of trees",required = True)
    parser.add_argument('-i','--input',type=argparse.FileType('r'),help="Required input file",required = True)
    parser.add_argument('-o','--output',type=argparse.FileType('w'),help="Required output file",required=True)
    parser.add_argument('-x','--testfile',type=argparse.FileType('r'),help="Required for testing file (optional)")
    parser.add_argument('-s','--nsample',type=int,default=512, help="Number of samples defualt 512")
    parser.add_argument('-r','--rotate', action='store_true',help='Rotate data if checked rotates')
    parser.add_argument('-m','--skipcolumn',help="Skip columns")
    parser.add_argument('-g','--gtcolumn',help='ground truth column',type=int)
    parser.add_argument('-c','--column',help='Column to include defualt use all column')
    parser.add_argument('-m','--model',help='Trained saved model, (optional)')


    args = parser.parse_args()
    input_data = pd.read_csv(args.input.name,header=0)

    if args.gtcolumn is not None:
        gt = input_data.iloc[:,args.gtcolumn-1]
    if args.testfile is not None:
        test_data = pd.read_csv(args.testfile.name,header=0)
    else:
        test_data = input_data
    if args.column is not None:
        col_set = []
        columns = args.column.split(',')
        #check for range column 3-4
        for col in columns:
            range_col = map(int,col.split('-'))

            if len(range_col) == 2:
                col_set.append(range(range_col[0]-1,range_col[1]))
            elif len(range_col) == 1:
                col_set.append(range_col-1)
            else:
                raise NameError("Incorrect column switch")
        col_set = list(itertools.chain.from_iterable(col_set))
        input_data = input_data.iloc[:,col_set]
        test_data = test_data.iloc[:,col_set]


    ntree = args.ntree
    nsample = args.nsample
    input_data = input_data.as_matrix()
    test_data = test_data.as_matrix()
    print ntree
    print nsample
    print input_data.shape
    print type(test_data)
    iff = iForest(ntree=ntree,train_data=input_data,test_data=test_data,nsample=nsample)
    sc = iff.getScore()
    if args.gtcolumn is not None:
        out_pd = pd.concat([pd.DataFrame(gt),pd.DataFrame(sc,columns=['score'])],axis=1)
    else:
        out_pd = pd.DataFrame(sc)
    out_pd.to_csv(args.output.name,delimiter=",",index=False)
    # import the pyiForest
    print iff.getNSample(),iff.getNTree()

if __name__ == '__main__':
    main()
