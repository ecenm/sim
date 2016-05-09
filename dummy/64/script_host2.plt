set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                          # set xtics automatically
set ytic auto
set yrange [0:5]
set y2range [0:40]
set y2tic auto                              # set ytics automatically
set nokey
set grid 
set terminal jpeg large size 800,600
set output outputname

set title mytitle
set xlabel x_label
set ylabel y_label
set y2label y2_label
set key right bottom

plot datafile using 3:5 axes x1y1 title parameter2 with linespoints pt 5 ps 2, \
    datafile using 3:7 axes x1y2 title parameter3 with linespoints pt 7 ps 2 


