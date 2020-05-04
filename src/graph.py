import matplotlib.pyplot as plt
import numpy as np
import sys
import os

def parse_file(path):
    size = np.array([])
    swaps = np.array([])
    comps = np.array([])
    time = np.array([])
    input_data = open(str(path))
    for i, line in enumerate(input_data):
        if(line == '\n'):
            break
        temp = line.split(',')
        size = np.append(size, int(line.split(',')[0]))
        swaps = np.append(swaps, int(line.split(',')[1]))   
        comps = np.append(comps, int(line.split(',')[2]))
        time = np.append(time, int(line.split(',')[3]))
    os.remove(path)
    return (size, swaps, comps, time)

def plot_size_swaps_comps(sort_algo, size, swaps, comps, path):
    plt.clf()
    plt.plot(size, swaps, 'ko', size, swaps, 'b')
    plt.plot(size, comps, 'ko', size, comps, 'r')
    if(sort_algo == '0'):
        plt.title('Bubble Sort Performance (Swaps/Comps vs Size)')
    elif(sort_algo == '1'):
        plt.title('Insertion Sort Performance (Swaps/Comps vs Size)')
    elif(sort_algo == '2'):
        plt.title('Selection Sort Performance (Swaps/Comps vs Size)')
    elif(sort_algo == '3'):
        plt.title('Shell Sort Performance (Swaps/Comps vs Size)')
    elif(sort_algo == '4'):
        plt.title('Merge Sort Performance (Swaps/Comps vs Size)')
    elif(sort_algo == '5'):
        plt.title('Quick Sort Performance (Swaps/Comps vs Size)')
    elif(sort_algo == '6'):
        plt.title('Radix Sort Performance (Swaps/Comps vs Size)')
    plt.xlabel('Swaps (Blue) / Comparisons (Blue)')
    plt.ylabel('Size (elements)')
    plt.grid()
    path = path[:path.rfind('.')]
    path = path + '_swaps_comps_plot.png'
    plt.savefig(path)

def plot_size_time(sort_algo, size, time, path):
    plt.clf()
    plt.plot(size, time, 'ko', size, time, 'b')
    if(sort_algo == '0'):
        plt.title('Bubble Sort Performance (Time vs Size)')
    elif(sort_algo == '1'):
        plt.title('Insertion Sort Performance (Time vs Size)')
    elif(sort_algo == '2'):
        plt.title('Selection Sort Performance (Time vs Size)')
    elif(sort_algo == '3'):
        plt.title('Shell Sort Performance (Time vs Size)')
    elif(sort_algo == '4'):
        plt.title('Merge Sort Performance (Time vs Size)')
    elif(sort_algo == '5'):
        plt.title('Quick Sort Performance (Time vs Size)')
    elif(sort_algo == '6'):
        plt.title('Radix Sort Performance (Time vs Size)')
    plt.xlabel('Time (milliseconds)')
    plt.ylabel('Size (elements)')
    plt.grid()
    path = path[:path.rfind('.')]
    path = path + '_time_plot.png'
    plt.savefig(path)


#sort_algo = "1"
#path = "/home/kurt/temporary/res/insertion_sort.csv"

sort_algo = sys.argv[1]
path = sys.argv[2]
parse_file(path)
data = parse_file(path)
plot_size_swaps_comps(sort_algo, data[0], data[1], data[2], path)
plot_size_time(sort_algo, data[0], data[3], path)