import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import numpy as np
import ctypes
import pathlib
import os

def plot_obstacle_array(num_obstacles, obstacle_array, x_limits, y_limits):
    #define Matplotlib figure and axis
    fig, ax = plt.subplots()
    #create axis limits
    plt.xlim(x_limits)
    plt.ylim(y_limits)
    #add rectangle to plot
    for i in range(num_obstacles):
        max_x = obstacle_array[0,i]
        max_y = obstacle_array[1,i]
        min_x = obstacle_array[2,i]
        min_y = obstacle_array[3,i]
        # print("max_x: " , max_x , " max_y: ", max_y , " min_x: " , min_x , " min_y: " , min_y)
        ax.add_patch(Rectangle((min_x, min_y), (max_x - min_x), (max_y - min_y)))
    #display plot
    plt.show()

script_dir = os.path.abspath(os.path.dirname(__file__))
libname_str = os.path.join(script_dir)
libname = pathlib.Path(libname_str)
obstacle_lib = ctypes.CDLL(libname / "libobstacle.so")
num_obstacles = 2
xlimits = [0,10]
ylimits = [0,10]
thickness_limits = [1,3]
obstacle_lib.createRandomObstacleArray.restype = np.ctypeslib.ndpointer(dtype=ctypes.c_float, shape=(4,num_obstacles))
# lib.arr_return.restype = ndpointer(dtype=ctypes.c_int, shape=(10,))
obstacle_array = obstacle_lib.createRandomObstacleArray(ctypes.c_int(num_obstacles), ctypes.c_float(xlimits[1]),
        ctypes.c_float(ylimits[1]), ctypes.c_float(xlimits[0]), ctypes.c_float(ylimits[0]),
        ctypes.c_float(thickness_limits[1]), ctypes.c_float(thickness_limits[0]))
print("obstacle array: " , obstacle_array.flatten())
# obstacle_array = np.array([[3,7,7], [4,8,2], [0,4,6], [0,4,0]])
# num_obstacles = np.shape(obstacle_array)[1]

# float* createRandomObstacleArray(unsigned int &num_obstacles, float &max_x_bound, float &max_y_bound,
#                                 float &min_x_bound, float &min_y_bound, float &max_thickness, float &min_thickness)

plot_obstacle_array(num_obstacles, obstacle_array, xlimits, ylimits)