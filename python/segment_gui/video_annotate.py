import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from drawable_rectangle import * 
import pickle
import sys

sys.path.append("../")
from read_video import VideoHelper
# readopencv [frames, row, cols, colors]

class VideoAnnotate:
    def __init__(self, filename, step = 1, file_to_write = "tmp.pkl"):
        self.frame_pos = 0; # indicate frame vector 
        self.fig = plt.figure(); 
        self.current_frame = 0; 
        self.vh = VideoHelper(filename); 
        self.ax = plt.imshow(self.vh.ReadFrame(self.current_frame))
        self.dr = DrawableRectangle(self.ax) 
        self.step = step; 
        self.file_to_write = file_to_write; 
        self.cube_segment_array = []

    def connect(self):
        self.dr.connect(); 
        self.cidkeypress = self.ax.figure.canvas.mpl_connect(
            'key_press_event', self.on_button_press)

    def disconnect(self):
        self.dr.disconnect(); 
        self.ax.figure.canvas.mpl_disconnect(self.cidkeypress)
        pickle.dump(self.cube_segment_array, open(self.file_to_write, "wb"))
        
    def on_button_press(self, event): 
        if event.key=='u': 
            print("Undoing rectangles...")
            self.dr.clear_patches(); 

        if event.key=='n':
            # Edge case (on last frame)
            if self.current_frame == self.vh.total_frames-1: 
                rects = self.get_rectangles(); 
                if (rects): 
                      self.cube_segment_array.append([self.current_frame, 
                          self.current_frame, rects]); 
                return 

            print("Stepping {} frames".format(self.step))

            start = self.current_frame; 
            if ((self.vh.total_frames - 1) - self.current_frame <= self.step):
                self.current_frame = self.vh.total_frames-1 
            else: 
                self.current_frame += self.step-1;

            rects = self.get_rectangles(); 
            # end point not inclusive
            if(rects): 
                self.cube_segment_array.append([start, 
                    self.current_frame, rects]); 
            self.current_frame +=1;
            self.ax.set_data(self.vh.ReadFrame(self.current_frame))
            self.dr.clear_patches(); 
            self.ax.figure.canvas.draw()

    def get_rectangles(self): 
        rectangles = []
        for patch in self.ax.axes.patches:
            rectangles.append([patch.get_xy(), patch.get_width(), patch.get_height()]); 
        return rectangles;

