//  -*- C++ -*- <this line is for emacs to recognize it as C++ code>
/*****************************************************************************

  Licensed to Accellera Systems Initiative Inc. (Accellera) 
  under one or more contributor license agreements.  See the 
  NOTICE file distributed with this work for additional 
  information regarding copyright ownership. Accellera licenses 
  this file to you under the Apache License, Version 2.0 (the
  "License"); you may not use this file except in compliance
  with the License.  You may obtain a copy of the License at
 
    http://www.apache.org/licenses/LICENSE-2.0
 
  Unless required by applicable law or agreed to in writing,
  software distributed under the License is distributed on an
  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
  KIND, either express or implied.  See the License for the
  specific language governing permissions and limitations
  under the License.

 *****************************************************************************/
#include "data_ext.h"

int sc_main(int argc, char** argv) {
  scv_smart_ptr<data_t> data_p("data");

  //set the values of the fields. Note: a scv_smart_ptr
  //works like a normal pointer object for accessing the
  //object.
  data_p->field_1 = 10;
  data_p->field_2 = 0xff;
  for(unsigned i=0; i<5; ++i) data_p->payload[i] = i*i;
  data_p->str = "my data string";

  scv_out << "Printing data in object " << data_p->get_name()
       << endl;
  data_p->print(); //print the object
  
  return 0;
}
