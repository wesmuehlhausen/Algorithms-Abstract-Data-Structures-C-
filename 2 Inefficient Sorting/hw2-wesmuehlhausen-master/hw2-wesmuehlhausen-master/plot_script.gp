
#----------------------------------------------------------------------
# This is an example gnuplot script to generate a basic performance
# comparison graph for CPSC 223. This example requires an "out.dat"
# file, which was generated by running:
#
#     ./hw2perf 1 > out.dat
#
# assuming both the ArrayList and LinkedList data structures are
# implemented.
#
# To run this script type the following at the command line
#
#     gnuplot -c plot_script.gp infile testname testtype outfile
#
# For example, to create the output for the test above, run the
# following from the command line
#
#     gnuplot -c plot_script.gp "out.dat" "Reverse Sorted" "1" "graph1.png"
#
# The test type for test cases 1 and 2 is "1"
# The test type for test cases 3 and 4 is "2"
#----------------------------------------------------------------------


infile = ARG1
testname = ARG2
testtype = ARG3
outfile = ARG4


# Set the terminal for PNG output and aspect ratio
set terminal pngcairo enhanced font 'Verdana, 10'
set size ratio 0.75

# Save the graph in the given file name (e.g., "add_end.png")
set output outfile

# Set the title and each axis label
set xlabel "Input Size (n)"
set ylabel "Time (milliseconds)"

# Move the key to the left of the graph
set key left

# Plot the data
if (testtype == "1") {
  set title "Resizable Array vs Linked List '" . testname . "' Sort Performance";
  plot infile u 1:2 t "ArrayList Selection Sort" w linespoints pointtype 7, \
       infile u 1:3 t "LinkedList Selection Sort" w linespoints pointtype 7, \
       infile u 1:4 t "ArrayList Insertion Sort" w linespoints pointtype 7, \
       infile u 1:5 t "LinkedList Insertion Sort" w linespoints pointtype 7
} else {
  set title "Reversed vs Shuffled Data '" . testname . "' Sort Performance";
  plot infile u 1:2 t "ArrayList Reversed Data" w linespoints pointtype 7, \
       infile u 1:3 t "ArrayList Shuffled Data" w linespoints pointtype 7, \
       infile u 1:4 t "LinkedList Reversed Data" w linespoints pointtype 7, \
       infile u 1:5 t "LinkedList Shuffled Data" w linespoints pointtype 7
}