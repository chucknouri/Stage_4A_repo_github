# -*- coding: utf-8 -*-
"""
Created on Mon Aug 16 17:23:44 2021

@author: nouri
"""
from rplidar import RPLidar
from numpy import zeros
import numpy as np
#import matplotlib.animation as animation
import matplotlib.pyplot as plt


lidar = RPLidar('COM6', baudrate=115200)


distance=[]
angle=[]
j=0
k=0
l=0

lidar.stop_motor()
lidar.stop()
lidar.disconnect()
lidar = RPLidar('COM6', baudrate=115200)

fig=plt.figure()
ax = plt.subplot(111, projection='polar')
ax.set_xticks(np.arange(0,2*np.pi,np.pi/6.0))
ax.set_ylim(0,200)
ax.set_yticks(np.arange(0,200,50))

distance=[]
angle=[] 

lidar.stop_motor()
lidar.stop()
for scans in lidar.iter_scans(max_buf_meas=20000,min_len=1):
    i=0
    for j in range (k,10):
        for i in range (len(scans)):
            if (scans[i][0]>0):
                angle.append(-(np.pi/2)-scans[i][1]*np.pi/180)
                distance.append(scans[i][2])
                #print(angle[i], distance[i])   
        k=k+1
        #print (k)
        break
    if (k==10):
        break

#for i in range (len(angle)):
ax.scatter(angle, distance)
plt.show()

lidar.stop_motor()
lidar.stop()
lidar.disconnect()
