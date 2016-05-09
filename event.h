#ifndef EVENT_H
#define EVENT_H


#include <iostream>
#include <queue>
#include <vector>
#include "packet.h"
#include "random_variable.h"


#define PACKET_ARRIVAL_AT_LINK 0
#define PACKET_DEPARTED_FROM_LINK 1
#define PACKET_ARRIVAL_AT_SWITCH 2
#define PACKET_DEPARTURE_FROM_SWITCH 3
#define PACKET_CREATION_EVENT 4
#define SWITCH_ARBITRATION 5
#define PACKET_SERVICE_EVENT 6
#define PACKET_PUSHING_EVENT 7
#define NEXT_HOP_EVENT 8
 
#define LOGGING 9
#define STATS 10
#define TOKEN 11
#define SWITCH_SCHEDULING_EVENT 12
#define STARTGEN_EVENT 13


class event {
public:
    // Construct sets time of event.
    event(uint32_t type ,double t);
    virtual ~event();
    // Execute event by invoking this method.
    virtual void process_event () = 0;
    uint32_t type;
    double time;
    bool cancelled; 
    uint32_t unique_id;
    static uint32_t instance_count;  
  		
};

/*struct EventComparator {
    bool operator() (const event * left, const event * right) const {
        return left->time > right->time;
    }
};*/


template<typename Event>
struct EventComparator {
  std::less<int> time_compare; // time_type hopefully is self-describing ...
  bool operator()(Event * left, Event * right) const {
    if (time_compare(left->time, right->time)) {
     // std::cout << "False Type: " << left->type << "\t" << right->type  << "\t" << "Time: " << left->time << "\t" << right->time  << " left-less " << std::endl;
      return false;
    }
    if (time_compare(right->time, left->time)) {
     // std::cout << "True Type: " << left->type << "\t" << right->type  << "\t" << "Time: " << left->time << "\t" << right->time  << "    right-less " << std::endl;
      return true;
    }
     //1=arriveEvent 3=leaveEvent
    if ((((left->type == 6) && (right->type == 7))||
	((left->type == 7) && (right->type == 6)))&& (left->time ==right->time))
            {
           //std::cout << "Time is equal, need to check the events" << std::endl;
           //std::cout << left->type << " \t "<< right->type << std::endl;
           {
                if((left->type == 6) && (right->type == 7)) {
                   // std::cout << "Trigger" << std::endl;
                //std::cout << "After" << left->type << " \t "<< right->type << std::endl;
                    return true;
                }
                else { //if ((left->type == 1) && (right->type == 3))

                    //std::cout << "Trigger else" << std::endl;
                    //return false;
                }
                    //return false;
          //return true;  
            }

   // if (left->type == 1 && right->type == 3) {
     //   std::cout << "Time: " << time  << "     arriveEvent-leaveEvent: " << std::endl;
     // return true;
   // }
    return false;
  }
}
};


class PacketCreationForInitializationEvent : public event {
    public:
        PacketCreationForInitializationEvent(
                double time,
                Host *src,
                Host *dst,
                RandomVariable *nv_bytes,
                RandomVariable *nv_intarr
                );
        ~PacketCreationForInitializationEvent();
        void process_event();
        Host *src;
        Host *dst;
        RandomVariable *nv_bytes;
        RandomVariable *nv_intarr;
};

class PacketCreationEvent : public event {
    public:
        PacketCreationEvent(double time, Packet *packet);
        ~PacketCreationEvent();
        void process_event();
        Packet *packet;
};


class PacketPushingEvent : public event {
    public:
        PacketPushingEvent(double time, Packet *packet, Queue *queue);
        ~PacketPushingEvent();
        void process_event();
        Packet *packet;
        Queue *queue;
};


class PacketServiceEvent : public event {
    public:
        PacketServiceEvent(double time, Packet *packet, Queue *queue);
        ~PacketServiceEvent();
        void process_event();
        Packet *packet;
        Queue *queue;
};

class FindNextHopEvent : public event {
    public:
        FindNextHopEvent(double time, Packet *packet, Queue::typenid node_details ); 
        ~FindNextHopEvent();
        void printdetails();
        void process_event();
        Packet *packet;
	    Queue::typenid local_node_details;
};


class PacketEnteringLinkEvent : public event {
    public:
        PacketEnteringLinkEvent(double time, Packet *packet, Queue::typenid next_hop);
        ~PacketEnteringLinkEvent();
        void process_event();
        Packet *packet;
        Queue::typenid local_node_details;
};

class PacketDepartingLinkEvent : public event {
    public:
        PacketDepartingLinkEvent(double time, Packet *packet, Queue::typenid next_hop);
        ~PacketDepartingLinkEvent();
        void process_event();
        Packet *packet;
        Queue::typenid local_node_details;

};

class PacketEnteringSwitchEvent : public event {
    public:
        PacketEnteringSwitchEvent(double time, Packet *packet, Queue::typenid next_hop);
        ~PacketEnteringSwitchEvent();
        void process_event();
        Packet *packet;
        Queue::typenid local_node_details;

};

class PacketDepartingSwitchEvent : public event {
    public:
        PacketDepartingSwitchEvent(double time, Packet *packet, Queue::typenid next_hop);
        ~PacketDepartingSwitchEvent();
        void process_event();
        Packet *packet;
        Queue::typenid local_node_details;
};


class SwitchArbitration : public event {
    public:
        SwitchArbitration(double time, Packet *packet);
        ~SwitchArbitration();
        void process_event();
        Packet *packet;

};

class SwitchSchedulingEvent : public event {
    public:
        SwitchSchedulingEvent(double time, Packet *packet, Queue::typenid node_details);
        ~SwitchSchedulingEvent();
        void process_event();
        Packet *packet;
        Queue::typenid local_node_details;

};

class StartPacketGenEvent : public event {
    public:
        StartPacketGenEvent(double time, double end_time);
        ~StartPacketGenEvent();
        void process_event();
        double end_time ; 

};

class StopPacketGenEvent : public event {
    public:
        StopPacketGenEvent(double time);
        ~StopPacketGenEvent();
        void process_event();

};
// Have to declare all my events here 
class LoggingEvent : public event {
    public:
        LoggingEvent(double time);
        LoggingEvent(double time, double ttl);
        ~LoggingEvent();
        void process_event();
        double ttl;
};

class StatsEvent : public event {
    public:
        StatsEvent(double time);
        ~StatsEvent();
        void process_event();
};

class TokenEvent : public event {
    public:
        TokenEvent(double time, Packet *packet);
        ~TokenEvent();
        void process_event();
        Packet *packet;
};



#endif
