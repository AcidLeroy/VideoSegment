from libcpp.string cimport string

include "../py_opencv/py_opencv.pyx"

cdef extern from "segmenter_interface.h":
    ctypedef struct Segment: 
        pass
    
cdef extern from "<vector>" namespace "std":
    cdef cppclass vector [T]: 
        pass

    

cdef extern from "user_divide.h":
    cdef cppclass UserDivide: 
        UserDivide()
        void SegmentVideo(VideoCapture *vc, vector[Segment] *indices)  
        

cdef class PyVideoCapture:
    cdef VideoCapture *vc
    def __cinit__(self, s): 
        cdef string cpp_string = s.encode('UTF-8')
        print(s)
        self.vc = new VideoCapture(cpp_string); 
        
cdef class PySegVector: 
    cdef vector[Segment] *seg
    
        
cdef class PyUserDivide:
    cdef UserDivide *thisptr # hold a C++ instance
    def __cinit__(self): 
        self.thisptr = new UserDivide()
    def __dealloc__(self): 
        del self.thisptr
        
#     def doSegmentVideo(self, PyVideoCapture, PySegVector): 
#         print "SegmentVideo"
#     cdef SegmentVideo(self, VideoCapture *vc, vector[Segment] *indices): 
#         return self.thisptr.SegmentVideo(vc, indices)

        
