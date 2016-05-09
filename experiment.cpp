#include <iostream>
#include <algorithm>
#include <fstream>
#include <stdlib.h>
#include <deque>
#include <stdint.h>
#include <cstdlib>
#include <ctime>
#include <map>
#include <iomanip>
#include "assert.h"
#include "math.h"

#include "packet.h"
#include "node.h"
#include "event.h"
#include "topology.h"
#include "queue.h"
#include "random_variable.h"

#include "factory.h"

#include "packet_generator.h"
#include "stats.h"
#include "params.h"

extern Topology *topology;
extern double current_time;
//extern std::priority_queue<event*, std::vector<event*>, EventComparator> event_queue;
extern std::priority_queue<event*, std::vector<event*>, EventComparator<event> > event_queue;
extern std::deque<Packet*> packets_to_schedule;
//extern std::vector<Packet*> packets_to_switch; // My declaration
std::deque<Packet*> packets;
extern std::deque<event*> packet_arrivals;
//extern Queue* myqueue;
Queue *myqueue;
extern uint32_t num_outstanding_packets;
extern uint32_t max_outstanding_packets;
extern DCExpParams params;
extern void add_to_event_queue(event*);
extern void read_experiment_parameters(std::string conf_filename, uint32_t exp_type);
extern void read_flows_to_schedule(std::string filename, uint32_t num_lines, Topology *topo);
extern uint32_t duplicated_packets_received;
extern std::vector<Packet*> packets_for_tx_stats;
extern std::vector< std::vector<Packet*> > packets_to_switch; // My declaration

std::vector< std::vector<Packet*> > packets_for_rx_stat;
std::vector< std::vector<Packet*> > packets_for_tx_stat;
std::vector< std::vector<Packet*> > packets_to_switch;
std::vector <uint32_t> packet_pushed;
std::vector <uint32_t> no_of_packets_tracker;
std::vector <uint32_t> tokens;


extern uint32_t num_outstanding_packets_at_50;
extern uint32_t num_outstanding_packets_at_100;
extern uint32_t arrival_packets_at_50;
extern uint32_t arrival_packets_at_100;

extern double start_time;
extern double get_current_time();
double tnext;
double tfirst;
double schedule_time;

extern void run_scenario();

/*int jrand (int n)
{
    static int seq[] = {
        //0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf
    };

    std::random_shuffle (seq, seq + sizeof seq / sizeof *seq);

    const int rnd =
        ((seq [0] << 11) | (seq [1] << 8) | (seq [2] << 4)) + seq [3];

    return rnd % n;
}*/


void run_experiment(int argc, char **argv, uint32_t exp_type) {
    if (argc < 3) {
        std::cout << "Usage: <exe> exp_type conf_file" << std::endl;
        return;
    }
   
    std::string conf_filename(argv[2]);
    read_experiment_parameters(conf_filename, exp_type);
    //params.num_hosts = 144;
    params.num_agg_switches = 9;
    params.num_core_switches = 4;
    int number_of_1s = 0;
    int number_of_3s = 0;

    if (params.simple_topology == 1) {
        topology = new SimpleTopology(params.num_hosts, params.bandwidth, params.queue_type, params.num_hosts);
    }    

    //std::cout << "Number of Hosts is : " << topology->num_hosts<<std::endl;
    for(int i=0;i<params.num_hosts;i++){
            packets_for_rx_stat.push_back(vector<Packet*>());  
            packets_for_tx_stat.push_back(vector<Packet*>());  
            packets_to_switch.push_back(vector<Packet*>());
            packet_pushed.push_back(uint32_t());
            no_of_packets_tracker.push_back(uint32_t());
            tokens.push_back(uint32_t());
 
            std::cout << packets_for_rx_stat.size()<< std::endl;          
    }


    uint32_t num_packets = params.num_packets_to_run;

   // input
    double input_packet_size_in_time = (1.0/double(params.input_work_rate))* ceil(double(params.packet_size)/double(params.input_bus_width));
   //double arrival_time_unit = input_packet_size_in_time;


   double input_clocks_per_packet = ceil(double(params.packet_size)/double(params.input_bus_width));

   double derived_arrival_rate = double(params.input_work_rate)/input_clocks_per_packet;
   double arrival_time_unit = 1.0/derived_arrival_rate;

   // output

   double output_packet_size_in_time = (1.0/double(params.output_work_rate))* ceil(double(params.packet_size)/double(params.output_bus_width));
   //double arrival_time_unit = input_packet_size_in_time;


   double output_clocks_per_packet = ceil(double(params.packet_size)/double(params.output_bus_width));

   double derived_schedule_rate = double(params.output_work_rate)/output_clocks_per_packet;
   double schedule_time_unit = 1.0/derived_schedule_rate;





    std::cout << "***********************************************************"<< std::endl;
    std::cout << "--------------------- Config details   --------------------"<< std::endl;
    std::cout << "***********************************************************"<< std::endl;
   std::cout<<" "<< std::endl;
   std::cout<<"queue_size "<< params.queue_size << std::endl;
   std::cout<<"num_packets_to_run "<< params.num_packets_to_run << std::endl;
   std::cout<<"packet_size "<< params.packet_size << std::endl;
   std::cout<<"Input parameters: "<< std::endl;
   std::cout<<"\t"<<"input_bus_width "<< params.input_bus_width << std::endl;
   std::cout<<"\t"<<"input_work_rate "<< params.input_work_rate << std::endl;
   std::cout<<"\t"<<"input_clocks_per_packet "<< input_clocks_per_packet << std::endl;
   std::cout<<"\t"<<"derived_arrival_rate "<< derived_arrival_rate << std::endl;
   std::cout<<"\t"<<"arrival_time_unit "<< arrival_time_unit << std::endl;
   std::cout<<"Output parameters: "<< std::endl;
   std::cout<<"\t"<<"output_bus_width "<< params.output_bus_width << std::endl;
   std::cout<<"\t"<<"output_work_rate "<< params.output_work_rate << std::endl;
   std::cout<<"\t"<<"output_clocks_per_packet "<< output_clocks_per_packet << std::endl;
   std::cout<<"\t"<<"derived_schedule_rate "<< derived_schedule_rate << std::endl;
   std::cout<<"\t"<<"schedule_time_unit "<< schedule_time_unit << std::endl;
   


   std::cout<<" "<< std::endl;
   //double arrival_time_unit = 1.0/params.arrival_rate; old way

    add_to_event_queue(new StatsEvent (4));
 
// for :(iterates over queues)
  //for (int j=2;j<3;j++){ // testing for single queue chaining
/*  for (int j=0;j<2;j+=2){ // testing for single queue chaining
  //for (int j=0;j<params.num_hosts;j++){ 
   for (uint32_t i = 0; i < params.num_packets_to_run; i++){

    std::vector<int> ports={1,3,1,3,1,3,1,3,1,3};
    double new_arrival_event = new_arrival_event+arrival_time_unit;

//   std::cout<<"-------------------------------------------> "<< std::endl;
     // int rand_num = jrand(9);
     // int random_port = ports[rand_num];
      //std::cout<< "random number is "<< rand_num << "\t" << "random port is " << random_port << std::endl;
    //std::cout << "j, j+1 " << j << "," << j+1 << std::endl;
    //std::cout << "j, random_port " << j << "," << j+1 << std::endl;
    //Packet *p1 = new Packet(start_time, i, 0, params.packet_size, topology->hosts[j], topology->hosts[random_port]);
    Packet *p1 = new Packet(start_time, i, 0, params.packet_size, topology->hosts[j], topology->hosts[1]);
    p1->start_time = 0 ;
    p1->end_time =0 ;
    p1->qid=j; // encoding the identification of queue for packet
    p1->src = topology->hosts[j];
    //p1->dst = topology->hosts[random_port] ;
    p1->dst = topology->hosts[1] ;
    std::cout << "p1->qid " << p1->qid << std::endl;

    if(random_port == 1)
     number_of_1s += 1;  
    else if (random_port == 3)
      number_of_3s += 1;
    else
        std::cout << "Invalid output port selected" << std::endl;


    //packets_for_tx_stats.push_back(p1);// array for stats
    packets_for_tx_stat[j].push_back(p1);// array for stats
    
    //std::cout<< p1->seq_no << "\t" << p1->src->id << "," << p1->dst->id << "\t"<< p1->size << "\t" << p1->start_time << "\t" << p1->end_time << std::endl;

    //std::cout<< "PRINTINGGGGGGGG "<< params.num_hosts <<  std::endl;
    //std::cout<< packets_for_tx_stats[i]->seq_no << packets_for_tx_stats[i]->start_time << "=======" << packets_for_tx_stats[i]->end_time << std::endl;

    add_to_event_queue(new PacketCreationEvent(start_time, p1)); 
    p1->sending_time = new_arrival_event;
    //tnext = tnext;
    

    add_to_event_queue(new PacketPushingEvent(new_arrival_event+3.2, p1, topology->hosts[j]->queue[0]));
    //std::cout << topology->hosts[j]->queue[0]->node_details.my_type << std::endl;
    
    
    if(params.debug==1){
    std::cout << " AT PACKETGEN <<< Packets sent from Host: "<< p1->src->id << " to Host: " <<p1->dst->id <<" with size "<< p1->size << ", sequence number " << p1->seq_no <<" start_time "<< p1->start_time <<" and sending time of "<< p1->sending_time<<  std::endl;
    		}
	
	}
}


  for (int j=2;j<3;j+=2){ // testing for single queue chaining
  //for (int j=0;j<params.num_hosts;j++){ 
   for (uint32_t i = 10; i < params.num_packets_to_run+10; i++){

    double new_arrival_event = new_arrival_event+arrival_time_unit;

//   std::cout<<"-------------------------------------------> "<< std::endl;
      int rand_num = jrand(1);
    std::cout << "j, j+1 " << j << "," << j+1 << std::endl;
    Packet *p1 = new Packet(start_time, i, 0, params.packet_size, topology->hosts[j], topology->hosts[1]);
    p1->start_time = 0 ;
    p1->end_time =0 ;
    p1->qid=j; // encoding the identification of queue for packet
    p1->src = topology->hosts[j];
    p1->dst = topology->hosts[1] ;
    std::cout << "p1->qid " << p1->qid << std::endl;
    //packets_for_tx_stats.push_back(p1);// array for stats
    packets_for_tx_stat[j].push_back(p1);// array for stats

    //std::cout<< p1->seq_no << "\t" << p1->src->id << "," << p1->dst->id << "\t"<< p1->size << "\t" << p1->start_time << "\t" << p1->end_time << std::endl;

    //std::cout<< "PRINTINGGGGGGGG "<< params.num_hosts <<  std::endl;
    //std::cout<< packets_for_tx_stats[i]->seq_no << packets_for_tx_stats[i]->start_time << "=======" << packets_for_tx_stats[i]->end_time << std::endl;

    add_to_event_queue(new PacketCreationEvent(start_time, p1));
    p1->sending_time = new_arrival_event;
    //tnext = tnext;


    add_to_event_queue(new PacketPushingEvent(new_arrival_event+3.2, p1, topology->hosts[j]->queue[0]));
    //std::cout << topology->hosts[j]->queue[0]->node_details.my_type << std::endl;


    if(params.debug==1){
    std::cout << " AT PACKETGEN <<< Packets sent from Host: "<< p1->src->id << " to Host: " <<p1->dst->id <<" with size "<< p1->size << ", sequence number " << p1->seq_no <<" start_time "<< p1->start_time <<" and sending time of "<< p1->sending_time<<  std::endl;
            }

    }
}*/

     add_to_event_queue(new StartPacketGenEvent(3, 200));
     add_to_event_queue(new StartPacketGenEvent(400, 550));
     add_to_event_queue(new StartPacketGenEvent(600, 700));
     add_to_event_queue(new StartPacketGenEvent(900, 1000));
    // add_to_event_queue(new StopPacketGenEvent());
    add_to_event_queue(new LoggingEvent (200000000));
/*    std::cout << "Number of 1s is "<< number_of_1s << std::endl;
    std::cout << "Number of 3s is "<< number_of_3s << std::endl;*/
    run_scenario();

}


