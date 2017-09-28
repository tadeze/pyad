all:
	python setup.py build_ext --inplace
install:
	python setup.py install
clean-cpp:
	rm *.cpp -rf 
clean:
	rm *.so -rf 
	rm *.pyd -rf
	rm build/ -rf 
clean-all:
	clean clean-cpp
.PHONY: build 
build: clean
	python setup.py build_ext --inplace 
build-win: clean
	export DISTUTILS_USE_SDK=1
	export MSSdk=1
	python.exe setup.py build_ext --inplace --compiler=msvc
.PHONY: cython-build
cython-build: clean clean-cpp
	python setup.py build_ext --inplace --use-cython 
.PHONY: tests
tests:
	hash nosetests 2>/dev/null || { echo -e >&2 "############ Required nosetest package"; exit 1;}
	nosetests --logging-level=INFO tests/ 