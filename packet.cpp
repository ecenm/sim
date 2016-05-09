#include "packet.h"

uint32_t Packet::instance_count = 0;

Packet::Packet(
        double sending_time, 
        uint32_t seq_no, 
        uint32_t pf_priority,
        uint32_t size,
	/*unsigned long long start_time,
	unsigned long long end_time,*/
	Host *src,
	Host *dst
    ) {
    this->m_fbe_time = m_fbe_time; // first bit entering time
    this->m_lbe_time = m_lbe_time; // last bit entering time
    this->m_fbl_time = m_fbl_time; // first bit leaving time
    this->m_lbl_time = m_lbl_time; // last bit leaving time 
    this->sending_time = sending_time;
    this->seq_no = seq_no;
    this->pf_priority = pf_priority;
    this->size = size;
    this->start_time = start_time;
    this->end_time = end_time;
    this->src = src;
    this->dst = dst;
    this->starting_time = starting_time;
    this->departure_time = departure_time;
    this->fbe_time = fbe_time; // first bit entering time
    this->lbe_time = lbe_time; // last bit entering time
    this->fbl_time = fbl_time; // first bit leaving time
    this->lbl_time = lbl_time; // last bit leaving time 
    this->qsize_we = qsize_we; // queue size when entering in packets
    this->qsize_wl = qsize_wl; // queue size when leaving in packets
    this->qsize_we_b = qsize_we_b; // queue size when entering in bytes
    this->qsize_wl_b = qsize_wl_b; // queue size when leaving in bytes
    this->qid=qid; // q id for packet to store
    this->dropped_pkts_we = dropped_pkts_we;
    this->dropped_pkts_wl = dropped_pkts_we;

    this->type = NORMAL_PACKET;
    this->unique_id = Packet::instance_count++;
    this->total_queuing_delay = 0;
}

PlainAck::PlainAck(uint32_t seq_no_acked, uint32_t size, Host* src, Host *dst) : Packet(0, seq_no_acked, 0, size, src, dst) {
    this->type = ACK_PACKET;
}

Ack::Ack(uint32_t seq_no_acked, std::vector<uint32_t> sack_list, uint32_t size, Host* src, Host *dst) : Packet(0,seq_no_acked, 0, size, src, dst) {
    this->type = ACK_PACKET;
    this->sack_list = sack_list;
}

