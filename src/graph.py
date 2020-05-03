import matplotlib.pyplot as plt
import numpy as np


def pl():
	
	plt.plot([1000,10000], [0,3])
	plt.title("fp")
	plt.xlabel("Input Size")
	plt.ylabel("Time(ms)")
	plt.show()
