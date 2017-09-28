default: build 
### FILES ### 
FILES=pyadlib _pyad.cpp setup.py MANIFEST.in
pyadlib: ../src
	cp -R ../src .
_pyad.cpp: _pyad.pyx cpyad.pxd
	cython --cplus _pyad.pyx -o _pyad.cpp
####
all: ${FILES}
	python setup.py build_ext --inplace
install: ${FILES}
	python setup.py install
.PHONY: build 
build: ${FILES}
	python setup.py build_ext --inplace 
.PHONY: sdist
sdist: ${FILES}
	python setup.py sdist 
	
.PHONY: wheel
wheel: ${FILES}
	python setup.py bdist_wheel

.PHONY: build-win
build-win: ${FILES} #clean  # Build for windows 
	export DISTUTILS_USE_SDK=1
	export MSSdk=1
	python.exe setup.py build_ext --inplace --compiler=msvc
.PHONY: cython-build
cython-build: clean clean-cpp
	python setup.py build_ext --inplace --use-cython 
.PHONY: tests
tests:ls
	hash nosetests 2>/dev/null || { echo -e >&2 "############ Required nosetest package"; exit 1;}
	nosetests --logging-level=INFO tests/ 
clean-cpp:
	rm *.cpp -rf 
clean:
	rm *.so *.pyc -rf 
	rm dist build pyad.egg-info src -rf 
clean-all:
	clean clean-cpp



