import numpy as np
from video_annotate import * 
import pickle
import sys
sys.path.append('../')
from video_helper import * 

filename = sys.argv[1]
step = int(sys.argv[2])
outfile = filename.split('.'); 
outfile = outfile[0]; 
outfile = outfile + ".pkl"

print("reading file: {}".format(filename));
print("Output file is: {}". format(outfile))

va = VideoAnnotate(filename, step, outfile, False); 
va.connect();
plt.show()
va.disconnect(); 

b = pickle.load(open("/Users/cody/test.pkl", "rb"))
for a in b: 
  print(a); 

