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
opencv_inc_dirs = opencv_prefix + "/usr/local/include"


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
    include_dirs=["/Users/cody/Software/opencv-3.0-release/usr/local/include/"] + video_segment_includes,
    library_dirs=["../../build/lib/",
        "/Users/cody/Software/opencv-3.0-release/lib"],  # ditto
    libraries=["video_segmenter"] + opencvlibs,  # ditto
    extra_link_args=[],)],  # if needed
    cmdclass={'build_ext': build_ext})
