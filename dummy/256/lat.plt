# datafile and ouputname should be given as input
# example: gnuplot -e "datafile='a2s3_qsim.txt'; outputname='a2s3.png'" script.plt 


set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set nokey
set grid 
#set term postscript eps#output terminal and file
#set output "qsim.ps"

#set terminal png
#set terminal jpeg medium size 640,480
set terminal jpeg large size 800,600
set output outputname

#set title "Plot of Queue length Vs time (based on config)"
set title mytitle
set xlabel x_label
set ylabel y_label
set key right bottom

plot datafile using 1:7 title parameter1 with linespoints pt 7 ps 2


