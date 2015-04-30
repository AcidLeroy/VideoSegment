from libcpp.string cimport string

cdef extern from "<opencv2/videoio/videoio.hpp>" namespace "cv": 
    cdef cppclass VideoCapture:
        VideoCapture(string)
