declare name "TableSaw";
declare version "0.0.1";
declare author "Benjamin Quiedeville";
declare description "Boss HM2 Emulation";

import("stdfaust.lib");

gain = hslider("slider", 0.1, 0.0, 1.0, 0.1);

process = *(gain);