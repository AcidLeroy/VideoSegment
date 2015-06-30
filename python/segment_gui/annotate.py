import numpy as np
from video_annotate import * 
import pickle
import sys
sys.path.append('../')
from read_video import * 

filename = sys.argv[1]
outfile = filename.split('.'); 
outfile = outfile[0]; 
outfile = outfile + ".pkl"
size_mb = 500; # 500 megabites should be plenty of buffer

print("reading file: {}".format(filename));
print("Output file is: {}". format(outfile))
frame_buffer = ReadVideo(filename, size_mb);

va = VideoAnnotate(filename, 10, outfile); 
va.connect();
plt.show()
va.disconnect(); 

b = pickle.load(open("/Users/cody/test.pkl", "rb"))
for a in b: 
  print(a); 

