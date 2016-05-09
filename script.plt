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
set xlabel "time (in seconds)"
set ylabel "Queue length (in bytes)"
set key left top

plot datafile using 2:3 title 'queue length (in bytes)' with lines lt rgb "green",\
      datafile using 2:4 title 'bytes dropped ' with lines lt rgb "red"


