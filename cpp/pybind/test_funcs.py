import iforest
#import cppimport
import numpy as np
#funcs = cppimport.imp("iforest")
def test_add():
    ff = iforest.FacadeForest()
    ff.displayData()

    # xs = np.random.randn(10)
    # print(xs)
    # print(iforest.square(xs))
    # ys = range(10)
    # print(iforest.square(ys))
    # ## 2-D
    # xs = np.arange(12).reshape(3,4).astype('float')
    # print(xs)
    # print("np :", xs.sum())
    # print("cpp:", iforest.sum(xs))
    #
    # print()
    # iforest.twice(xs)
    # print(xs)

if __name__ == '__main__':
    test_add()
