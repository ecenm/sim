/*-
 * Copyright (c) 2016 Neelakandan.Manihatty-Bojan
 * All rights reserved.
 *
 * 
 *  File:
 *        params.h
 *
 *
 *  Author:
 *        Neelakandan.Manihatty-Bojan
 * 		
 *  Description:
 *        A header file for parameters definitions
 *
 */

#ifndef PARAMS_H
#define PARAMS_H

#include <string>
#include <fstream>

//TODO: separate types of params, including (but not limited to):
// global experiment params, unit params (e.g. queue, switch, link, host), debug/tracing params, files params (e.g. output, config)

class DCExpParams {
    public:
        std::string param_str;

        uint32_t initial_cwnd; //initial congestion window, valid values ?
        //double arrival_rate;   //queue input arrival rate, in packets per second. valid values ?
//TODO: complete all parameters descriptions for all entries
        //double schedule_rate;  
        uint32_t max_cwnd;
        uint32_t debug;
        double retx_timeout_value;
        uint32_t mss;
        uint32_t hdr_size;
        uint32_t queue_size;
        uint32_t queue_type;
        uint32_t packet_type;
        uint32_t load_balancing; //0 per pkt, 1 per flow

        double propagation_delay;
        double bandwidth;

        uint32_t num_packets_to_run;
        double end_time;
        std::string packet_trace;
        uint32_t cut_through;
        uint32_t packet_size;
        
        uint32_t input_bus_width;
        uint32_t input_work_rate;
        uint32_t output_bus_width;
        uint32_t output_work_rate;

        uint32_t num_hosts;
        uint32_t num_agg_switches;
        uint32_t num_core_switches;
        uint32_t preemptive_queue;
        uint32_t big_switch;
        uint32_t simple_topology;
        uint32_t host_type;
        double traffic_imbalance;
        double load;

        double reauth_limit;

        double magic_trans_slack;
        uint32_t magic_delay_scheduling;
        uint32_t magic_inflate;

        uint32_t use_packet_trace;
        uint32_t smooth_cdf;
        uint32_t burst_at_beginning;
        double capability_timeout;
        double capability_resend_timeout;
        uint32_t capability_initial;
        uint32_t capability_window;
        uint32_t capability_prio_thresh;
        double capability_window_timeout;
        uint32_t capability_third_level;
        uint32_t capability_fourth_level;
        
        uint32_t nqph;
        uint32_t nqps;

        std::string interarrival_cdf;
        uint32_t num_host_types;

        double fastpass_epoch_time;

        uint32_t permutation_tm;

        double get_full_pkt_tran_delay(uint32_t size_in_byte = 1500)
        {
            return size_in_byte * 8 / this->bandwidth;
        }

};


void read_experiment_parameters(std::string conf_filename, uint32_t exp_type);

/* General main function */
#define DEFAULT_EXP 1

#define INFINITESIMAL_TIME 0.000000000001

#endif



