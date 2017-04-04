from distutils.core import setup, Extension
import numpy
from Cython.Distutils import build_ext
import os
os.environ["CC"] = "g++"
os.environ["CXX"] = "g++"
setup(
    cmdclass={'build_ext': build_ext},
    ext_modules=[Extension("perceptron",
                 sources=["perceptron.pyx"],
                 language="c++",
                 extra_compile_args=['-std=c++11'],
                 include_dirs=[numpy.get_include()])],
    )
