cd cython
rm *.so
python setup.py build_ext --inplace
nosetests ./test_pyForest.py -v
cd ..
