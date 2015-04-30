from libcpp.string cimport string
include "../py_opencv/py_opencv.pyx"
include "../py_utils/vector_numpy.pyx"
from libcpp.vector cimport vector
    
cdef extern from "user_divide.h":
    cdef cppclass UserDivide: 
        UserDivide()
        void SegmentVideo(VideoCapture *vc, vector[size_t] *indices)  
        

cdef class PyVideoCapture:
    cdef VideoCapture *vc
    def __cinit__(self, s): 
        cdef string cpp_string = s.encode('UTF-8')
        print(s)
        self.vc = new VideoCapture(cpp_string); 
    def __dealloc__(self): 
        del self.vc
        
        
cdef class PyUserDivide:
    cdef UserDivide *thisptr # hold a C++ instance
    def __cinit__(self): 
        self.thisptr = new UserDivide()
    def __dealloc__(self): 
        del self.thisptr
    def SegmentVideo(self, PyVideoCapture pvc): 
        cdef vector[size_t] out;
        self.thisptr.SegmentVideo(pvc.vc, &out); 
        return out

        
        
