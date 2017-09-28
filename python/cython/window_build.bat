:: Build python package in wondows.
:: Required C++ compiler with C++11 support. VC++12
SET DISTUTILS_USE_SDK=1
SET MSSdk=1
python.exe setup.py build_ext --inplace --compiler=msvc