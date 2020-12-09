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

  ram.h -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

/* Filename ram.h */
/* This is the interface file for synchronous process 'ram' */

#include "common.h"

SC_MODULE( ram )
{
  SC_HAS_PROCESS( ram );

  sc_in_clk clk;

  const signal_bool_vector32& datain; //input
  const sc_signal<bool>& cs;        //input
  const sc_signal<bool>& we;        //input
  const signal_bool_vector10& addr;   //input
  signal_bool_vector32& dataout;      //output

  // Internal variable
  int memory[4000];

  // Parameter
  const int wait_cycles; // Number of cycles it takes to access memory

  //Constructor 
  ram(sc_module_name NAME,
      sc_clock& TICK,
      const signal_bool_vector32& DATAIN,
      const sc_signal<bool>& CS,
      const sc_signal<bool>& WE,
      const signal_bool_vector10& ADDR,
      signal_bool_vector32& DATAOUT,
      const int WAIT_CYCLES = 1)
    : clk(TICK), datain(DATAIN), cs(CS), we(WE), 
      addr(ADDR), dataout(DATAOUT), wait_cycles(WAIT_CYCLES)
  {
    SC_CTHREAD( entry, clk.pos() );
  }

  // Process functionality in member function below
  void entry();
};


