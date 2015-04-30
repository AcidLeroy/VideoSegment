from libcpp.vector cimport vector
import numpy as np
cimport numpy as np

def ConvertNpArray2Vector(np.ndarray[long, ndim=1] a): 
    cdef vector[long] v;  
    v.reserve(a.shape[0]); 
    print("Size is : %d" % a.shape[0])
    # This step is unfortunate because we have to copy
    v.assign(&a[0], &a[0] + a.shape[0]); 
    return v 
