#./main 1 config.txt >> 10a2s3_eventsim.txt
#./main 1 config.txt >> 10a3s2_eventsim.txt
#./main 1 config.txt >> 10a3s3_eventsim.txt
#./main 1 config.txt >> 10a3s3p_eventsim.txt
#./main 1 config.txt >> 10a3ps3_eventsim.txt

# Plotting the results with gnuplot
#gnuplot -e "datafile='10a2s3_eventsim.txt'; mytitle = 'Queue Length Vs Time (Arrival Rate = 2 pkts/sec, Schedule Rate = 3 pkts/sec) [ES]';outputname='10a2s3_es.jpg'" script.plt 
#gnuplot -e "datafile='10a3s2_eventsim.txt'; mytitle = 'Queue Length Vs Time (Arrival Rate = 3 pkts/sec, Schedule Rate = 2 pkts/sec)[ES]';outputname='10a3s2_es.jpg'" script.plt 
#gnuplot -e "datafile='10a3s3_eventsim.txt'; mytitle = 'Queue Length Vs Time (Arrival Rate = 3 pkts/sec, Schedule Rate = 3 pkts/sec)[ES]';outputname='10a3s3_es.jpg'" script.plt
#gnuplot -e "datafile='10a3s3p_eventsim.txt'; mytitle = 'Queue Length Vs Time (Arrival Rate = 3 pkts/sec, Schedule Rate = 3.001 pkts/sec)[ES]';outputname='10a3s3p_es.jpg'" script.plt
#gnuplot -e "datafile='10a3ps3_eventsim.txt'; mytitle = 'Queue Length Vs Time (Arrival Rate = 3.001 pkts/sec, Schedule Rate = 3 pkts/sec)[ES]';outputname='10a3ps3_es.jpg'" script.plt



# make rclean
# change number of packets.


#./main 1 config.txt >> 100a2s3_eventsim.txt
#./main 1 config.txt >> 100a3s2_eventsim.txt
#./main 1 config.txt >> 100a3s3_eventsim.txt
#./main 1 config.txt >> 100a3s3p_eventsim.txt
#./main 1 config.txt >> 100a3ps3_eventsim.txt

# Plotting the results with gnuplot
#gnuplot -e "datafile='100a2s3_eventsim.txt'; mytitle = 'Queue Length Vs Time (Arrival Rate = 2 pkts/sec, Schedule Rate = 3 pkts/sec) [ES]';outputname='100a2s3_es.jpg'" script.plt 
#gnuplot -e "datafile='100a3s2_eventsim.txt'; mytitle = 'Queue Length Vs Time (Arrival Rate = 3 pkts/sec, Schedule Rate = 2 pkts/sec)[ES]';outputname='100a3s2_es.jpg'" script.plt 
#gnuplot -e "datafile='100a3s3_eventsim.txt'; mytitle = 'Queue Length Vs Time (Arrival Rate = 3 pkts/sec, Schedule Rate = 3 pkts/sec)[ES]';outputname='100a3s3_es.jpg'" script.plt
#gnuplot -e "datafile='100a3s3p_eventsim.txt'; mytitle = 'Queue Length Vs Time (Arrival Rate = 3 pkts/sec, Schedule Rate = 3.001 pkts/sec)[ES]';outputname='100a3s3p_es.jpg'" script.plt
#gnuplot -e "datafile='100a3ps3_eventsim.txt'; mytitle = 'Queue Length Vs Time (Arrival Rate = 3.001 pkts/sec, Schedule Rate = 3 pkts/sec)[ES]';outputname='100a3ps3_es.jpg'" script.plt



# Plotting the results with gnuplot
#gnuplot -e "datafile='output'; 
#            mytitle = 'Latency Vs Packet number (Arrival Rate = 0.3125 pkts/sec, Schedule Rate = 2 pkts/sec) [ES]';
#            outputname='latvspno_1024.jpg';
#            x_label='Packet number';
#            y_label='Packet Latency (Last bit entering to exiting)';
#            y2_label='Queue Size (in packets)';
#            parameter1='Packet Latency';            
#            parameter2='Queue Size' 
#            " scriptv2.plt 
#

gnuplot -e "datafile='queue_0.log'; 
            mytitle = 'Stats (pkt_size: 256 B, arr_rate: 1.25 pkts/s,sch_rate: 2 pkts/s)';
            outputname='stats_256.jpg';
            x_label='Packet entering time';
            y_label='Packet Latency (Last bit entering to exiting)';
            y2_label='# of packets';
            parameter1='Packet Latency (y1)';            
            parameter2='Packets Dropped (y2)'; 
            parameter3='Queue Size (y2)'
            " scriptv2.plt 


#gnuplot -e "datafile='qplot.txt'; 
#            mytitle = 'Queue Stats (Packet size = 256 Bytes, Arrival Rate = 1.25 pkts/sec, Schedule Rate = 2 pkts/sec) [ES]';
#            outputname='qplot_256.jpg';
#            x_label='time';
#            y_label='Number of packets';
#            parameter1='Queue Size (in packets)';            
#            parameter2='Number of packets dropped' 
#            " qplot.plt 
#
#gnuplot -e "datafile='output'; 
#            mytitle = 'Latency Stats (Packet size = 256 Bytes, Arrival Rate = 1.25 pkts/sec, Schedule Rate = 2 pkts/sec) [ES]';
#            outputname='lat_256.jpg';
#            x_label='Packet Number';
#            y_label='Packet Latency (last bit entering to last bit leaving)';
#            parameter1='per packet latency';            
#            " lat.plt 
#
#


# Running the python scripts to generate results
#python qsim.py -n 10 -p 64 -q 2000 -a 3 -s 2 -o a3s2_qsim.txt
#python qsim.py -n 10 -p 64 -q 2000 -a 2 -s 3 -o a2s3_qsim.txt
#python qsim.py -n 10 -p 64 -q 2000 -a 3 -s 3 -o a3s3_qsim.txt


