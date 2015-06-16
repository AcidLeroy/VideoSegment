import cv2
import numpy as np
import matplotlib.pyplot as plt
import unittest

class Rectangle:       
    def __init__(self, tl = [0,0], br = [0,0]): 
        if (len(tl) != 2 or len(br) != 2): 
            return 
        self.top_left = tl; 
        self.bottom_right = br; 
        
    def Display(self) : 
        print("top left = ({},{})".format(self.top_left[0], self.top_left[1]))

class TestRectangle(unittest.TestCase) : 
    def test_DefaultConstructor(self): 
        rect = Rectangle() 
        self.assertEqual([1, 0], rect.top_left)

if __name__ == '__main__': 
    unittest.main()
