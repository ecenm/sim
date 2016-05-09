#include "factory.h"
#include <assert.h>
#include "packet.h"


/* Factory method to return appropriate queue */
Queue* Factory::get_queue(
        uint32_t id,// host id  
        double rate,
        uint32_t queue_size, 
        uint32_t type,
        double drop_prob, 
        int location,
        uint32_t input_bus_width,
        uint32_t input_work_rate,
        uint32_t output_bus_width,
        uint32_t output_work_rate,
        uint32_t i, // interface id, nqph
	uint32_t host_type
        ) { // Default drop_prob is 0.0

    switch(type) {
        case DROPTAIL_QUEUE:
            return new Queue(id, rate, queue_size, location, input_bus_width, input_work_rate, output_bus_width, output_work_rate, i, host_type);
    }
    assert(false);
    return NULL;
}

Host* Factory::get_host(
        uint32_t id, 
        double rate,
        uint32_t queue_size,
        uint32_t queue_type, 
        uint32_t host_type, 
        double drop_prob,
        int location,
        uint32_t input_bus_width,
        uint32_t input_work_rate,
        uint32_t output_bus_width,
        uint32_t output_work_rate,
        uint32_t nqph //number of queues per host
        ) { // Default drop_prob is 0.0
    switch(host_type) {
        case NORMAL_HOST:
            return new Host(id, rate, queue_size, queue_type, host_type, location, input_bus_width, input_work_rate, output_bus_width, output_work_rate, nqph);
            //return new Queue(id, rate, queue_size, location);
    }
    assert(false);
    return NULL;
}

Packet* Factory::get_packet(
        double start_time,
        uint32_t seq_no,
        uint32_t pf_priority,
        uint32_t size,
        Host *src,
        Host *dst
        ) { 
            return new Packet(start_time, seq_no, pf_priority,size,src,dst)  ;
    }

