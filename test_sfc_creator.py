import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import numpy as np
import ctypes
import pathlib
import os

def plot_sfc_array(num_sfcs, sfc_array, num_obstacles, obstacle_array, x_limits, y_limits):
    #define Matplotlib figure and axis
    fig, ax = plt.subplots()
    #create axis limits
    plt.xlim((x_limits[0]-1, x_limits[1]+1))
    plt.ylim((y_limits[0]-1, y_limits[1]+1))
    #add rectangle to plot
    print("obstacle array: " , obstacle_array)
    for i in range(num_obstacles):
        box_max_x = obstacle_array[0,i]
        box_max_y = obstacle_array[1,i]
        box_min_x = obstacle_array[2,i]
        box_min_y = obstacle_array[3,i]
        # print("max_x: " , max_x , " max_y: ", max_y , " min_x: " , min_x , " min_y: " , min_y)
        ax.add_patch(Rectangle((box_min_x, box_min_y), 
                               (box_max_x - box_min_x), 
                               (box_max_y - box_min_y)))
    for j in range(num_sfcs):
        sfc_max_x = sfc_array[0,j]
        sfc_max_y = sfc_array[1,j]
        sfc_min_x = sfc_array[2,j]
        sfc_min_y = sfc_array[3,j]
        color = (np.random.random(), np.random.random(), np.random.random())
        ax.add_patch(Rectangle((sfc_min_x, sfc_min_y), 
                               (sfc_max_x - sfc_min_x), (sfc_max_y - sfc_min_y), 
                               linewidth=2, edgecolor=color, facecolor='none'))
    #display plot
    plt.show()

script_dir = os.path.abspath(os.path.dirname(__file__))
libname_str = os.path.join(script_dir)
libname = pathlib.Path(libname_str)
sfc_lib = ctypes.CDLL(libname / "libsfc.so")

class SFCMapGenerator(object):
    def __init__(self, obstacle_array, x_limits, y_limits, min_spacing):
        obstacle_array_length = len(obstacle_array)
        num_obstacles = int(obstacle_array_length/4)
        obstacle_array_c = (ctypes.c_float * obstacle_array_length)(*obstacle_array)
        sfc_lib.SFCMapCreator_new.argtypes = [ctypes.c_float, ctypes.c_float,
            ctypes.c_float, ctypes.c_float, ctypes.c_float, ctypes.c_int,
            ctypes.POINTER(ctypes.c_float)]
        sfc_lib.SFCMapCreator_new.restype = ctypes.c_void_p
        self.obj = sfc_lib.SFCMapCreator_new(ctypes.c_float(min_spacing), ctypes.c_float(x_limits[1]),
                ctypes.c_float(y_limits[1]), ctypes.c_float(x_limits[0]), ctypes.c_float(y_limits[0]),
                ctypes.c_int(num_obstacles), obstacle_array_c)
        sfc_lib.getNumberOfSFCs_new.argtypes = [ctypes.c_void_p]
        sfc_lib.getNumberOfSFCs_new.restype = ctypes.c_int
        num_sfcs = sfc_lib.getNumberOfSFCs_new(self.obj)
        sfc_lib.getSFCArray_new.argtypes = [ctypes.c_void_p]
        sfc_lib.getSFCArray_new.restype = np.ctypeslib.ndpointer(dtype=ctypes.c_float, shape=(4,num_sfcs))
        
    def getSFCArray(self):
        return sfc_lib.getSFCArray_new(self.obj)
    
    def getNumSFCs(self):
        return sfc_lib.getNumberOfSFCs_new(self.obj)


num_obstacles = 10
xlimits = [0,20]
ylimits = [0,20]
thickness_limits = [1,3]
min_spacing = 2

## Create obstacles
sfc_lib.createRandomObstacleArray.restype = np.ctypeslib.ndpointer(dtype=ctypes.c_float, shape=(4,num_obstacles))
obstacle_array = sfc_lib.createRandomObstacleArray(ctypes.c_int(num_obstacles), ctypes.c_float(xlimits[1]),
        ctypes.c_float(ylimits[1]), ctypes.c_float(xlimits[0]), ctypes.c_float(ylimits[0]),
        ctypes.c_float(thickness_limits[1]), ctypes.c_float(thickness_limits[0]))
print("obstacle array: " , obstacle_array)
# obstacle_array = np.array([[ 9.560177,   8.210312,  13.31599,    3.097362,  10.866077,  17.904964,
#   17.553402,  10.063512,  15.101596,   6.9690795],
#  [18.385164,  16.116405,   4.2257195,  3.4529514,  6.938169,   6.3696475,
#    9.885885,  10.541793,  19.119724,   9.89949  ],
#  [ 7.8548384,  6.20519,   11.965118,   1.055296,   8.351238,  16.149162,
#   15.20384,    8.148664,  12.477508,   4.999225 ],
#  [17.0272,    14.124512,   3.1157844,  1.453658,   4.16989,    4.671185,
#    7.795393,   8.806321,  16.305481,   8.568687 ]])

sfc_gen = SFCMapGenerator(obstacle_array.flatten(), xlimits, ylimits, min_spacing)
num_sfcs = sfc_gen.getNumSFCs()
print("num sfcs: " , num_sfcs)
sfc_array = sfc_gen.getSFCArray()
print(sfc_array)
plot_sfc_array(num_sfcs, sfc_array, num_obstacles, np.reshape(obstacle_array,(4,num_obstacles)), xlimits, ylimits)