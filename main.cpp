#include <iostream>
#include <string>
#include <cstdlib>

#include "node.h"
#include "queue.h"
#include "packet.h"
#include "event.h"
#include "topology.h"
#include "random_variable.h"
#include "factory.h"
#include "params.h"


#include <vector> // To add more number of objects(packets)
using namespace std;
extern DCExpParams params;

// ------------------ Time for simulation -----------------------------
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

double current_time = 0 ;
//double start_time = -1 ;
double start_time = 0 ;
//uint32_t packet_pushed = 0;
//uint32_t count = 0;

Topology* topology;
//std::priority_queue<event*, std::vector<event*>, EventComparator> event_queue;
std::priority_queue<event*, std::vector<event*>, EventComparator<event> > event_queue;
std::deque<Packet*> packets_to_schedule;
//std::vector<Packet*> packets_to_switch;
std::deque<event*> packet_arrivals;
std::vector<Packet*> packets_for_rx_stats;
std::vector<Packet*> packets_for_tx_stats;
//std::vector< std::vector<Packet*> > packets_for_rx_stat();
//std::vector< std::vector<Packet*> > packets_for_tx_stat();
//std::vector< std::vector<Packet*> > packets_to_switch();
vector<Packet*>::iterator it;
vector<Packet*>::iterator itt; 

//Queue *myqueue;
//std::cout <<"---------------> " << params.queue_size << std::endl;
//------Some methods to get useful details about event queue ---------

void add_to_event_queue(event* ev) {
    event_queue.push(ev);
}

uint32_t get_event_queue_size() {
	std::cout<<"EVENT_QUEUE_SIZE IS "<< event_queue.size()<< std::endl;
    return event_queue.size();
}

double get_current_time() {
    return current_time; // in us
}


void run_scenario() {
    // Packet Arrivals create new Packet arrivals
    // Add the first packet arrival
    //
   // std::cout << "Debug --- Running_Scenario" << std::endl;
    //myqueue = new Queue(0, 10, params.queue_size, 0);
    /*if (packet_arrivals.size() > 0) {
        add_to_event_queue(packet_arrivals.front());
        packet_arrivals.pop_front();
    }*/
    get_event_queue_size();
    int last_evt_type = -1;
    int same_evt_count = 0;
    //while (event_queue.size() > 0) {
    while (!event_queue.empty()) {
        event *ev = event_queue.top();
        event_queue.pop();
        current_time = ev->time;
      if (start_time < 0) {
            start_time = current_time;
        }
        if (ev->cancelled) {
            delete ev; //TODO: Smarter
            continue;
        }
        ev->process_event();
        delete ev;
    if(params.debug ==1){
    get_event_queue_size();
    }
//        if(last_evt_type == ev->type && last_evt_type != 9)
//            same_evt_count++;
//        else
//            same_evt_count = 0;
//
//        last_evt_type = ev->type;

//        if(same_evt_count > 1000){
//            std::cout << "Ended event dead loop. Type:" << last_evt_type << "\n";
//            break;
//        }
    }
}

extern void run_experiment(int argc, char** argv, uint32_t exp_type);


// --------------- Main function ---------------------------------------------- 

int main(int argc, char ** argv)
{

    time_t start_time;
    time(&start_time);

    //srand(time(NULL));
    srand(0);
    std::cout.precision(15);

    uint32_t exp_type = atoi(argv[1]);
    switch (exp_type) {
        case DEFAULT_EXP:
            run_experiment(argc, argv, exp_type);
            break;
        default:
            assert(false);
    }
    packets_for_rx_stats.size();

   if(params.debug ==1){
    std::cout << "PACKETS TO SCHEDULE " <<packets_to_schedule.size()<<std::endl;
    std::cout << "FINAL_STATS -------------------------------------------------"<< std::endl;


    //myqueue->getsize();
    //myqueue->get_num_of_packets();
    std::cout << "FINAL_STATS -------------------------------------------------"<< std::endl;
    }
    time_t end_time;
    time(&end_time);
    double duration = difftime(end_time, start_time);
    if(params.debug==1){
    cout << currentDateTime() << " Simulator ended. Execution time: " << duration << " seconds\n";
    }
}
    

