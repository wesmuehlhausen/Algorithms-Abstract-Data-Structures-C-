
#----------------------------------------------------------------------
# This is an example gnuplot script to generate a basic performance
# comparison graph for CPSC 223. This example requires an "out.dat"
# file, which was generated by running:
#
#     ./hw4perf 1 > out.dat
#
# assuming both the ArrayListCollection and LinkedListCollection data
# structures are implemented.
#
# To run this script type the following at the command line
#
#     gnuplot -c plot_script.gp infile testname outfile
#
# For example, to create the output for the add test above, run the
# following from the command line
#
#     gnuplot -c plot_script.gp "out.dat" "Add" "add.png"
#
#----------------------------------------------------------------------


infile = ARG1
testname = ARG2
outfile = ARG3


# Set the terminal for PNG output and aspect ratio
set terminal pngcairo enhanced font 'Verdana, 10'
set size ratio 0.75

# Save the graph in the given file name (e.g., "add_end.png")
set output outfile

# Set the title and each axis label
set title "Resizable Array vs Linked List " . testname . " Performance"
set xlabel "Input Size (n)"
set ylabel "Time (microseconds)"

# Move the key to the left of the graph
set key left

# Plot the data
plot infile u 1:2 t "ArrayList Collection" w linespoints pointtype 7, \
     infile u 1:3 t "LinkedList Collection" w linespoints pointtype 7

