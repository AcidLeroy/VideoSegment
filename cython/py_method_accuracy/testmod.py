import sys
sys.path.insert(0, '../lib/')
import py_video_segment as pvs
import numpy as np

gnd_truth = np.array([1,2,3]); 
predicted = np.array([1,2,2,4]); 

a = pvs.PyMethodAccuracy(gnd_truth, predicted, 10)

a.PrintVectors()
print("Number of false positives: ")
print(a.NumFalsePositives()); 
print(a.NumTruePositives()); 
print(a.NumFalseNegatives()); 
print(a.NumTrueNegatives()); 
