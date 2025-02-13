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

process = _, _ 
        : fi.lowpass(4, filter_freq), fi.lowpass(4, filter_freq)
        : hm2, hm2
        : fi.lowpass(4, filter_freq), fi.lowpass(4, filter_freq) 
with {

    filter_freq = ma.SR * 0.5 * 0.25 * 0.9;

    ceiling = 1.5;
    min_gain_db = 0.0;
    max_gain_db = 60.0;
    dist_gain = ba.db2linear(gain * max_gain_db);
    crossover_point = 0.02;

    asym_tanh = _ <: (min(0) : ma.tanh),
                     (min(1) : max(0)),
                     (max(1) : -(1) : ma.tanh) :
                     +, _ : +;

    crossover = _ <: (max(crossover_point) - crossover_point), 
                     (min(-crossover_point) + crossover_point) 
                     : + ;
  
    hard_clip = min(0.7) : max(-0.7);


    hm2 = *(dist_gain) 
        : /(ceiling) : asym_tanh : *(ceiling)

        : highpass(1, 10) 
        : crossover 
        
        : hard_clip 
        : lowpass(1, 12000) : highpass(1, 30)
    
        : peak_eq_cq(eq_low * 20, 80, 0.5) 
        : peak_eq_cq(eq_high * 20, 1500, 0.5) 
        : peak_eq_cq(eq_high * 20, 1000, 0.5) 
        : *(ba.db2linear(-20))
        : *(volume);
};
