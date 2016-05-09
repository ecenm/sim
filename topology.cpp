#include "topology.h"
#include "params.h"

extern DCExpParams params;

Topology::Topology() {}

SimpleTopology::SimpleTopology(
       uint32_t num_hosts,
       double bandwidth, 
       uint32_t queue_type,
       uint32_t num_myq
       ): Topology() {
    this->num_hosts = num_hosts;
    this->num_myq = num_myq;
    double c1= bandwidth;

   // Create hosts with their queues
    
        hosts.push_back(Factory::get_host(0,0, params.queue_size, params.queue_type, params.host_type,0,0,32,10,32,10,params.nqph)); // TODO Parameterize Rate and drop rate
    
        hosts.push_back(Factory::get_host(1,0, params.queue_size, params.queue_type, params.host_type,0,1,32,10,32,2,params.nqph)); // TODO Parameterize Rate and drop rate
        
        hosts.push_back(Factory::get_host(2,0, params.queue_size, params.queue_type, params.host_type,0,2,32,10,32,10,params.nqph)); // TODO Parameterize Rate and drop rate
        
        hosts.push_back(Factory::get_host(3,0, params.queue_size, params.queue_type, params.host_type,0,3,32,10,32,2,params.nqph)); // TODO Parameterize Rate and drop rate

        for (uint32_t i=0; i < num_myq; i++) {
            for (uint32_t j=0; j < params.nqph; j++) { // nqph - number of queues per host
            std::cout<< "host stats  : "<< i << "\t" << j << std::endl;
            hosts[i]->queue[j]->printdetails();
            }
    }

    // Create EPS and pushing it to switch
    Eps* eps1 = new Eps(0,params.nqps,0,1); // nqps - number of queues per switch
    switches.push_back(eps1);

    std::cout << "num of queues in switches" << switches.size() << std::endl;

    SimpleCrossbar* cb = new SimpleCrossbar(0);
    crossbars.push_back(cb);

   for (uint32_t j=0; j < params.nqps; j++) {
    switches[0]->queues[j]->printdetails();
    //std::cout << switches[0]->queues[j]->node_details.my_sub_id << std::endl;
   }
  
	  
    // Create simple links and sinks 

   for (uint32_t i=0; i < 4; i++) { // need to parameterize number of links 

    SimpleLink* sl = new SimpleLink(i);
    slinks.push_back(sl); // TODO make generic

    
   }

   
   for (uint32_t i= 0; i< 2; i++) {
    SimpleSink* si = new SimpleSink(i); //sink
    sinks.push_back(si); 
   
   }


    // host0 q0 ------sl0------- sw0 q0
    //SimpleLink *sl0 = slinks[0];
    slinks[0]->set_src_dst(hosts[0]->queue[0]->node_details, switches[0]->queues[0]->node_details);
    slinks[2]->set_src_dst(hosts[2]->queue[0]->node_details, switches[0]->queues[2]->node_details);

    // sw0 q1 ------sl1------- host1 q0
    //SimpleLink *sl1 = slinks[1];
    slinks[1]->set_src_dst(switches[0]->queues[1]->node_details,hosts[1]->queue[0]->node_details);
    slinks[3]->set_src_dst(switches[0]->queues[3]->node_details,hosts[3]->queue[0]->node_details);

    sinks[0]->set_src_dst(hosts[1]->queue[0]->node_details, sinks[0]->node_details);
    sinks[1]->set_src_dst(hosts[3]->queue[0]->node_details, sinks[0]->node_details);

 
   hosts[0]->queue[0]->set_src_dst(hosts[0]->queue[0]->node_details, slinks[0]->node_details);
   hosts[2]->queue[0]->set_src_dst(hosts[2]->queue[0]->node_details, slinks[2]->node_details);

   hosts[1]->queue[0]->set_src_dst(slinks[1]->node_details, hosts[1]->queue[0]->node_details);
   hosts[3]->queue[0]->set_src_dst(slinks[3]->node_details, hosts[3]->queue[0]->node_details);


   switches[0]->queues[0]->set_src_dst(slinks[0]->node_details, crossbars[0]->node_details);
   switches[0]->queues[2]->set_src_dst(slinks[2]->node_details, crossbars[0]->node_details);

   switches[0]->queues[1]->set_src_dst(crossbars[0]->node_details, slinks[1]->node_details);
   switches[0]->queues[3]->set_src_dst(crossbars[0]->node_details, slinks[3]->node_details);





   std::cout << "*******************\n"<< std::endl;
   std::cout << "Configuration Details\n" << std::endl;
   std::cout << "*******************\n"<< std::endl;
   

   std::cout<< "[Node id]" <<  "\t"<<"src_type" << "\t"<<"src_id" << "\t"<< "src_q_id"  <<  "\t"<<"dst_type" <<  "\t"<<"dst_id" << "\t" << "dst_q_id"  <<  "\t"<<"my_type"  <<  "\t"<<"my_id" << "\t" << "my_q_id" << std::endl;
   
   std::cout<<"Hosts"<<std::endl;
    for (int i=0;i<4;i++){

      std::cout<<"[Host "<< i<<"]" <<  "\t"<<hosts[i]->queue[0]->node_details.src_type <<  "\t"<<hosts[i]->queue[0]->node_details.src_id << "\t"<<hosts[i]->queue[0]->node_details.src_sub_id  <<  "\t"<<hosts[i]->queue[0]->node_details.dst_type <<  "\t"<<hosts[i]->queue[0]->node_details.dst_id   << "\t"<<hosts[i]->queue[0]->node_details.dst_sub_id   << "\t"<<hosts[i]->queue[0]->node_details.my_type  <<  "\t"<<hosts[i]->queue[0]->node_details.my_id    <<   "\t"<<hosts[i]->queue[0]->node_details.my_sub_id  <<  std::endl;
    }


    std::cout<<"Links"<<std::endl;
    for (int i=0;i<4;i++){

    std::cout<< "[Link "<<i<<"]" <<  "\t"<< slinks[i]->node_details.src_type <<  "\t"<<slinks[i]->node_details.src_id  <<  "\t" << slinks[i]->node_details.src_sub_id <<  "\t"<<slinks[i]->node_details.dst_type <<  "\t"<<slinks[i]->node_details.dst_id  << "\t"<< slinks[i]->node_details.dst_sub_id  <<  "\t"<<slinks[i]->node_details.my_type  <<  "\t"<<slinks[i]->node_details.my_id  << "\t"<<slinks[i]->node_details.my_sub_id << std::endl;
    }
    

    std::cout<<"Switches"<<std::endl;
    for (int i=0;i<4;i++){

    std::cout<< "[Swi_Q "<< i<<"]" <<  "\t"<< switches[0]->queues[i]->node_details.src_type <<  "\t"<<switches[0]->queues[i]->node_details.src_id  <<  "\t" << switches[0]->queues[i]->node_details.src_sub_id <<  "\t"<<switches[0]->queues[i]->node_details.dst_type <<  "\t"<<switches[0]->queues[i]->node_details.dst_id  << "\t"<< switches[0]->queues[i]->node_details.dst_sub_id  <<  "\t"<<switches[0]->queues[i]->node_details.my_type  <<  "\t"<<switches[0]->queues[i]->node_details.my_id  << "\t"<<switches[0]->queues[i]->node_details.my_sub_id << std::endl;
    }

    //hosts[1]->queue->node_details.src_type = 22 ;
    //hosts[1]->queue->node_details.src_id   = 0 ;
    //hosts[1]->queue->node_details.dst_type = 7 ;
    //hosts[1]->queue->node_details.dst_id   = 1 ;
   // hosts[1]->queue->node_details.my_type  = 7 ;
   // hosts[1]->queue->node_details.my_id    = 1 ;

    std::cout<<"Sink"<<std::endl;
    for (int i=0;i<2;i++){

std::cout<< "[Sink " << i <<"]" <<  "\t"<<sinks[i]->node_details.src_type <<  "\t"<<sinks[i]->node_details.src_id   <<  "\t"<<sinks[i]->node_details.src_sub_id << "\t"<<sinks[i]->node_details.dst_type <<  "\t"<<sinks[i]->node_details.dst_id   <<  "\t"<<sinks[i]->node_details.dst_sub_id  << "\t"<<sinks[i]->node_details.my_type  <<  "\t"<<sinks[i]->node_details.my_id <<"\t"<< sinks[i]->node_details.my_sub_id << std::endl;
    }

    hosts[0]->queue[0]->printdetails();
    
    hosts[1]->queue[0]->printdetails();
	
    sinks[0]->printdetails();

	std::cout << ".............................."<< std::endl;

}

Queue::typenid SimpleTopology::get_next_hop(double time, Packet *p, Queue::typenid node_details) {

    if (node_details.dst_type == HOST) {	
	return hosts[node_details.dst_id]->queue[node_details.dst_sub_id]->node_details;	
	}	

    else if (node_details.dst_type == LINK) { //Because we use NODE
	
	return slinks[node_details.dst_id]->node_details;	

	}
	
    else if (node_details.dst_type == EPS) {
	return switches[node_details.dst_id]->queues[node_details.dst_sub_id]->node_details;
	}

    else if (node_details.dst_type == SINK) {

	return sinks[node_details.dst_id]->node_details;
	}

    else if (node_details.dst_type == CROSSBAR) {
        uint32_t pkt_dstn_id = p->dst->id;
        std::cout << pkt_dstn_id << std::endl;
	    return switches[0]->queues[pkt_dstn_id]->node_details;
    }

    else if ((node_details.dst_type != HOST) || (node_details.dst_type != LINK) || (node_details.dst_type != SINK)||(node_details.dst_type != EPS) || (node_details.dst_type != CROSSBAR))  
        {

        std::cout <<"Asserting NULL "<< std::endl;
        assert(false);
        //return NULL;
        }
}

