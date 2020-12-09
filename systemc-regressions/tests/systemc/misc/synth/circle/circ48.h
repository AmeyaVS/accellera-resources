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

  circ48.h -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#include "common.h"

SC_MODULE( circ48 )
{
    SC_HAS_PROCESS( circ48 );

    sc_in_clk clk;

    sc_in<bool>         reset;
    sc_in<bool>         x_ok;
    sc_in<bool>         y_ok;
    sc_out<bool>        out_wr;
    sc_out<bool>        out_sel;
    sc_out<bool_vector> out_xy;
    sc_out<bool_vector> diffs;

    void entry();
 
    circ48( sc_module_name         name_,
	    const sc_clock&        clk_,
	    const sc_signal<bool>& reset_,
	    const sc_signal<bool>& x_ok_,
	    const sc_signal<bool>& y_ok_,
	    sc_signal<bool>&       out_wr_,
	    sc_signal<bool>&       out_sel_,
	    signal_bool_vector&    out_xy_,
	    signal_bool_vector&    diffs_ )
	: sc_module( name_ ),
          clk( clk_ ),
	  reset( reset_ ),
	  x_ok( x_ok_ ),
	  y_ok( y_ok_ ),
	  out_wr( out_wr_ ),
	  out_sel( out_sel_ ),
	  out_xy( out_xy_ ),
	  diffs( diffs_ )
    {
	SC_CTHREAD( entry, clk.pos() );
	watching( reset.delayed() == 1 );
    }
};


/*****************************************************************************/
/**									    **/
/**  This function is the "clean" behavior (i.e. not written with synthesis **/
/**  or implementation in mind.  This is a circle generator, that uses an   **/
/**  algorithmic, interpolating technique.  Origin of circle is fixed to    **/
/**  point (0,0) 							    **/
/**  NOTE:  Extra WAIT at end for VGB (requires waits after signal assign)  **/
/**									    **/
/*****************************************************************************/

void
circ48::entry()
{
    sc_signed x(4); 	
    sc_signed y(4); 
    sc_signed x_end(4); 
    sc_signed y_end(4); 
    sc_signed diff(8);
    bool first;

    // reset initialization

    out_wr.write( 0 );		// Initialize at time zero ????
    out_sel.write( 0 );

    // setup counter-clockwise circle generation

    while(true) {  // Reset_loop
	x_end = 4;
	x = x_end;
	diff = 0;
	diffs.write(diff);
	y_end = 4;
	y = y_end;
	first = true;
	wait(); 		

        // perform counter-clockwise circle generation

	while(first || (x != x_end) || (y != y_end)) {  // Main_loop
	    first = false;
	    diff = diff + 1;

	    if (diff > 1) {
		if ((x >= 0) && (y >= 0)) {
		    diff = diff - x - x;
		    x = x - 1;
		}
		else { // else_1_begin
		    if ((x < 0) && (y >= 0)) {
			diff = diff - y - y;
			y = y - 1;
		    }
		    else { // else_2_begin
			if ((x < 0) && (y < 0)) {
			    diff = diff + x + x;
			    x = x + 1;
			}
			else {
			    diff = diff + y + y;
			    y = y + 1;
			}
		    } // else_2_end
		} // else_1_end
	    } 
	    else {
		if ((x >= 0) && (y >= 0)) {
		    diff = diff + y + y;
		    y = y + 1;
		}
		else { // else_3_begin
		    if ((x < 0) && (y >= 0)) {
			diff = diff - x - x;
			x = x - 1;
		    }
		    else { // else_4_begin
			if ((x < 0) && (y < 0)) {
			    diff = diff - y - y;
			    y = y - 1;
			}
			else {
			    diff = x + x;
			    x = x + 1;
			}
		    } // else_4_end
		} // else_3_end
	    }
	    
            // send the intermediate x value to port
	
	    out_sel.write(0);	// Select x
	    out_wr.write(1);	// Output ready signal
	    out_xy.write(x);	
	    diffs.write(diff);
	    wait();

            // handshake x..

	    wait_until(x_ok.delayed() == 1); 
	    out_wr.write(0);
	    wait();
	    
            // send the intermediate y value to port
     
	    out_sel.write(1);	// Select y
	    out_wr.write(1);	// Output ready signal
	    out_xy.write(y);
	    wait();
 
            // handshake y..
 
	    wait_until(y_ok.delayed() == 1); 
	    out_wr.write(0);
	    wait();
	}  // End of Main_loop
    }  // End of Reset_loop 
}
