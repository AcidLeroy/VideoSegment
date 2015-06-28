import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from drawable_rectangle import * 
import pickle
class VideoAnnotate:
    def __init__(self, frames, step = 1, file_to_write = "tmp.pkl"):
        self.frames = frames; 
        self.fig = plt.figure(); 
        self.current_frame = 0; 
        self.ax = plt.imshow(frames[:,:,self.current_frame])
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
            if self.current_frame == self.frames.shape[2]-1: 
                rects = self.get_rectangles(); 
                if (rects): 
                    if self.cube_segment_array: 
                        self.cube_segment_array[-1] = [self.current_frame, 
                            self.current_frame, rects]; 
                    else: 
                        self.cube_segment_array.append([self.current_frame, 
                            self.current_frame, rects]); 
                return 

            print("Stepping {} frames".format(self.step))

            start = self.current_frame; 
            if ((self.frames.shape[2]-1) - self.current_frame <= self.step):
                self.current_frame = self.frames.shape[2]-1 
            else: 
                self.current_frame += self.step-1;

            rects = self.get_rectangles(); 
            self.ax.set_data(self.frames[:,:,self.current_frame])
            self.dr.clear_patches(); 
            self.ax.figure.canvas.draw()
            # end point not inclusive
            if(rects): 
                self.cube_segment_array.append([start, 
                    self.current_frame, rects]); 

    def get_rectangles(self): 
        rectangles = []
        for patch in self.ax.axes.patches:
            rectangles.append([patch.get_xy(), patch.get_width(), patch.get_height()]); 
        return rectangles;

