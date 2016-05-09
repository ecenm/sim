# datafile and ouputname should be given as input
# example: gnuplot -e "datafile='a2s3_qsim.txt'; outputname='a2s3.png'" script.plt 


set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set y2tic auto                              # set ytics automatically
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
set y2label y2_label
set key right bottom

#set autoscale y
#set autoscale y2

#plot datafile using 2:3 title 'queue length (in bytes)' with lines lt rgb "green",\
#      datafile using 2:4 title 'bytes dropped ' with lines lt rgb "red"


plot datafile using 1:6 axes x1y1 title parameter1 with linespoints pt 4 ps 2,\
      datafile using 1:7 axes x1y2 title parameter2 with linespoints pt 7 ps 2 
#      datafile using 1:5 axes x1y2 title parameter2 with linespoints pt 6 ps 2 
#plot datafile using 1:2 title 'queue length (in bytes)' with lines lt rgb "green",\
#      datafile using 1:5 title 'bytes dropped ' with lines lt rgb "red"


