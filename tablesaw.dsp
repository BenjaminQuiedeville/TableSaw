declare name "TableSaw";
declare version "0.0.1";
declare author "Benjamin Quiedeville";
declare description "Boss HM2 Emulation";

import("stdfaust.lib");
import("filter.lib");

gain = hslider("gain", 0.5, 0.0, 1.0, 0.1);
eq_low = hslider("low", 0.5, 0.0, 1.0, 0.1);
eq_high = hslider("high", 0.5, 0.0, 1.0, 0.1);
volume = hslider("vol", 0.5, 0.0, 1.0, 0.1);

// peak_eq_cq(boost_db, frequence, Q)
// highpass/lowpass(ordre, frequence)


// bypass(circuit, param) = _ <: circuit, _ : *(param) * (1 - param) : +;
// write_left_to_right(param) = (_ <: _, _), _ : _, (*(param), *(1-param) : +)

process = _, _ : hm2, hm2
with {

    ceiling = 1;
    min_gain_db = 0.0;
    max_gain_db = 30.0;
    dist_gain = ba.db2linear(gain * max_gain_db);
    crossover_point = 0.3;

    asym_tanh = _ <: (min(0) : ma.tanh),
                     (min(1) : max(0)),
                     (max(1) : -(1) : ma.tanh) :
                     +, _ : +;

    crossover = _ <: (max(crossover_point) - crossover_point), 
                     (min(-crossover_point) + crossover_point) 
                     : + ;
  
    hard_clip = min(1) : max(-1);


    hm2 = *(dist_gain) 
        : /(ceiling) : asym_tanh : *(ceiling) 

        : highpass(1, 10) 
        : crossover 
        
        : hard_clip 
        : lowpass(1, 10000) : highpass(1, 10)
    
        : peak_eq_cq(eq_low * 20, 80, 0.4) 
        : peak_eq_cq(eq_high * 10, 1500, 0.4) 
        : peak_eq_cq(eq_high * 10, 1000, 0.4) 
        : *(volume);
};
