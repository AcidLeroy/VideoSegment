import numpy as np
from video_annotate import * 
import pickle
        
frames = np.random.rand(32,256,256,3)
va = VideoAnnotate(frames, 3, "segment1.pkl")
va.connect()
plt.show()
va.disconnect()

b = pickle.load(open("segment1.pkl", "rb"))
for a in b: 
  print (a)
