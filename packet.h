#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>
#include "node.h"

#define NORMAL_PACKET 0
#define ACK_PACKET 1



class Packet {

    public:
        Packet(double sending_time, uint32_t seq_no, uint32_t pf_priority,
                uint32_t size, /*unsigned long long start_time, unsigned long long end_time,*/ 
		Host *src, Host *dst);
	
	        double sending_time;
        double starting_time;
        double departure_time;
    	double m_fbe_time; // first bit entering time
    	double m_lbe_time; // last bit entering time
    	double m_fbl_time; // first bit leaving time
    	double m_lbl_time; // last bit leaving time 
        double fbe_time; // first bit entering time
    	double lbe_time; // last bit entering time
    	double fbl_time; // first bit leaving time
    	double lbl_time; // last bit leaving time 
        double qsize_we; // queue size when entering
    	double qsize_wl; // queue size when leaving
        double qsize_we_b; // queue size when entering
    	double qsize_wl_b; // queue size when leaving
        uint32_t qid; // queue id (location for packet to store)
        uint32_t dropped_pkts_we;
        uint32_t dropped_pkts_wl;
        uint32_t seq_no;
        uint32_t pf_priority;
        uint32_t size;
    	Host *src;
    	Host *dst;
        uint32_t unique_id;
        static uint32_t instance_count;
        int remaining_pkts_in_batch;
        int capability_seq_num_in_data;

        uint32_t type; // Normal or Ack packet
        double total_queuing_delay;
        double last_enque_time;

        int capa_data_seq;
	    double start_time;
	    double end_time;
};

class PlainAck : public Packet {
        public:
          PlainAck(uint32_t seq_no_acked, uint32_t size, Host* src, Host* dst);
};

class Ack : public Packet {
    public:
        Ack(uint32_t seq_no_acked, std::vector<uint32_t> sack_list,
                uint32_t size,
                Host* src, Host *dst);
        uint32_t sack_bytes;
        std::vector<uint32_t> sack_list;
};


#endif

