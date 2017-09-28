import argparse
import numpy as np
# import pandas as

import itertools
from pyiForest import IsolationForest


def iForest(ntree, nsample, train_data, test_data, max_height=0, stop_height=0,
            rotate=False, adaptive=False, model_name=None):

    iff = IsolationForest()
    if model_name is None:
        trees = iff.train(traindf=train_data, ntree=ntree, nsample=nsample, maxheight=max_height,
                          rotate=rotate, adaptive=adaptive, rho=0.01, stoplimit=5)
    else:
        iff.load(model_name)
        trees = iff.get_ntree()
    sc = iff.score(test_data)
    print "Number of trees used: {0:d}".format(trees)
    return iff, sc


def main():
    parser = argparse.ArgumentParser(description="iForest usage switches")
    parser.add_argument('-t', '--ntree', type=int,
                        help="Required for number of trees", required=True)
    parser.add_argument('-i', '--input', type=argparse.FileType('r'),
                        help="Required input file", required=True)
    parser.add_argument('-o', '--output', type=argparse.FileType('w'),
                        help="Required output file", required=True)
    parser.add_argument('-x', '--testfile', type=argparse.FileType('r'),
                        help="Required for testing file (optional)")
    parser.add_argument('-s', '--nsample', type=int,
                        default=512, help="Number of samples defualt 512")
    parser.add_argument('-a', '--adaptive', action='store_true',
                        help='Train using adaptive forest')
    parser.add_argument('-r', '--rotate', action='store_true',
                        help='Rotate data if checked rotates')
    parser.add_argument('-p', '--pathlength',
                        action='store_true', help='Output all depths')
    parser.add_argument('-d', '--depth', action='store_true',
                        help='Output average depth')
    parser.add_argument('-j', '--skiprow',
                        help="If there is header skip skip first row.",
                        action='store_true')
    parser.add_argument('-g', '--gtcolumn',
                        help='skip column', type=int)
    parser.add_argument('-c', '--column',
                        help='Column to include defualt use all column.E.g. 1-10 or 1,3')
    parser.add_argument('-m', '--model',
                        type=argparse.FileType('w'),
                        help='Save trained model to file. Provide file name')
    parser.add_argument('-l', '--load', type=argparse.FileType('r'),
                        help='Load model from file. Required saved model name')

    args = parser.parse_args()

    # Read inputs
    # input_data = pd.read_csv(args.input.name,header=0)
    # if args.gtcolumn is not None:
    #     gt = input_data.iloc[:,args.gtcolumn-1]
    # print args.column
    col_set = None
    print args.column
    if args.column is not None:
        col_set = []
        columns = args.column.split(',')
        # check for range column 3-4

        for col in columns:
            range_col = map(int, col.split('-'))
            print range_col

            if len(range_col) == 2:
                col_set = col_set + range(range_col[0] - 1, range_col[1])
            elif len(range_col) == 1:
                col_set.append(range_col[0] - 1)
            else:
                raise NameError("Incorrect column switch")

    if args.skiprow:
        header = 1
    else:
        header = 0

    # input_data.iloc[:,col_set]
    input_data = np.loadtxt(args.input, usecols=col_set,
                            skiprows=header, delimiter=',')
    if args.testfile is not None:
        test_data = np.loadtxt(
            args.testfile.name, usecols=col_set, skiprows=header, delimiter=',')
    else:
        test_data = input_data

    test_data = input_data  # test_data.iloc[:,col_set]

    ntree = args.ntree
    nsample = args.nsample

    #input_data = input_data.as_matrix()
    #test_data = test_data.as_matrix()

    if args.load is not None:
        model_name = args.load.name
    else:
        model_name = None
    iff, sc = iForest(ntree=ntree, train_data=input_data, test_data=test_data, nsample=nsample, adaptive=args.adaptive,
                      rotate=args.rotate, model_name=model_name)

    header_output = "score"
    result = np.vstack(iff.anomaly_score())

    if args.depth:
        header_output += ",depth"
        result = np.hstack([result, np.matrix(iff.average_depth()).T])
    if args.pathlength:
        tree_prefix = lambda tr: "tree_" + str(tr)
        header_output += ',' + ','.join(map(tree_prefix, range(1, ntree + 1)))
        result = np.hstack([result, np.matrix(iff.path_length())])

    np.savetxt(args.output, result, delimiter=',',
               header=header_output, comments='')
    if args.model is not None:
        # Save the model
        print args.model.name
        iff.save(args.model.name)

    # if args.gtcolumn is not None:
    #     out_pd = pd.concat([pd.DataFrame(gt),pd.DataFrame(sc,columns=['score'])],axis=1)
    # else:
    #     out_pd = pd.DataFrame(sc)
    # out_pd.to_csv(args.output.name,index=False)

if __name__ == '__main__':
    main()
