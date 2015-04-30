from libcpp.string cimport string
from libcpp.vector cimport vector
import numpy as np
cimport numpy as np
include "../py_utils/vector_numpy.pyx"

cdef extern from "method_accuracy.h":
    cdef cppclass MethodAccuracy: 
        MethodAccuracy(); 
        @staticmethod
        long NumFalsePositives[T](vector[T] &gnd_truth,
            vector[T] &predicted, long length); 
        @staticmethod
        long NumTrueNegatives[T](vector[T] &gnd_truth,
            vector[T] &predicted, long length); 
        @staticmethod
        long NumFalseNegatives[T](vector[T] &gnd_truth,
            vector[T] &predicted, long length); 
        @staticmethod
        long NumTruePositives[T](vector[T] &gnd_truth,
            vector[T] &predicted, long length); 

#def ConvertNpArray2Vector(np.ndarray[long, ndim=1] a): 
#    cdef vector[long] v; 
#    v.reserve(a.shape[0]); 
#    print("Size is : %d" % a.shape[0])
#    # This step is unfortunate because we have to copy
#    v.assign(&a[0], &a[0] + a.shape[0]); 
#    return v 
   

cdef class PyMethodAccuracy:
    cdef vector[long] truth; 
    cdef vector[long] pred; 
    cdef long total_length; 
    cdef MethodAccuracy *thisptr # hold a C++ instance
    def __cinit__(self, np.ndarray[long, ndim=1] gnd_truth, 
        np.ndarray[long, ndim=1] predicted, long length): 
        self.thisptr = new MethodAccuracy()
        print("Created PyMethodAccuracy"); 
        self.truth = ConvertNpArray2Vector(gnd_truth); 
        self.pred = ConvertNpArray2Vector(predicted); 
        self.total_length = length; 

    def __dealloc__(self): 
        del self.thisptr

    def PrintVectors(self): 
        print("Predicted values: "); 
        print("Size: %d"% self.pred.size()); 
        for i in range(self.pred.size()):
            print(self.pred[i]); 
        print("Truth values: "); 
        for i in range(self.truth.size()):
            print(self.truth[i]); 

    def NumFalsePositives(self):
        return (self.thisptr.NumFalsePositives[long](self.truth,
            self.pred,self.total_length))
    def NumTrueNegatives(self):
        return (self.thisptr.NumTrueNegatives[long](self.truth,
            self.pred,self.total_length))
    def NumFalseNegatives(self):
        return (self.thisptr.NumFalseNegatives[long](self.truth,
            self.pred,self.total_length))
    def NumTruePositives(self):
        return (self.thisptr.NumTruePositives[long](self.truth,
            self.pred,self.total_length))



