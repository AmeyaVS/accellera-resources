## ****************************************************************************
##
##  The following code is derived, directly or indirectly, from the SystemC
##  source code Copyright (c) 1996-2012 by all Contributors.
##  All Rights reserved.
##
##  The contents of this file are subject to the restrictions and limitations
##  set forth in the SystemC Open Source License Version 2.3 (the "License");
##  You may not use this file except in compliance with such restrictions and
##  limitations. You may obtain instructions on how to receive a copy of the
##  License at http://www.systemc.org/. Software distributed by Contributors
##  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
##  ANY KIND, either express or implied. See the License for the specific
##  language governing rights and limitations under the License.
##
## ****************************************************************************
##
##  Makefile.am --
##  Process this file with automake to produce Makefile.in
##
## ****************************************************************************
##
##  Original Authors:
##  Eric Paire, Jerome Cornet
##  STMicroelectronics, 2012-04-27
##
## ****************************************************************************
##  
##  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
##  changes you are making here.
##
##      Name, Affiliation, Date: 
##  Description of Modification:
##
## ****************************************************************************

TESTS = \
	ex_03_nestdata

check_PROGRAMS = \
	ex_03_nestdata

ex_03_nestdata_SOURCES = \
	state.h \
	state_ext.h \
	test.cc

EXTRA_DIST = \
	README \
	checktest.sh \
	ex_03_nestdata.vcproj \
	test_reg.cc

my_data_DATA = \
	$(EXTRA_DIST) \
	$(ex_03_nestdata_SOURCES)

my_datadir = $(prefix)/examples/scv/extensions/ex_03_nestdata

ex_03_nestdata_CPPFLAGS = \
	-I$(SYSC_INC_PREFIX) \
	-I$(top_srcdir)/src \
	-I$(buildInc)

ex_03_nestdata_LDADD = \
	$(top_builddir)/src/scv/libscv.la

ex_03_nestdata_LDFLAGS = \
	-R$(SYSC_LIB_PREFIX)
