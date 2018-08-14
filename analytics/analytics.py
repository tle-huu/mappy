from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
import sys
import os

import seaborn as sns; sns.set()

if len(sys.argv) < 2:
	sys.exit(1)


def parser1(file):
    Z = []
    average = 0

    with open(file) as f:
        print(f.readline())
        for line in f:
            temp = line.split()
            for i in range(len(temp)):
                temp[i] = float(temp[i])
                if (temp[i] != 20):
                    average = max(average, temp[i])
            Z.append(temp)
    f.closed
    return Z, average

def parser2(file):
    tab = []
    with open(file) as f:
        for line in f:
            temp = line.split()
            for i in range(len(temp)):
                temp[i] = float(temp[i])
            tab.append(temp)
    f.closed
    return tab

def calc_average(tab):
    distance, time = 0, 0
    numb = len(tab)
    for x in tab:
        distance += x[1]
        time += x[2]
    print("number of cars : {} ".format(numb))
    distance /= numb
    time /= numb
    return distance, time



dist , time = calc_average(parser2(sys.argv[1]))
print("average distance travelled : {}".format(dist))
print(" -- ")
print("average time travelling : {}".format(time))
sys.exit(1)

Z, average = parser1(sys.argv[1])

Z = np.rot90(np.array(Z))

ax = sns.heatmap(Z)

print(average)

plt.show()
sys.exit(1)

fig = plt.figure()
ax= fig.add_subplot(111, projection='3d')

X = np.arange(0, 20)
Y = np.arange(0, 45)

X, Y = np.meshgrid(X, Y)

Z = np.array(Z)
#Z = np.array(parser(sys.argv[1]))

surf = ax.plot_surface(X, Y, Z, rstride = 1, cstride=1, cmap=cm.coolwarm, linewidth=2, antialiased=False)

ax.set_zlim3d(0, 20)
ax.set_ylim3d(0, 45)
ax.set_xlim3d(0, 20)
fig.colorbar(surf, shrink=0.5, aspect=10)

print(Z)
#ax.plot_wireframe(X, Y, Z, rstride=10, cstride=10)

plt.show()
