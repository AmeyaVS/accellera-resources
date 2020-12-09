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

  test.cpp -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

//
// bug in sc_vcd_trace::cycle() 
//   in SystemC 1.2.1Beta  (also 1.0.2).
// Simulates correctly (two clock edges at time 15).
// But VCD is corrupt - has #0 instead of #15.
// Also, this message should be printed but isn't:
//   VCD Trace Warning:
//   Multiple cycles found with same (15) time units count.
//   Waveform viewers will only show the states of the last one.
//   Use ((vcd_trace_file*)vcdfile)->sc_set_vcd_time_unit(int exponent10_seconds)
//   to increase time resolution.
//
//

#include "systemc.h"
// #include <iostream.h>

// class foo: sc_module {
class foo: public sc_module {
public:
    sc_in<bool>	clk1;
    sc_in<bool>	clk2;

    SC_CTOR(foo) {
        SC_METHOD(do_clk1);
        sensitive_pos << clk1;
        SC_METHOD(do_clk2);
        sensitive_pos << clk2;
    }
    void do_clk1() { 
        cout << "foo: clk1 + " << sc_time_stamp() << endl;
    }
    void do_clk2() {
        cout << "foo: clk2 + " << sc_time_stamp() << endl;
    }
};

int
sc_main(int argc, char *argv[])
{
    // sc_clock	clk1("clk1", 10, 0.5);
    // sc_clock	clk2("clk2", 12, 0.5);
    sc_signal<bool> clk1( "clk1" );
    sc_signal<bool> clk2( "clk2" );

    foo		FOO("FOO");

    FOO.clk1(clk1);
    FOO.clk2(clk2);

    sc_trace_file *tf = sc_create_vcd_trace_file("test");
    // sc_trace(tf, clk1.signal(), "clk1");
    // sc_trace(tf, clk2.signal(), "clk2");
    sc_trace(tf, clk1, "clk1");
    sc_trace(tf, clk2, "clk2");

    sc_start(0);

    clk1 = 0;                                         
    clk2 = 0;                                          // 0 ns
    sc_start(3);
    clk2 = 1;                                          // 3 ns +
    sc_start(2);
    clk1 = 1;                                          // 5 ns +
    sc_start(4);
    clk2 = 0;                                          // 9 ns
    sc_start(1);
    clk1 = 0;                                          // 10 ns
    sc_start(5);
    clk2 = 1;                                          // 15 ns +
    sc_start(0);
    clk1 = 1;                                          // 15 ns +
    sc_start(5);
    clk1 = 0;                                          // 20 ns
    sc_start(1);
    clk2 = 0;                                          // 21 ns
    sc_start(4);
    clk1 = 1;                                          // 25 ns +
    sc_start(2);
    clk2 = 1;                                          // 27 ns +
    sc_start(3);
    clk1 = 0;                                          // 30 ns

    sc_close_vcd_trace_file(tf);

    return 0;
}