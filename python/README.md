# Python Utility Scripts

This directory contains a list of python modules that are useful for video segmentation. Below I give a brief overview 
of what the function of each script is and how it is to be used. 

- *video_annotate.py* - This script is used for manually selecting a range of images from a video
- *video_helper.py* - Used for collecting video segments into numpy arrays using OpenCV.
- *drawable_rectangle* - A utility for drawing on matplotlib 2d graphs
- *hasher.py* - Input a file and generate a sha1 key. Useful to verify that you are working with
the same file as expected.
- *annotate.py* - high level script used to create .pkl files from video-type files. It calls 
*video_annotate.py*.
- *extractor.py* - This script takes a .pkl file as an input and can generate the target frames
and subregions of an image. This is useful for retrieving image cube data after it was 
manually selected.
- *hdf5_writer.py* - This script takes in a location of video files that have already been annotated
(i.e. you have already run the *annotate.py* script on them) and creates and hdf5 file from 
the pickled elements. This is done by actually reading the video file and then storing the frames
and corresponding subregions to the hdf5 file. As a result, the output can take quite a long time
and the output file can be quite large depending on how many videos and subregions there are. 
