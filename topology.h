#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "queue.h"
#include "packet.h"
#include "node.h"
#include "factory.h"
#include "assert.h"

class Topology{
	public:             
        Topology();
        virtual Queue::typenid get_next_hop(double time, Packet *p, Queue::typenid node_details) = 0;
        //virtual double get_oracle_pct(Packet* p) = 0 ;

        uint32_t num_hosts;
        uint32_t num_myq;

        std::vector<Host *> hosts;
        std::vector<Switch *> switches;
        std::vector<FiberLink *> links;
        std::vector<SimpleLink *> slinks;
        std::vector<SimpleSink *> sinks;
        std::vector<SimpleCrossbar *> crossbars;
        //std::vector<Queue *> myq;
        //std::vector<Server *> servers;
};

class SimpleTopology: public Topology {
    public:
        SimpleTopology(uint32_t num_hosts, double bandwidth, uint32_t queue_type, uint32_t num_myq);
        virtual Queue::typenid get_next_hop(double time, Packet *p, Queue::typenid node_details);
        //virtual double get_oracle_pct(Packet *p);

        CoreSwitch* the_switch;    
};








#endif
