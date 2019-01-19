from setuptools import setup, Extension
#from Cython.Distutils import build_ext
import distutils.sysconfig
import numpy
import os

os.environ["CC"] = "g++"  
NAME = "pyad"
VERSION = "0.1"
DESCR = "Anomaly detection usin Isolation Forest"
URL = "http://eecs.oregonstate.edu"
REQUIRES = ['numpy', 'cython']

AUTHOR = "Tadesse Zemicheal"
EMAIL = "tadesse.habte@gmail.com"

LICENSE = "Apache 2.0"
SRC_DIR = "src/"
CYTH_DIR = "./"
PACKAGES = [CYTH_DIR]

# Remove the "-Wstrict-protypes" compiler option, which isn't valid to c++
cfg_vars = distutils.sysconfig.get_config_vars()
CFLAGS = cfg_vars.get('CFLAGS')

if CFLAGS is not None:
  cfg_vars['CFLAGS'] = CFLAGS.replace("-Wstrict-prototypes", "")
# Check cython installed 
cmdclass = {}
USE_CYTHON = os.getenv('USE_CYTHON', True)
if USE_CYTHON:
    from Cython.Build import build_ext
    module_src = CYTH_DIR+"_pyad.pyx"
    cmdclass = {"build_ext":build_ext}
else:
    module_src = "_pyad.cpp"



ext = Extension("pyad", 
                  sources=[module_src,SRC_DIR + "facade_forest.cpp", SRC_DIR + "utility.cpp",
                                 SRC_DIR + "tree.cpp", SRC_DIR + "forest.cpp", SRC_DIR + "isolation_forest.cpp"],
                 language="c++",
                extra_compile_args=['-std=c++11'],
                include_dirs=[numpy.get_include(), SRC_DIR+"include"])

EXTENSIONS = [ext]

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
        license=LICENSE,
        cmdclass=cmdclass,
        ext_modules=EXTENSIONS
        )
