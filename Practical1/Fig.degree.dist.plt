#!/usr/bin/gnuplot
reset
set term post eps enh col 'Helvetica' 16 dl 3

input_file='degree_dist.txt'
output_fig='Degree_Dist.eps'

set size ratio -1
set xrange [0:5]
set yrange [0:5]

set title 'Degree Distribution'  # plot title
set xlabel 'Number of Nodes' # x-axis label
set ylabel 'Degree of the Node'  # y-axis label

set out output_fig

plot input_file w p notitle
