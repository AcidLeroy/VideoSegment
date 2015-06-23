
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches
#from segment_frames 

class DrawableRectangle:
    def __init__(self, ax):
        self.ax = ax
        self.pressed = False;
        self.start = (0,0)
        self.current_patch = ax.axes.add_patch(
                patches.Rectangle(
                    self.start,
                    0,
                    0,
                    fill=False ))

    def PrintPoint(self, event): 
        row = round(event.ydata) 
        col = round(event.xdata) 
        print("row = {}, col = {}".format(row, col))

    def connect(self):
        'connect to all the events we need'
        self.cidpress = self.ax.figure.canvas.mpl_connect(
            'button_press_event', self.on_press)
        self.cidrelease = self.ax.figure.canvas.mpl_connect(
            'button_release_event', self.on_release)
        self.cidmotion = self.ax.figure.canvas.mpl_connect(
            'motion_notify_event', self.on_motion)
    

    def on_press(self, event):
        'on button press we will see if the mouse is over us and store some data'
        if event.inaxes != self.ax.axes: return

        contains, attrd = self.ax.contains(event)
        if not contains: return
        self.PrintPoint(event)
        self.pressed = True;
        row = round(event.ydata)
        col = round(event.xdata)
        self.start = (col, row)
        self.current_patch = self.ax.axes.add_patch(
                patches.Rectangle(
                    self.start,
                    10,
                    10,
                    linestyle = 'dashed',
                    hatch='X',
                    linewidth=3, 
                    fill=False ))
        self.ax.figure.canvas.draw()

    def on_motion(self, event):
        'on motion we will move the ax if the mouse is over us'
        if self.pressed is False: return
        if event.inaxes != self.ax.axes: return
        self.PrintPoint(event)
        self.current_patch.set_width(round(event.xdata) - self.start[0])
        self.current_patch.set_height(round(event.ydata) - self.start[1])
        self.ax.figure.canvas.draw()

    def on_release(self, event):
        'on release we reset the press data'
        if self.pressed is False: return
        if event.inaxes != self.ax.axes: return
        self.pressed = False
        self.current_patch.set_width(round(event.xdata) - self.start[0])
        self.current_patch.set_height(round(event.ydata) - self.start[1])
        self.ax.figure.canvas.draw()
    

    def disconnect(self):
        'disconnect all the stored connection ids'
        self.ax.figure.canvas.mpl_disconnect(self.cidpress)
        self.ax.figure.canvas.mpl_disconnect(self.cidrelease)
        self.ax.figure.canvas.mpl_disconnect(self.cidmotion)
        

class VideoAnnotate:
    def __init__(self, frames):
        self.frames = frames; 
        self.fig = plt.figure(); 
        self.current_frame = 0; 
        self.ax = plt.imshow(frames[:,:,self.current_frame])
        self.dr = DrawableRectangle(self.ax) 
        self.step = 1; 

    def connect(self):
        self.dr.connect(); 
        self.cidkeypress = self.ax.figure.canvas.mpl_connect(
            'key_press_event', self.on_button_press)

    def disconnect(self):
        self.dr.disconnect(); 
        self.ax.figure.canvas.mpl_disconnect(self.cidkeypress)
        
    def on_button_press(self, event): 
        print("pressed a button"); 
        print("Key pressed is: {}".format(event.key))
        if event.key=='n':
            if 
            self.current_frame += self.step;
            self.ax.set_data(self.frames[:,:,self.current_frame])
            self.ax.figure.canvas.draw()

frames = np.random.rand(256,256,32)

va = VideoAnnotate(frames)
va.connect()
plt.show()
va.disconnect()
