default: build 
### FILES ### 
FILES=setup.py MANIFEST.in
# pyadlib: ../src
# 	cp -R ../src .
# 	cp -R ../README.md .
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
	rm pyada/*.cpp -rf 
clean:
	rm pyada/*.so pyada/*.pyc -rf 
	rm dist build pyada.egg-info src -rf 
clean-all:clean clean-cpp



