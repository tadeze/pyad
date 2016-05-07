# from distutils.core import setup, Extension
# import numpy
# from Cython.Distutils import build_ext
# import os
# os.environ["CC"] = "g++"
# os.environ["CXX"] = "g++"
# setup(
#     cmdclass={'build_ext': build_ext},
#     ext_modules=[Extension("pyForest",
#                  sources=["_pyForest.pyx", "../FacadeForest.cpp","../utility.cpp","../Tree.cpp","../Forest.cpp","../IsolationForest.cpp"],
#                  language="c++",
#                  extra_compile_args=['-std=c++11'],
#                  include_dirs=[numpy.get_include()])],
#     )



from setuptools import setup, Extension
from Cython.Distutils import build_ext
import numpy
import os
os.environ["CC"] = "g++"
os.environ["CXX"] = "g++"

NAME = "pyiForest"
VERSION = "0.1"
DESCR = "A python wrapper to c++ iForest code in Cython"
URL = "http://eecs.oregonstate.edu"
REQUIRES = ['numpy', 'cython']

AUTHOR = "Tadesse Zemicheal"
EMAIL = "tadesse.habte@gmail.com"

#LICENSE = "Apache 2.0"

SRC_DIR = "src/CPP/"
CYTH_DIR="src/"
PACKAGES =[CYTH_DIR]

ext_1 = Extension("pyiForest",
                 sources=[CYTH_DIR+"_pyForest.pyx", SRC_DIR+"FacadeForest.cpp",SRC_DIR+"utility.cpp",
                 SRC_DIR+"Tree.cpp",SRC_DIR+"Forest.cpp",SRC_DIR+"IsolationForest.cpp"],
                 language="c++",
                 extra_compile_args=['-std=c++11'],
                 include_dirs=[numpy.get_include()])
EXTENSIONS = [ext_1]

if __name__ == "__main__":
    setup(install_requires=REQUIRES,
          packages=PACKAGES,
          zip_safe=False,
          name=NAME,
          version=VERSION,
          description=DESCR,
          author=AUTHOR,
          author_email=EMAIL,
          url=URL,
          #license=LICENSE,
          cmdclass={"build_ext": build_ext},
          ext_modules=EXTENSIONS
          )