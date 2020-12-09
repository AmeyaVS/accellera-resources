//----------------------------------------------------------------------
//   Copyright 2009-2020 NXP
//   Copyright 2009 Vienna University of Technology
//   Copyright 2009-2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
//   Copyright 2015-2020 COSEDA Technologies GmbH
//   All Rights Reserved Worldwide
//
//   Licensed under the Apache License, Version 2.0 (the
//   "License"); you may not use this file except in
//   compliance with the License.  You may obtain a copy of
//   the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in
//   writing, software distributed under the License is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//   CONDITIONS OF ANY KIND, either express or implied.  See
//   the License for the specific language governing
//   permissions and limitations under the License.
//----------------------------------------------------------------------

#include "bit_src_de.h"

bit_src_de::bit_src_de( sc_core::sc_module_name nm )
: out("out")
{
  SC_THREAD(bit_gen_thread);
}

void bit_src_de::bit_gen_thread()
{
  while(true)
  {
    bool var = (bool)(std::rand()%2);
    out.write(var);
    sc_core::wait( 200, sc_core::SC_NS);
  }
}
