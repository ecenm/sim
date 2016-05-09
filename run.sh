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
gnuplot -e "datafile='output'; 
            mytitle = 'Latency Vs Packet number (Arrival Rate = 0.3125 pkts/sec, Schedule Rate = 2 pkts/sec) [ES]';
            outputname='latvspno_1024.jpg';
            x_label='Packet number';
            y_label='Packet Latency (Last bit entering to exiting)';
            y2_label='Queue Size (in packets)';
            parameter1='Packet Latency';            
            parameter2='Queue Size' 
            " scriptv2.plt 




# Running the python scripts to generate results
#python qsim.py -n 10 -p 64 -q 2000 -a 3 -s 2 -o a3s2_qsim.txt
#python qsim.py -n 10 -p 64 -q 2000 -a 2 -s 3 -o a2s3_qsim.txt
#python qsim.py -n 10 -p 64 -q 2000 -a 3 -s 3 -o a3s3_qsim.txt


