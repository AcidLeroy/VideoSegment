# VideoSegment
Set of utilities to segment video based on particular actions that occur
in the video. 

## How to build
Unfortunately, there hasn't been time to implement a single, easy to use build. Currently, the steps that must
be followed in order to build are as follows: 
* To build c++ shared objects and programs once directory has been cloned: 
```
mkdir build
cd build
cmake ..
make -j
```
* To build the cython extensions to python:
```
cd cython
python setup.py build_ext
```
Notes for building: 
* C++ shared objects **must** be created first before cython modules can be created. 
* The python shared object is put into cython/lib/py_video_segment.so.
* In order to build the Cython modules, you **must** specify OpenCV_DIR environment variable. 

## Coding Convention
[Google C++
Style](https://google-styleguide.googlecode.com/svn/trunk/cppguide.html)
Please run the provided lint tool with this as well. 

## Third Party Libraries
* Cmake
* OpenCV
* Python 2.7 
* Google test
* Sci-kit learn
* Numpy
* Scipy

## Notes
- I have only test this using OS X yosemite. I don't know what 
  else it may work on. 
- Make sure that when you are building that you set the correct environment
  variables up to find where you installed OpenCV. I personally don't like
  to install things in my root directory if I can help it. 
- 
