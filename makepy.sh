python setup.py build_ext --inplace
cp *.so test/
cd test
nosetests ./test_pyForest.py -v
cd ..
