#ifndef DEFINED_NODE
#define DEFINED_NODE

#include <iostream>
#include <string>
#include "queue.h"


#define HOST 10
#define SWITCH 12
#define LINK 99
#define SERVER 4
#define SINK 5

#define CORE_SWITCH 13
#define AGG_SWITCH 11
#define EPS 40        
#define CROSSBAR 50

#define COPPER_LINK 20
#define FIBER_LINK 21
#define SIMPLE_LINK 22

using namespace std;

class Node {
    public:
        Node(uint32_t id, uint32_t type);
        uint32_t id;
        uint32_t type;
};

class Host : public Node {
    public:
        Host(uint32_t id, double rate, uint32_t queue_size, uint32_t queue_type, uint32_t host_type, int location, uint32_t input_bus_width, uint32_t input_work_rate, uint32_t output_bus_width, uint32_t output_work_rate, uint32_t nqph);
        std::vector<Queue *> queue;
        //Queue *queue;
        int host_type;
//	typenid *node_details;
};

class Sink : public Node {
    public:
        Sink(uint32_t id, uint32_t sink_type);
        int sink_type;
};

class SimpleSink : public Sink {
    public:
	Queue::typenid node_details;
        SimpleSink(uint32_t id);
        //void set_src_dst(Node *src, Node *dst);
        void set_src_dst(Queue::typenid src, Queue::typenid dst);
	void printdetails();
};

class Crossbar : public Node {
    public:
        Crossbar(uint32_t id, uint32_t crossbar_type);
        int crossbar_type;
};

class SimpleCrossbar : public Crossbar{
    public:
	Queue::typenid node_details;
        SimpleCrossbar(uint32_t id);
        //void set_src_dst(Node *src, Node *dst);
        //void set_src_dst(Queue::typenid src, Queue::typenid dst);
	//void printdetails();
};



class Link : public Node {
    public:
        Link(uint32_t id, uint32_t link_type);
        Queue *queue;
        int link_type;
};

class CopperLink : public Link {
    public:
        CopperLink(uint32_t id, double rate, uint32_t queue_type);
};

class FiberLink : public Link {
    public:
        FiberLink(uint32_t id, double rate, uint32_t queue_type);
};

class SimpleLink : public Link {
    public:
	Queue::typenid node_details;
        SimpleLink(uint32_t id);
        void set_src_dst(Queue::typenid src, Queue::typenid dst);
        void set_delay(double td, double pd);
        double pd, td, totd;
        uint32_t src_id, dst_id, src_type, dst_type;
};



class Switch : public Node {
    public:
        Switch(uint32_t id, uint32_t switch_type);
        uint32_t switch_type;
        std::vector<Queue *> queues;
};

class Eps: public Switch 
{
	public:
		Eps(uint32_t id, uint32_t nq, double rate, uint32_t queue_type);
};



class CoreSwitch: public Switch 
{
	public:
		CoreSwitch(uint32_t id, uint32_t nq, double rate, uint32_t queue_type);
};

class AggSwitch: public Switch 
{
	public:
		AggSwitch(uint32_t id, uint32_t nq1, double r1, uint32_t nq2, double r2, uint32_t queue_type);
};

// My definitions 

class l2switch
{
    private:
        int id;
    public:
        int in_port;
        int out_port;
        int switching_latency;
        l2switch():switching_latency(50),in_port(4),out_port(4){};
        Queue *queue;
//		string name;
//		void recv_pkt(packet pkt);

};


class l2switch_optical: public l2switch
{
	private:
		int id;
	public:
		int in_port,out_port;
		int switching_latency;
		l2switch_optical():switching_latency(100),in_port(4),out_port(4){}
		Queue *queue;

//		string name;
//		packet pkt;
//		int number_of_ports;
//		void set_l2switch(int id, string name, int number_of_ports, int switching_latency);
//		void send_pkt(packet pkt, int port);
//		void display_send_pkt(packet pkt);
//		void display_recv_pkt(packet pkt);
//		void recv_pkt(packet pkt);

};

class l2switch_hybrid: public l2switch
{
	private:
		int id;
	public:
		int in_port;
		int out_port;
		int switching_latency;
		l2switch_hybrid():switching_latency(150),in_port(4),out_port(4){}
		Queue *queue;

//		string name;
//		packet pkt;
//		int number_of_ports;
//		void set_l2switch(int id, string name, int number_of_ports, int switching_latency);
//		void send_pkt(packet pkt, int port);
//		void display_send_pkt(packet pkt);
//		void display_recv_pkt(packet pkt);
//		void recv_pkt(packet pkt);

};


#endif
