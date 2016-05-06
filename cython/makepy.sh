rm *.so
python setup.py build_ext --inplace
python ./test_pyForest.py 
