set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set logscale x 10
set xtic auto                          # set xtics automatically
set ytic auto
set nokey
set grid 
set terminal jpeg large size 800,600
set output outputname

set title mytitle
set xlabel x_label
set ylabel y_label
set key right bottom

plot datafile using 1:2 title parameter1 with linespoints pt 7 ps 2, \
datafile using 1:3 title parameter2 with linespoints pt 5 ps 2


