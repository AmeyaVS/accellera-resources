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

  test02.cpp -- 

  Original Author: Ucar Aziz, Synopsys, Inc., 2002-02-15
                   Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

//test of sc_prim_channel::next_trigger(const sc_event&)

#include <systemc.h>

//write and read interfaces
class write_if : virtual public
sc_interface
 {
  public:
   virtual void write() = 0;
};

class read_if : virtual public 
sc_interface
{
 public:
  virtual void read( ) = 0;
};

// channel implements write_if and read_if interfaces
class channel :
  public sc_channel,
  public write_if,
  public read_if
{

  public :

  //constructor
  channel(sc_module_name name):sc_channel(name)  
  { }

  //write to channel 
  void write(){
    static int i = 0;
    if(i < 10){
    next_trigger(read_event);
    data = i;
    cout<<"writting "<< data <<" to channel";
    i++;
    cout<<" and notifying write_event" << endl;
    write_event.notify();
  }
  }

  //read from channel
  void read( ){
    int j;
    next_trigger(write_event);
    j = data;
    cout<<"reading  "<<j<<" from channel";
    cout<<" and notifying read_event" << endl; 
    read_event.notify();
  }

  private:
  int data;
  sc_event write_event, read_event;

};

//source module
SC_MODULE(mod_a)
{
  sc_port<write_if> out;

  void write( )
  {
    out->write();
  }  

  SC_CTOR( mod_a ){
  
    SC_METHOD(write);
  }
};
  
//sink module
SC_MODULE(mod_b)
{
  sc_port<read_if> input;
  int i;

  void read( )
  {
   input->read();
  }  

  SC_CTOR( mod_b ){
  
    SC_METHOD(read);
  }
};
  

int sc_main(int, char*[] )
{
  channel a("a");
  mod_a modul_a("modul_a");
  mod_b modul_b("modul_b");
  modul_a.out(a);
  modul_b.input(a); 

  sc_start(10, SC_NS);
  return 0 ;
}
