import serial
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from collections import deque

ser = serial.Serial("COM6", 9600)
x_c = 1000
pxmt_list = deque([0] * x_c)

fig, ax = plt.subplots()
plt.axis([0, x_c, 0, 70000])
plt.title("Dynamic Plot of vcnl4200", fontsize=25)
plt.xlabel("ms", fontsize=16)
plt.ylabel("Proximity", fontsize=16)
line, = ax.plot(pxmt_list)
for i in range(4):
    print(str(ser.readline())[2:][:-5])


def animate(i, data):
    data[-1] = int(str(ser.readline())[2:][:-5])
    data.rotate(1)
    line.set_ydata(data)  # update the data.
    return line,


ani = animation.FuncAnimation(
    fig, animate, fargs=[pxmt_list], interval=1, blit=True, save_count=50, frames=x_c)

plt.show()
