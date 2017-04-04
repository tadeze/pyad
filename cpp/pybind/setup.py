import os, sys

from distutils.core import setup, Extension
from distutils import sysconfig
os.environ["CC"] = "g++"
os.environ["CXX"] = "g++"

cpp_args = ['-std=c++11']

ext_modules = [
    Extension(
    'pyiforest',
        ['../utility.cpp','../Tree.cpp','../FacadeForest.cpp','../Forest.cpp',
        '../IsolationForest.cpp','wrapper.cpp'],
        include_dirs=['../pybind11/'],
    language='c++',
    extra_compile_args = cpp_args,
    ),
]

setup(
    name='wrap',
    version='0.0.1',
    author='Cliburn Chan',
    author_email='cliburn.chan@duke.edu',
    description='Example',
    ext_modules=ext_modules,
)
