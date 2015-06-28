import numpy as np
import cv2

def ReadVideo(filename, buf_size_mb, color=True): 
    cap = cv2.VideoCapture(filename)
    if not cap.isOpened(): 
        print("Fatal Error: Could not open file %s") % filename
        exit(-1)
    
    ret, frame = cap.read()
    if not ret: 
        print ("Could not read a frame")
        exit(-1)
    if (not(color)): 
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY); 


    buf_size_b = 1e6 * buf_size_mb
    num_frames = int(np.floor(buf_size_b / frame.nbytes))
    cv_total_frames = cv2.CAP_PROP_FRAME_COUNT
    frames_in_video = int(cap.get(cv_total_frames))
    if (frames_in_video < num_frames): 
        num_frames = frames_in_video
    
    def PopulateBuffer(num):
        cap.set(cv2.CAP_PROP_POS_FRAMES, num)
        ret, frame = cap.read()
        
        if not ret:
            print("Fatal Error: Could not read/decode frame %d" % num)
            exit(-1)
        if (not(color)): 
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY); 
        return frame
         
    # Preallocate frames
    frame_buffer = np.zeros((num_frames,) + frame.shape, dtype=np.uint8) 
    
    for i in range(0, num_frames): 
        frame_buffer[i, :] = PopulateBuffer(i)
    return frame_buffer
