#ifndef QUEUE_H
#define QUEUE_H

#include <deque>
#include <stdint.h>
#include <vector>

#define DROPTAIL_QUEUE 1

class Packet;
class Node;
struct typenid; 

class Queue {
    public:
	struct typenid{
	 typenid() : src_type(0), src_id(0), src_sub_id(0), dst_type(0), dst_id(0), dst_sub_id(0), my_type(0), my_id(0), my_sub_id(0){}
         uint32_t src_type;
         uint32_t src_id;
         uint32_t src_sub_id;
         uint32_t dst_type;
         uint32_t dst_id;
         uint32_t dst_sub_id;
         uint32_t my_type;
         uint32_t my_id;
         uint32_t my_sub_id;
         } node_details; 

        Queue(uint32_t id, double rate, uint32_t limit_bytes, int location, uint32_t input_bus_width, uint32_t input_work_rate, uint32_t output_bus_width, uint32_t output_work_rate, uint32_t i, uint32_t host_type);
        void set_src_dst(Queue::typenid src, Queue::typenid dst);
        virtual void enque(Packet *packet);
        virtual Packet *deque();
        virtual void drop(Packet *packet);
        double get_transmission_delay(uint32_t size);
	    void getsize();
	    void get_num_of_packets();
        void printdetails();
        // Members
        uint32_t bus_width;
        uint32_t work_rate;
        
        uint32_t id;
        uint32_t unique_id;
        static uint32_t instance_count;
        double rate;
        uint32_t limit_bytes;
        std::deque<Packet *> packets;
        uint32_t bytes_in_queue;
        uint32_t packets_in_queue;
        bool busy;

        Packet* packet_transmitting;
        
	uint64_t b_arrivals, b_departures;
        uint64_t p_arrivals, p_departures;

        double propagation_delay;
        bool interested;

        uint64_t pkt_drop;
        uint64_t bytes_dropped;
        uint64_t packets_dropped;
        uint64_t spray_counter;
        
        uint32_t input_bus_width;
        double input_work_rate;
        double input_packet_size_in_time;

        uint32_t output_bus_width;
        double output_work_rate;
        double output_packet_size_in_time;

        uint32_t i; 
	uint32_t host_type;
        int location;
        Node *src;
        Node *dst;
	double num_of_packets;
	unsigned long long start_time;
	unsigned long long end_time;
};


#endif
