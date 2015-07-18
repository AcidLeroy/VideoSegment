import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as patches

class DrawableRectangle:
    def __init__(self, ax):
        self.ax = ax
        self.pressed = False;
        self.start = (0,0)

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
                    0,
                    0,
                    linestyle = 'dashed',
                    hatch='X',
                    linewidth=3, 
                    fill=False ))
        self.ax.figure.canvas.draw()

    def on_motion(self, event):
        'on motion we will move the ax if the mouse is over us'
        if self.pressed is False: return
        if event.inaxes != self.ax.axes: return
        self.current_patch.set_width(round(event.xdata) - self.start[0])
        self.current_patch.set_height(round(event.ydata) - self.start[1])
        self.ax.figure.canvas.draw()

    def clear_patches(self): 
        self.ax.axes.patches = []
        self.ax.figure.canvas.draw()

    def on_release(self, event):
        'on release we reset the press data'
        if self.pressed is False: return
        if event.inaxes != self.ax.axes: return
        self.pressed = False
        diff_x = round(event.xdata) - self.start[0];
        diff_y = round(event.ydata) - self.start[1];
        if (diff_x != 0 and diff_y != 0):
            self.current_patch.set_width(diff_x)
            self.current_patch.set_height(diff_y)
            self.ax.figure.canvas.draw()
        else: 
            self.current_patch.remove(); 

    def disconnect(self):
        'disconnect all the stored connection ids'
        self.ax.figure.canvas.mpl_disconnect(self.cidpress)
        self.ax.figure.canvas.mpl_disconnect(self.cidrelease)
        self.ax.figure.canvas.mpl_disconnect(self.cidmotion)
