/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2005 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.4 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************
 
  main.cpp -- Main function for the dashboard controller for a
           car. This controller contains a speedometer, two odometers (total
           and partial distance), a clock, and the pulse generator. The
           pulses are generated by the sensors placed around one of the wheel
           shafts. The rate of pulse generation is determined by the speed of
           the car, which is constant at 120 km/h.  The clock represents the
           real time. The signals in this program are traced. The simulation
           is stopped by the odometers module.

           purpose -- no environment module; multiple modules at one level;
           single processes within each module; input, output and clock
           ports; internal and external signals; asynchronous function and
           thread processes; one clock; tracing.
 
  Original Author: Ali Dasdan, Synopsys, Inc.
 
 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#include "systemc.h"
#include "const.h"
#include "pulse.h"
#include "speed.h"
#include "dist.h"

int
sc_main(int argc, char *argv[])
{
  // Pulses for the speedometer and odometers, generated by the pulse
  // generator.
  sc_signal<bool> speed_pulses("speed_pulses");
  sc_signal<bool> dist_pulses("dist_pulses");
  // Clocks.
  sc_clock clk1("fast_clk", FAST_CLOCK_PERIOD1, 0.5, 0.0, false);

  gen_pulse_mod gen_pulse("gen_pulse");
  gen_pulse << clk1 << speed_pulses << dist_pulses;

  speed_mod speedometer("speedometer");
  speedometer << clk1 << speed_pulses;

  dist_mod odometers("odometers");
  odometers << dist_pulses;

  // Tracing:
  // Trace file creation.
  sc_trace_file *tf = sc_create_vcd_trace_file("dash");
  // External signals.
  sc_trace(tf, clk1.signal(), "fast_clk");
  sc_trace(tf, speed_pulses, "speed_pulses");
  sc_trace(tf, dist_pulses, "dist_pulses");
  // Internal signals.
  sc_trace(tf, speedometer.elapsed_time, "elapsed_time");

  sc_start(-1);

  return 0;
}

// End of file