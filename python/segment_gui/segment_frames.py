import cv2
import numpy as np
import matplotlib.pyplot as plt
import unittest

class Rectangle:       
    def __init__(self, tl = (0,0), br = (0,0)): 
        if (len(tl) != 2 or len(br) != 2): 
            return 
        self.top_left = tl; 
        self.bottom_right = br; 
        
    def Display(self) : 
        print("top left = ({},{})".format(self.top_left[0], self.top_left[1]))

class TestRectangle(unittest.TestCase) : 
    def test_DefaultConstructor(self): 
        rect = Rectangle() 
        self.assertEqual((0, 0), rect.top_left)

class SegmentFrame: 
    def __init__(self, frame = np.zeros([10,10])):
        # Frame number + Rectangle
        self.segments = []; 
        self.frame = frame; 
    def AddRectangle(self, frame_number, rect): 
        self.segments.append([frame_number, rect.top_left, rect.bottom_right]) 
    
    def DrawBox(self, rect): 
        row = 0; 
        col = 1;
        top = self.frame[rect.top_left[row], rect.top_left[col]:(rect.bottom_right[col]+1)]
        left = self.frame[(rect.top_left[row] + 1):(rect.bottom_right[row]+1), rect.top_left[col]]
        right = self.frame[rect.top_left[row]+1:(rect.bottom_right[row]+1), rect.bottom_right[col]]
        bottom = self.frame[rect.bottom_right[row], (rect.top_left[col]+1):(rect.bottom_right[col])]
        
        top[:] = 1; 
        left[:] = 1; 
        right[:] = 1; 
        bottom[:] = 1; 

        
        
class TestSegmentFrame(unittest.TestCase) : 

    def setUp(self): 
        self.rows = 9; 
        self.cols = 10; 
        self.frame = np.zeros([self.rows,self.cols]); 
        self.box = Rectangle((2,3), (4,6));

    def test_DefaultConstructor(self): 
        seg = SegmentFrame()
        self.assertEqual(0, len(seg.segments))

    def test_Frame(self): 
        frame = np.zeros([13, 19])
        seg = SegmentFrame(frame)
        self.assertEqual(frame.all(), seg.frame.all()); 

    def test_AddTwoRects(self): 
        seg = SegmentFrame()
        seg.AddRectangle(1, Rectangle([0,0], [1,1])) 
        seg.AddRectangle(1, Rectangle([2,2], [3,3])) 
        self.assertEqual(2, len(seg.segments))

    def test_DrawBox(self): 
        seg = SegmentFrame(self.frame) 
        seg.DrawBox(self.box)
        self.assertEqual(1, seg.frame[self.box.top_left]);
        self.assertEqual(1, seg.frame[self.box.bottom_right]);
        print(self.frame)

if __name__ == '__main__': 
    unittest.main()
