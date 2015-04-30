from distutils.core import setup, Extension
from Cython.Distutils import build_ext
import os
import sys

opencv_prefix = os.environ.get('OpenCV_DIR')

if opencv_prefix == None: 
    print "Please set the OpenCV_DIR environment variable to build this."
    sys.exit()

# Need to link in opencv libraries
opencvlibs = [
        "opencv_highgui", 
        "opencv_imgcodecs",
        "opencv_videoio"
        ]
opencv_inc_dirs = [opencv_prefix + "/usr/local/include"]
opencv_lib_dirs = [opencv_prefix + "/lib"]


# Include directores for the CPP source
video_segment_includes = [
    "../src/interfaces",
    "../src/user_divide",
    "../src/video_marker" 
]


setup(ext_modules=[Extension(
    "py_video_segment",  # name of extension
    ["py_video_segment.pyx"],  # filename of our Pyrex/Cython
    language="c++",  # this causes Pyrex/Cython to create C++ source
    include_dirs= opencv_inc_dirs + video_segment_includes,
    library_dirs=["../../build/lib/"] + opencv_lib_dirs,  # ditto
    libraries=["video_segmenter"] + opencvlibs,  # ditto
    extra_link_args=[],)],  # if needed
    author="Cody W. Eilar",
    author_email="Cody.W.Eilar@gmail.com",
    cmdclass={'build_ext': build_ext})
