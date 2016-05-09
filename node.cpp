#include "node.h"
#include "factory.h"
#include "params.h"

extern DCExpParams params;


Node::Node(uint32_t id, uint32_t type) {
    this->id = id;
    this->type = type;
}

// TODO FIX superclass constructor

Host::Host(uint32_t id, double rate, uint32_t queue_size, uint32_t queue_type, uint32_t host_type, int location, uint32_t input_bus_width, uint32_t input_work_rate, uint32_t output_bus_width, uint32_t output_work_rate, uint32_t nqph) : Node(id, HOST) {
    for(uint32_t i=0;i<nqph;i++){
    this->host_type = HOST;
    queue.push_back(Factory::get_queue(id, rate, params.queue_size,1, 0, location, input_bus_width, input_work_rate, output_bus_width, output_work_rate,i,HOST));
    }
}

Sink::Sink(uint32_t id, uint32_t sink_type) : Node(id, SINK) {
    this->sink_type = sink_type;
}

Crossbar::Crossbar(uint32_t id, uint32_t crossbar_type) : Node(id, CROSSBAR) {
    this->crossbar_type = crossbar_type;
}


Link::Link(uint32_t id, uint32_t link_type) : Node(id, LINK) {
    this->link_type = link_type;
}

CopperLink::CopperLink(uint32_t id, double rate, uint32_t type) : Link(id, COPPER_LINK) {
    //queue = Factory::get_queue(id, rate, params.queue_size, type, 0, 0); fixit
    queue = Factory::get_queue(id, rate, params.queue_size, 1, 0, 0, 32, 10, 32, 4, 2, 99);
}

FiberLink::FiberLink(uint32_t id, double rate, uint32_t type) : Link(id, FIBER_LINK) {
    queue = Factory::get_queue(id, rate, params.queue_size, 1, 0, 0, 32, 10, 32, 4, 2, 99);
}

SimpleLink::SimpleLink(uint32_t id): Link(id, LINK){
        //Queue::typenid node_details= node_details;
        Queue::typenid node_details;
	this->id = id;
        this->td = 5.0; //TODO: This needs to be updated to be configurable
        this->pd = 5.0;
        this->node_details.my_type = LINK; // Need to parameters for HOST and SWITCH
        this->node_details.my_id = id;
        this->node_details.my_sub_id = 0;
        totd = this->td + this->pd ;
         //std::cout<<"td : "<< td << " pd : " << pd << " total delay is " << totd << std::endl;
}
    
void SimpleLink::set_src_dst(Queue::typenid src, Queue::typenid dst){

        /*this->src_type = src_type;
        this->dst_type = dst_type;
 
        this->src_id = src_id;
        this->dst_id = dst_id;*/

        this->node_details.src_type = src.my_type;
        this->node_details.src_id = src.my_id;
        this->node_details.src_sub_id = src.my_sub_id;
        this->node_details.dst_type = dst.my_type;
        this->node_details.dst_id = dst.my_id;
        this->node_details.dst_sub_id = dst.my_sub_id;

        //std::cout<<"src_id : "<< src_id << " is connected to " << "dst_id : " << dst_id <<  std::endl;
        //std::cout<<"src_type : "<< src_type << " is connected to " << "dst_type : " << dst_type <<  std::endl;

}

void SimpleLink::set_delay(double td, double pd){
//    this->td = 5.0; //TODO: This needs to be updated to be configurable
//    this->pd = 5.0;
//    totd = this->td + this->pd ;
   std::cout<<"td : "<< td << " pd : " << pd << " total delay is " << totd << std::endl;
}


SimpleSink::SimpleSink(uint32_t id): Sink(id, SINK){
        //Queue::typenid node_details= node_details;
        Queue::typenid node_details;
	this->id = id;
        this->node_details.my_type = SINK; // Need to parameters for HOST and SWITCH
        this->node_details.my_id = id;
        this->node_details.my_sub_id = 0;


}
    
void SimpleSink::set_src_dst(Queue::typenid src, Queue::typenid dst){


        this->node_details.src_type = src.my_type;
        this->node_details.src_id = src.my_id;
        this->node_details.src_sub_id = src.my_sub_id;
        this->node_details.dst_type = dst.my_type;
        this->node_details.dst_id = dst.my_id;
        this->node_details.dst_sub_id = dst.my_sub_id;

        //std::cout<<"src_id : "<< src_id << " is connected to " << "dst_id : " << dst_id <<  std::endl;
        //std::cout<<"src_type : "<< src_type << " is connected to " << "dst_type : " << dst_type <<  std::endl;

}

void SimpleSink::printdetails(){


        std::cout << node_details.src_type << std::endl ;
        std::cout << node_details.src_id   << std::endl ;
        std::cout << node_details.src_sub_id   << std::endl ;
        std::cout << node_details.dst_type << std::endl ;
        std::cout << node_details.dst_id   << std::endl ;
        std::cout << node_details.dst_sub_id   << std::endl ;
        std::cout << node_details.my_type << std::endl ;
        std::cout << node_details.my_id   << std::endl ;
        std::cout << node_details.my_sub_id   << std::endl ;


        //std::cout<<"src_id : "<< src_id << " is connected to " << "dst_id : " << dst_id <<  std::endl;
        //std::cout<<"src_type : "<< src_type << " is connected to " << "dst_type : " << dst_type <<  std::endl;

}

SimpleCrossbar::SimpleCrossbar(uint32_t id): Crossbar(id, CROSSBAR){
        //Queue::typenid node_details= node_details;
    Queue::typenid node_details;
    //std::vector<Queue::typenid> nlist(4,0);
	this->id = id;
        this->node_details.my_type = CROSSBAR; // Need to parameters for HOST and SWITCH
        this->node_details.my_id = id;
        this->node_details.my_sub_id = 0;


}
// TODO FIX superclass constructor
Switch::Switch(uint32_t id, uint32_t switch_type) : Node(id, SWITCH) {
    this->switch_type = switch_type;
}


Eps::Eps(uint32_t id, uint32_t nq, double rate, uint32_t type) : Switch(id, EPS) {
    for (uint32_t i = 0; i < nq; i++) {
      queues.push_back(Factory::get_queue(id, rate, params.queue_size, 1, 0, 2, 32, 10, 32, 10,i,switch_type)); 
      // needs to be configurable
      // need to think about queue type, when we develop EPS 

//    queue.push_back(Factory::get_queue(id, rate, params.queue_size,1, 0, location, input_bus_width, input_work_rate, output_bus_width, output_work_rate,i));
    }
    // crossbar()
}



CoreSwitch::CoreSwitch(uint32_t id, uint32_t nq, double rate, uint32_t type) : Switch(id, CORE_SWITCH) {
    for (uint32_t i = 0; i < nq; i++) {
        queues.push_back(Factory::get_queue(i, rate, params.queue_size, type, 0, 2, 32, 10, 32, 4,2,40));
    }
}

//nq1: # host switch, nq2: # core switch
AggSwitch::AggSwitch(
        uint32_t id,
        uint32_t nq1,
        double r1,
        uint32_t nq2,
        double r2,
        uint32_t type
        ) : Switch(id, AGG_SWITCH) {
    for (uint32_t i = 0; i < nq1; i++) {
        queues.push_back(Factory::get_queue(i, r1, params.queue_size, type, 0, 3, 32, 10, 32, 4, 2,40));
    }
    for (uint32_t i = 0; i < nq2; i++) {
        queues.push_back(Factory::get_queue(i, r2, params.queue_size, type, 0, 1, 32, 10, 32, 4, 2,40));
    }
}

//l2switch::l2switch:port(3),switching_latency(params.queue_size0){}
