/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2002 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.3 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  main.cpp -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

/* Main file for parametric adder simulation */

#include "paramadd.h"
#include "stim.h"

int sc_main(int ac, char *av[])
{
  // Parameter Settings
  int width = 4;

  // Signal Instantiation
  sc_signal<bool> reset;
  signal_bool_vector a ("Operand1");
  signal_bool_vector b ("Operand2");
  sc_signal<bool> cin;
  sc_signal<bool> ready;
  signal_bool_vector sum ("Sum");
  sc_signal<bool> co;
  sc_signal<bool> done;

  // Clock Instantiation
  sc_clock clk ("Clock", 10, 0.5, 0);

  // Process Instantiation
  paramadd D1("D1", clk, reset, a, b, cin, ready, sum, 
	      co, done, width);
  stim T1("T1", clk, done, reset, a, b, cin, 
	  ready, width);

  // Simulation Run Control
  sc_start( -1 );
  return 0;
}
