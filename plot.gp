#!/usr/bin/gnuplot -c

set terminal png

set key autotitle columnhead

stats ARG1 nooutput

plot for [i=2:STATS_columns] ARG1 using 1:i with lines

