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

  switch4.cpp -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#include "systemc.h"
short
select( int a, int b, int c )
{
    sc_signed x(7);
    sc_signed y(9);

    switch ((c >> 2) & 3) {
    case 0:
        x = a + b;
        return x.to_int();
    case 1:
        x = a - b;
        break;
    case 2:
        x = (a >> 16) + (b << 16);
        return x.to_int();
    case 3:
        x = (a << 16) - (b >> 16);
        break;
    }

    y = 2 * x;
    return y.to_int();
}

int
sc_main( int, char** argv )   
{
    return 0;
}
