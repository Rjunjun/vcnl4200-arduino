import serial
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

ser = serial.Serial("COM8", 9600)
x_c = 1000
pxmt_list = [0] * x_c

for i in range(4) :
    str(ser.readline())[2:][:-5]
fig, ax = plt.subplots()
plt.axis([0, x_c, 0, 65537])
plt.title("Dynamic Plot of vcnl4200",fontsize=25)
plt.xlabel("ms",fontsize=16)
plt.ylabel("Proximity",fontsize=16)
line, = ax.plot(pxmt_list)

def animate(i):
    cc=str(ser.readline())[2:][:-5]
    pxmt_list[i % x_c] = int(cc)
    if(i % x_c == 0) :
        for i in range(x_c):
            pxmt_list[i] = 0
    line.set_ydata(pxmt_list)  # update the data.
    return line,

ani = animation.FuncAnimation(
    fig, animate, interval=1, blit=True, save_count=50)

plt.show()

