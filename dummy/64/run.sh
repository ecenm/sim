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

# change pkt_size and work_rate iteratively

#gnuplot -e "datafile='queue_0.log'; 
#            mytitle = 'Stats (pkt_size: 64 B, output_work_rate: 10, more details in Table 1)';
#            outputname='stats_64_work_rate_10.jpg';
#            x_label='Packet entering time';
#            y_label='Packet Latency (Last bit entering to exiting)';
#            y2_label='# of packets';
#            parameter1='Packet Latency (y1)';            
#            parameter2='Packets Dropped (y2)'; 
#            parameter3='Queue Size (y2)'
#            " scriptv2.plt 


gnuplot -e "datafile='queue_0.log'; 
            mytitle = 'Packet Latency Vs Packet Entering time (pkt_size: 1024 B), host 0 to host 1';
            outputname='stats_1024_work_rate_10.jpg';
            x_label='Packet entering time';
            y_label='Packet Latency (Last bit entering to exiting)';
            parameter1='Packet Latency'            
            " scriptv2.plt 

gnuplot -e "datafile='1000.log'; 
            mytitle = 'Host 0 Stats (pkt_size: 1024 B, input_arrival_rate: 10, output_service_rate: 10)';
            outputname='host_0_stats.jpg';
            x_label='Packet entering time';
            y_label='# of packets (y1)';           
            y2_label='# of packets (y2)';
            parameter2='Queue Size (y1)'; 
            parameter3='Packets Dropped (y2)'
            " script_host0.plt 

gnuplot -e "datafile='1010.log'; 
            mytitle = 'Host 1 Stats (pkt_size: 1024 B, input_arrival_rate: 10, output_service_rate: 4)';
            outputname='host_1_stats.jpg';
            x_label='Packet entering time';
            y_label='# of packets (y1)';           
            y2_label='# of packets (y2)';
            parameter2='Queue Size (y1)'; 
            parameter3='Packets Dropped (y2)'
	    " script_host1.plt

gnuplot -e "datafile='1020.log'; 
            mytitle = 'Host 2 Stats (pkt_size: 1024 B, input_arrival_rate: 10, output_service_rate: 10)';
            outputname='host_2_stats.jpg';
            x_label='Packet entering time';
            y_label='# of packets (y1)';           
            y2_label='# of packets (y2)';
            parameter2='Queue Size (y1)'; 
            parameter3='Packets Dropped (y2)'
            " script_host2.plt 

gnuplot -e "datafile='1030.log'; 
            mytitle = 'Host 3 Stats (pkt_size: 1024 B, input_arrival_rate: 10, output_service_rate: 4)';
            outputname='host_3_stats.jpg';
            x_label='Packet entering time';
            y_label='# of packets (y1)';           
            y2_label='# of packets (y2)';
            parameter2='Queue Size (y1)'; 
            parameter3='Packets Dropped (y2)'
	    " script_host3.plt


gnuplot -e "datafile='4000.log'; 
            mytitle = 'Switch Queue 0 Stats (pkt_size: 1024 B, input_arrival_rate: 10, output_service_rate: 10)';
            outputname='switch_queue_0_stats.jpg';
            x_label='Packet entering time';
            y_label='# of packets (y1)';           
            y2_label='# of packets (y2)';
            parameter2='Queue Size (y1)'; 
            parameter3='Packets Dropped (y2)'
            " script_switch_q_0.plt 

gnuplot -e "datafile='4001.log'; 
            mytitle = 'Switch Queue 1 Stats (pkt_size: 1024 B, input_arrival_rate: 10, output_service_rate: 4)';
            outputname='switch_queue_1_stats.jpg';
            x_label='Packet entering time';
            y_label='# of packets (y1)';           
            y2_label='# of packets (y2)';
            parameter2='Queue Size (y1)'; 
            parameter3='Packets Dropped (y2)'
	        " script_switch_q_1.plt

gnuplot -e "datafile='4002.log'; 
            mytitle = 'Switch Queue 2 Stats (pkt_size: 1024 B, input_arrival_rate: 10, output_service_rate: 10)';
            outputname='switch_queue_2_stats.jpg';
            x_label='Packet entering time';
            y_label='# of packets (y1)';           
            y2_label='# of packets (y2)';
            parameter2='Queue Size (y1)'; 
            parameter3='Packets Dropped (y2)'
            " script_switch_q_2.plt 

gnuplot -e "datafile='4003.log'; 
            mytitle = 'Switch Queue 3 Stats (pkt_size: 1024 B, input_arrival_rate: 10, output_service_rate: 4)';
            outputname='switch_queue_3_stats.jpg';
            x_label='Packet entering time';
            y_label='# of packets (y1)';           
            y2_label='# of packets (y2)';
            parameter2='Queue Size (y1)'; 
            parameter3='Packets Dropped (y2)'
	        " script_switch_q_3.plt

#gnuplot -e "datafile='qplot.txt'; 
#            mytitle = 'Queue Stats (Packet size = 64 Bytes, Arrival Rate = 5 pkts/sec, Schedule Rate = 2 pkts/sec) [ES]';
#            outputname='qplot_64.jpg';
#            x_label='time';
#            y_label='Number of packets';
#            parameter1='Queue Size (in packets)';            
#            parameter2='Number of packets dropped' 
#            " qplot.plt 
#
#gnuplot -e "datafile='output'; 
#            mytitle = 'Latency Stats (Packet size = 64 Bytes, Arrival Rate = 5 pkts/sec, Schedule Rate = 2 pkts/sec) [ES]';
#            outputname='lat_64.jpg';
#            x_label='Packet Number';
#            y_label='Packet Latency (last bit entering to last bit leaving)';
#            parameter1='per packet latency';            
#            " lat.plt 
#



# Running the python scripts to generate results
#python qsim.py -n 10 -p 64 -q 2000 -a 3 -s 2 -o a3s2_qsim.txt
#python qsim.py -n 10 -p 64 -q 2000 -a 2 -s 3 -o a2s3_qsim.txt
#python qsim.py -n 10 -p 64 -q 2000 -a 3 -s 3 -o a3s3_qsim.txt


