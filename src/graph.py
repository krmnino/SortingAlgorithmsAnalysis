import matplotlib.pyplot as plt
import numpy as np
import sys

print(sys.argv[0])
print(sys.argv[1])
print(sys.argv[2])

def pl():
	plt.plot([1000,10000], [0,3])
	plt.title("fp")
	plt.xlabel("Input Size")
	plt.ylabel("Time(ms)")
	plt.show()
