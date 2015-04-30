import sys
sys.path.insert(0, '../lib/')
import py_video_segment as pvs

pud = pvs.PyUserDivide()
cap = pvs.PyVideoCapture("/Users/cody/test.MOV")
vals = pud.SegmentVideo(cap)

print(vals)
