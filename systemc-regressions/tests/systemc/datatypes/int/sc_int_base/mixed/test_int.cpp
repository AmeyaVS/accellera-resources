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

  test_int.cpp -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#include "systemc.h"


int sc_main( int ac, char *av[] )
{
  sc_int_base a(8),b(8);
  int x;

  

  x = 8;
  a = 8;
  assert( x == a);
  
  cout << "x + a = " << x + a << endl;
  cout << "++a = " << ++a << endl;
  cout << "a-- = " << a-- << endl;
  
  // bit-select on L.H.S.
  a[0] = 1;
  cout << "a = " << a << endl;

  // bitselect on R.H.S.
  cout << "a[3] = " << a[3] << endl;


  // part-select on R.H.S
  cout << "a.range(4,0) = " << a.range(4,0) << endl;
  cout << "a = " << a << endl;  
  
  sc_int_base c(5);
  c = a.range(4,0);
  cout << "c = " << c << endl;

  // part-select on L.H.S.
  a.range(2,0) = 7;
  cout << "a = " << a << endl;

  a.range(4,2) = 5;
  cout << "a = " << a << endl;

  a.range(7,4) = 8;
  cout << "a = " << a << endl;

  // concat on R.H.S.
  sc_int_base sx(4); 
  sx = 1;
  sc_int_base sy(4);
  sy = 3;
  a = ( sx, sy );

  cout << "a = " << a << endl;
  
  sc_int_base sb(8);
  // concat of part-selects
  sb = ( a.range(7,4), a.range(3,0) );
  
  cout << "sb = " << sb << endl;

  ( sx, sy ) = 17;

  cout << "sx = " << sx << endl;
  cout << "sy = " << sy << endl;
  
  // concat and part-selects
  ( sx, sy ) = ( a.range(7,4), a.range(3,0) );
  
  cout << "sx = " << sx << endl;
  cout << "sy = " << sy << endl;
  
  sc_int_base  s5(5);

  s5 = ( sx , a[4] );
  
  cout << "s5 = " << s5 << endl;

  s5 = (a[4],sx);
  cout << "s5 = " << s5 << endl;

  sc_bv<8> sc8;
  sc_bv<4> sc4;
  
  // ( sc8.range(7,4), sc4 ) = 17; 
  ( sc8.range(7,4), sc4 ) = "00010001"; 

  cout << "sc8 = " << sc8.to_int() << endl;
  cout << "sc4 = " << sc4.to_int() << endl;
  
  sc_int_base sia(8);


  sc_uint_base u4(4);
  
  // part-select on sc_uint
  u4 = sx.range(3,0);

  cout << "u4 = " << u4 << endl;

  u4[3] = sx[0];

  cout << "u4 = " << u4 << endl;

  sx = (u4.range(1,0), u4.range(3,2));

  cout << "sx = " << sx << endl;

  sc_bv<8> bva;
  sc_lv<8> lva;

  // Mixing bv, lv on the RHS

  bva = "10000000";
  lva = "10000001";

  b = bva & "1010";
  cout << "b = " << b << endl;

  // b = lva ^ bva;
  b = sc_bv<8>( lva ^ bva );
  cout << "b = " << b << endl;

  //Mixing bv, lv on the LHS

  bva = b;
  lva = b;

  cout << "bva = " << bva << endl;
  cout << "lva = " << lva << endl;

  bva = b & lva.to_int();
  
  cout << "bva = " << bva << endl;
  

  //Mixing sc_signed on LHS
  
  sc_signed ss8(8);
  ss8 = b;
  cout << "ss8 = " << ss8 << endl;

  ss8 = u4;
  cout << "ss8 = " << ss8 << endl;
 
  // Mixing sc_signed/sc_unsigned on RHS
  sc_unsigned su8(8);

  su8 = 8;
  b = su8 + 1;
  
  cout << "b = " << b << endl;

  b = ss8 * su8;
  b = ss8 ^ su8;
  su8 = bva.to_int() | ss8;
 
  cout << "b = " << b << endl;

  // Having more than two concats

  sc_int_base ai2(2);
  sc_int_base bi4(4);
  sc_int_base ci2(2);
  sc_int_base di2(2);
  sc_int_base ei8(8);
  sc_int_base ei10(10);

  ai2 = 2;
  bi4 = 2;
  ci2 = 2;
  di2 = 2;
  
  ei8 = (ai2, bi4, ci2 );

  cout << "ei8 = " << ei8 << endl;

  ei10 = (ai2, bi4, ci2 , di2);
  
  cout << "ei10 = " << ei10 << endl;
  
  // bit-true behavior
  sc_int_base bs4(4);
  sc_signed ds4(4);

  bs4[3] = 1;
  bs4[2] = 0;
  bs4[1] = 0;
  bs4[0] = 0;

  ds4[3] = 1;
  ds4[2] = 0;
  ds4[1] = 0;
  ds4[0] = 0;
  
  
  cout << "bs4  = " << bs4 << endl;
  cout << "ds4 =  " << ds4 << endl;

  return 0;

}