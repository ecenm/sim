/*-
 * Copyright (c) 2016 Neelakandan.Manihatty-Bojan
 * All rights reserved.
 *
 * 
 *  File:
 *        params.cpp
 *
 *
 *  Author:
 *        Neelakandan.Manihatty-Bojan
 * 		
 *  Description:
 *        Read and update parameters from configuration files
 *
 */

#include "params.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>

DCExpParams params;


//TODO: change config file strcture
// One idea:
// Folder structure:
// --Config
//	-- queues
//		-- qtype1.cfg
//		-- qtype<n>.cfg
//	-- links
//		-- linktype1.cfg
//		-- linktype<n>.cfg
//	-- host
//		-- hosttype1.cfg
//		-- hosttype<n>.cfg
//	-- switch
//		-- swtype1.cfg
//		-- swtypen.cfg
// 	-- global
//		-- general.cfg
//		-- TBD
//	-- stimulus
//		-- stimtype1.cfg
//		-- stimtype<n>.cfg
//	-- misc
//		-- TBD

/* Read and parse parameters from a config file */
void read_experiment_parameters(std::string conf_filename, uint32_t exp_type) {
    //std::cout << conf_filename<<std::endl;
    //std::cout << exp_type<<std::endl;
    std::ifstream input(conf_filename);
    std::string line;
    std::string key;
    params.interarrival_cdf = "none";
    params.permutation_tm = 0;
    while (std::getline(input, line)) {
        std::istringstream lineStream(line);
        if (line.empty()) {
            continue;
        }


        lineStream >> key;
        assert(key[key.length()-1] == ':');
        key = key.substr(0, key.length()-1);
        if (key == "init_cwnd") {
            lineStream >> params.initial_cwnd;
        }
        else if (key == "max_cwnd") {
            lineStream >> params.max_cwnd;
        }
/*        else if (key == "arrival_rate") {
            lineStream >> params.arrival_rate;
        }
         else if (key == "schedule_rate") {
            lineStream >> params.schedule_rate;
        }*/
         else if (key == "debug") {
            lineStream >> params.debug;
        }
        else if (key == "retx_timeout") {
            lineStream >> params.retx_timeout_value;
        }
        else if (key == "queue_size") {
            lineStream >> params.queue_size;
        }
        else if (key == "propagation_delay") {
            lineStream >> params.propagation_delay;
        }
        else if (key == "bandwidth") {
            lineStream >> params.bandwidth;
        }
        else if (key == "queue_type") {
            lineStream >> params.queue_type;
        }
        else if (key == "packet_type") {
            lineStream >> params.packet_type;
        }
        else if (key == "num_packets") {
            lineStream >> params.num_packets_to_run;
        }
        else if (key == "packet_trace") {
            lineStream >> params.packet_trace;
        }
        else if (key == "cut_through") {
            lineStream >> params.cut_through;
        }
        else if (key == "input_bus_width") {
            lineStream >> params.input_bus_width;
        }
        else if (key == "input_work_rate") {
            lineStream >> params.input_work_rate;
        }
        else if (key == "output_bus_width") {
            lineStream >> params.output_bus_width;
        }
        else if (key == "output_work_rate") {
            lineStream >> params.output_work_rate;
        }
        else if (key == "packet_size") {
            lineStream >> params.packet_size;
        }
        else if (key == "load_balancing") {
            lineStream >> params.load_balancing;
        }
        else if (key == "preemptive_queue") {
            lineStream >> params.preemptive_queue;
        }
        else if (key == "big_switch") {
            lineStream >> params.big_switch;
        }
        else if (key == "simple_topology") {
            lineStream >> params.simple_topology;
        }
         else if (key == "host_type") {
             lineStream >> params.host_type;
        }
        else if (key == "imbalance") {
            lineStream >> params.traffic_imbalance;
        }
        else if (key == "load") {
            lineStream >> params.load;
        }
        else if (key == "traffic_imbalance") {
            lineStream >> params.traffic_imbalance;
        }
        else if (key == "reauth_limit") {
            lineStream >> params.reauth_limit;
        }
        else if (key == "magic_trans_slack") {
            lineStream >> params.magic_trans_slack;
        }
        else if (key == "magic_delay_scheduling") {
            lineStream >> params.magic_delay_scheduling;
        }
        else if (key == "capability_timeout") {
            lineStream >> params.capability_timeout;
        }
        else if (key == "use_packet_trace") {
            lineStream >> params.use_packet_trace;
        }
        else if (key == "smooth_cdf") {
            lineStream >> params.smooth_cdf;
        }
        else if (key == "burst_at_beginning") {
            lineStream >> params.burst_at_beginning;
        }
        else if (key == "capability_resend_timeout") {
            lineStream >> params.capability_resend_timeout;
        }
        else if (key == "capability_initial") {
            lineStream >> params.capability_initial;
        }
        else if (key == "capability_window") {
            lineStream >> params.capability_window;
        }
        else if (key == "capability_prio_thresh") {
            lineStream >> params.capability_prio_thresh;
        }
        else if (key == "capability_third_level") {
            lineStream >> params.capability_third_level;
        }
        else if (key == "capability_fourth_level") {
            lineStream >> params.capability_fourth_level;
        }
        else if (key == "capability_window_timeout") {
            lineStream >> params.capability_window_timeout;
        }
        else if (key == "interarrival_cdf") {
            lineStream >> params.interarrival_cdf;
        }
        else if (key == "num_host_types") {
            lineStream >> params.num_host_types;
        }
        else if (key == "num_hosts") {
            lineStream >> params.num_hosts;
        }
        else if (key == "nqph") {
            lineStream >> params.nqph;
        }
        else if (key == "nqps") {
            lineStream >> params.nqps;
        }
        else if (key == "permutation_tm") {
            lineStream >> params.permutation_tm;
        }
        else {
            std::cout << "Unknown conf param: " << key << " in file: " << conf_filename << "\n";
            assert(false);
        }


        params.param_str.append(line);
        params.param_str.append(", ");
    }

//    params.hdr_size = 40; //TODO: why is this assigned directly?
//    params.mss = 1460;    //TODO: why is this assigned directly?
}
