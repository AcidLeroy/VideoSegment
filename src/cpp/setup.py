from distutils.core import setup, Extension
from Cython.Distutils import build_ext

opencvlibs = []

setup(ext_modules=[Extension(
        "UserDivide",                 # name of extension
        ["pyuser_divide.pyx"],# filename of our Pyrex/Cython
        language="c++", # this causes Pyrex/Cython to create C++ source
        include_dirs=["../cpp/",
        "/Users/cody/Software/opencv-3.0-release/usr/local/include/"],
        library_dirs=["../../../build/lib", 
        "/Users/cody/Software/opencv-3.0-release/lib"],             # ditto
        libraries=["UserDivide", "opencv_videoio", "opencv_imgcodecs", 
        "opencv_highgui"],             # ditto
        extra_link_args=[],)],       # if needed
        cmdclass = {'build_ext': build_ext})
