#include <climits>
#include <iostream>
#include <cstdlib>
#include "assert.h"
#include <algorithm>


#include "queue.h"
#include "packet.h"
#include "params.h"

extern DCExpParams params;
uint32_t Queue::instance_count = 0;

/* Queues */
Queue::Queue(uint32_t id, double rate, uint32_t limit_bytes, int location, uint32_t input_bus_width, uint32_t input_work_rate, uint32_t output_bus_width, uint32_t output_work_rate, uint32_t i, uint32_t host_type) {
    this->id = id;
    this->unique_id = Queue::instance_count++;
    this->rate = rate; // in bps
    this->limit_bytes = limit_bytes;
    this->bytes_in_queue = 0;
    this->packets_in_queue = 0;
    this->busy = false;
    //this->packet_propagation_event = NULL;
    this->location = location;

    this->propagation_delay = 10;
    this->p_arrivals = 0; this->p_departures = 0;
    this->b_arrivals = 0; this->b_departures = 0;

    this->pkt_drop = 0;
    this->bytes_dropped = 0;
    this->spray_counter=std::rand();
    this->packet_transmitting = NULL;
    this->num_of_packets = 0;
   
    this->i = i; 
    this->node_details.my_type = host_type; // Need to parameters for HOST and SWITCH
    this->node_details.my_id = id; // host id
    this->node_details.my_sub_id = i; // instance number, interface, nqph
   
    this->input_bus_width= input_bus_width;
    this->input_work_rate= input_work_rate;

    this->output_bus_width= output_bus_width;
    this->output_work_rate= output_work_rate;

    // Only for temporary, doesn't work when packet size changes. 
    this->input_packet_size_in_time = (1.0/double(this->input_work_rate))* ceil(double(params.packet_size)/double(this->input_bus_width)); // packet_size is fixed
    this->output_packet_size_in_time = (1.0/double(this->output_work_rate))* ceil(double(params.packet_size)/double(this->output_bus_width));


    //this->node_details = node_details; 
}

void Queue::getsize(){
std::cout << "************************************************************" << std::endl;
std::cout << " Bytes in queue: " << bytes_in_queue <<  " Packets dropped: " << pkt_drop << std::endl;
std::cout << "************************************************************" << std::endl;
//return 0;
}
void Queue::enque(Packet *packet) {
    p_arrivals += 1;
    b_arrivals += packet->size;
    if (bytes_in_queue + packet->size <= limit_bytes) {
        packets.push_back(packet);
        bytes_in_queue += packet->size;
        packets_in_queue += 1;
    } else {
        pkt_drop++;
        drop(packet);
    }
}

Packet *Queue::deque() {
    if (bytes_in_queue > 0) {
        Packet *p = packets.front();
        packets.pop_front();
        bytes_in_queue -= p->size;
        if(packets_in_queue > 0){
            packets_in_queue -= 1;
        }
        p_departures += 1;
        b_departures += p->size;
        return p;
    }
    return NULL;
}

void Queue::drop(Packet *packet) {
	bytes_dropped += packet->size;
    packets_dropped += 1;
    //delete packet;
    //packet = NULL;
   //std::cout<< "****************************" <<std::endl;
}

double Queue::get_transmission_delay(uint32_t size) {
    return size * 8.0 / rate;
}

void Queue::get_num_of_packets() {
    num_of_packets=bytes_in_queue/params.packet_size;
    std::cout << "number_of_packets " << num_of_packets;
}


void Queue::set_src_dst(Queue::typenid src, Queue::typenid dst) {
        //this->src = src;
        //this->dst = dst;
        this->node_details.src_type = src.my_type;
        this->node_details.src_id = src.my_id;
        this->node_details.src_sub_id = src.my_sub_id;
        this->node_details.dst_type = dst.my_type;
        this->node_details.dst_id = dst.my_id;
        this->node_details.dst_sub_id = dst.my_sub_id;
        
}

void Queue::printdetails()
{

    std::cout << input_bus_width << std::endl;
    std::cout << input_work_rate << std::endl;

    std::cout << output_bus_width<< std::endl;
    std::cout << output_work_rate<< std::endl;

    std::cout << input_packet_size_in_time << std::endl;
    std::cout << output_packet_size_in_time << std::endl;

    std::cout << node_details.my_type << std::endl;
    std::cout << node_details.my_id << std::endl;
    std::cout << node_details.my_sub_id << std::endl;




}
