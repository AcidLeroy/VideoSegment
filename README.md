# VideoSegment
Set of utilities to segment video based on particular actions that occur
in the video. 

## How to build
Using Cmake, the shared objects for both the C++ project and the python shared objects can be created: 
```
mkdir build
cd build
cmake ..
make -j
```
Once these are built, the shared objects will be ready to use in `build/lib/`. 

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
