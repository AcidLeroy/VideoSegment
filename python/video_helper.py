import numpy as np
import cv2

class VideoHelper: 
    def __init__(self, filename): 
        self.cap = cv2.VideoCapture(filename)
        if not self.cap.isOpened(): 
            raise RuntimeError("Fatal Error: Could not open file {}".
                format(filename))
        cv_total_frames = cv2.CAP_PROP_FRAME_COUNT
        self.total_frames = int(self.cap.get(cv_total_frames))
        self.frame_shape = self.ReadFrame(0).shape;

    def ConvertToGray(self, frame): 
        return(cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)); 

    def ReadFrame(self, frame_number): 
        # Verify that we are in bounds
        if (frame_number > self.total_frames-1): 
           frame_number = self.total_frames-2 
        self.cap.set(cv2.CAP_PROP_POS_FRAMES, frame_number)
        ret, frame = self.cap.read()
        if not ret:
            raise RuntimeError("Fatal Error: Could not read/decode frame {}".
                format(frame_number))

        b,g,r = cv2.split(frame)       # get b,g,r
        frame = cv2.merge([r,g,b])     # switch it to rgb
        return frame

    def ReadFrameRange(self, start, stop):
        if stop < start: 
            start, stop = stop, start
        if start < 0: 
            start = 0; 
        if stop > self.total_frames - 1: 
            stop = self.total_frames - 1; 

        frame_buffer = np.zeros((stop-start+1,) + self.frame_shape, dtype=np.uint8) 
        
        for idx, val in enumerate(range(start, stop+1)): 
            frame_buffer[idx, ...] = self.ReadFrame(val)

        return frame_buffer


    def ReadToBuffer(self, buf_size_mb): 
        buf_size_b = 1e6 * buf_size_mb

        # Read first frame to get dimensions
        frame = self.ReadFrame(0);

        num_frames = int(np.floor(buf_size_b / frame.nbytes))
        if (self.total_frames < num_frames): 
            num_frames = self.total_frames

        # Preallocate frames
        frame_buffer = np.zeros((num_frames,) + self.frame_shape, dtype=np.uint8) 
        frame_buffer[0, ...] = frame
        for i in range(1, num_frames): 
            frame_buffer[i, ...] = self.ReadFrame(i)

        return frame_buffer;
