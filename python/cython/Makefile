all:
	python setup.py build_ext --inplace
install:
	python setup.py install
clean-cpp:
	rm *.cpp -rf 
clean:
	rm *.so -rf 
	rm build/ -rf 
	rm dist -rf 
	
clean-all:
	clean clean-cpp
.PHONY: build 
build: clean
	python setup.py build_ext --inplace 

.PHONY: cython-build
cython-build: clean clean-cpp
	python setup.py build_ext --inplace --use-cython 
.PHONY: tests
tests:
	hash nosetests 2>/dev/null || { echo -e >&2 "############ Required nosetest package"; exit 1;}
	nosetests --logging-level=INFO tests/ 


