#ifndef PACKET_GEN_H
#define PACKET_GEN_H

#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdint.h>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <set>
#include "math.h"
#include "assert.h"


#include "packet.h"
#include "event.h"
#include "node.h"
#include "topology.h"
#include "queue.h"
#include "random_variable.h"
#include <fstream>
#include <iostream>

#include "factory.h"
#include "params.h"


extern Topology *topology;
extern double current_time;
//extern std::priority_queue<event *, std::vector<event *>, EventComparator> event_queue;
extern std::priority_queue<event*, std::vector<event*>, EventComparator<event> > event_queue;
extern std::deque<Packet *> packets_to_schedule;
extern std::deque<event *>  packet_arrivals;
extern DCExpParams params;


extern void add_to_event_queue(event *);
extern uint32_t get_event_queue_size();

extern double start_time;
extern double get_current_time();

class PacketGenerator {
public:
    uint32_t num_packets;
    Topology *topo;
    std::string filename;

    PacketGenerator(uint32_t num_packets, Topology *topo, std::string filename);
    virtual void write_packets_to_file(std::deque<Packet*> packets, std::string filename);
    virtual void make_packets();
    virtual void write_pkt_file(std::deque<Packet *> packets,std::string filename);
};

class PoissonPacketGenerator : public PacketGenerator {
public:
    PoissonPacketGenerator(uint32_t num_packets, Topology *topo, std::string filename);
    virtual void make_packets();
};

class PacketReader : public PacketGenerator {
public:
    PacketReader(uint32_t num_packets, Topology *topo, std::string filename);
    virtual void make_packets();
};

class CustomCDFPacketGenerator : public PacketGenerator {
public:
    CustomCDFPacketGenerator(uint32_t num_packets, Topology *topo, std::string filename, std::string interarrivals_cdf_filename);
    virtual void make_packets();

    std::string interarrivals_cdf_filename;
private:
    std::vector<EmpiricalRandomVariable*>* makeCDFArray(std::string fn_template, std::string filename);
};


class PermutationTM : public PacketGenerator {
public:
    PermutationTM(uint32_t num_packets, Topology *topo, std::string filename);
    virtual void make_packets();

};


#endif
