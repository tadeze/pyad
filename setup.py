from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext as _build_ext
from Cython.Build import cythonize
import distutils.sysconfig
import numpy
import os

__version__ = "0.1"
os.environ["CC"] = "g++"
LICENSE = "Apache 2.0"
SRC_DIR = "pyad/src/"
CYTH_DIR = "pyad/"
PACKAGES = [CYTH_DIR]

class build_ext(_build_ext):
    def finalize_options(self):
        _build_ext.finalize_options(self)
        # Prevent numpy from thinking it is still in its setup process:
        __builtins__.__NUMPY_SETUP__ = False
        import numpy
        self.include_dirs.append(numpy.get_include())

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
    module_src = CYTH_DIR+"__ad.pyx"
    cmdclass = {"build_ext":build_ext}
else:
    module_src = "__ad.cpp"



ext = cythonize([Extension("*",
                  sources= [module_src, SRC_DIR + "facade_forest.cpp", SRC_DIR + "utility.cpp",
                                 SRC_DIR + "tree.cpp", SRC_DIR + "forest.cpp", SRC_DIR + "isolation_forest.cpp"],
                 language="c++",
                extra_compile_args=['-std=c++11'],
                include_dirs=[numpy.get_include(), SRC_DIR+"include"]),
                Extension("*", 
                sources=[CYTH_DIR+"__loda.pyx"],
                language="c++",
                include_dirs=[numpy.get_include()])
                ])

EXTENSIONS = ext


if __name__ == "__main__":
  setup(install_requires=['numpy', 'cython'],
        packages=PACKAGES,
        zip_safe=False,
        name="pyad",
        version= __version__,
        description="Anomaly detection algorithms",
        author="Tadesse Zemicheal",
        author_email="zemichet@oregonstate.edu",
        url= "http://eecs.oregonstate.edu/~zemichet",
        license=LICENSE,
        cmdclass=cmdclass,
        ext_modules=EXTENSIONS
        )

