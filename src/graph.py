import matplotlib.pyplot as plt
import numpy as np
import sys


def parse_file():
    size = np.array([])
    swaps = np.array([])
    comps = np.array([])
    time = np.array([])
    input_data = open(str(parse_file))
    for i, line in enumerate(input_data):
        if(line == '\n'):
            break
        size = np.append(size, int(line.split(',')[0]))
        swaps = np.append(swaps, int(line.split(',')[1]))   
        comps = np.append(comps, int(line.split(',')[2]))
        time = np.append(swaps, int(line.split(',')[3]))
    return (size, swaps, comps, time)

def plot_graph():
    plt

sort_algo = sys.argv[1]
path = sys.argv[2]
parse_file(path)