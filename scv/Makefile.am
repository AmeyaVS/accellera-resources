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
##  Process this file with automake to produce a Makefile.in file.
## 
## ****************************************************************************
##
##  Original Authors:
##  Norris Ip, Dean Shea, John Rose, Jasvinder Singh, William Paulsen,
##  John Pierce, Rachida Kebichi, Ted Elkind, David Bailey,
##  Cadence Design Systems, Inc., 2002-09-23
##
## ****************************************************************************
##  
##  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
##  changes you are making here.
##
##      Name, Affiliation, Date: Eric Paire, Jerome Cornet, 
##                               STMicroelectronics, 2012-03-27
##  Description of Modification: Revamp of autotool build system for 64-bit
##                               support, 32-bit compilation on 64-bit host
##
##      Name, Affiliation, Date: Torsten Maehne, 
##                               Universite Pierre et Marie Curie, 2013-05-03
##  Description of Modification: Remove manual definition of the
##                               SHELL variable in all Makefile.am files, as it
##                               is already properly initialized by automake to
##                               POSIX-compliant shell.
##                               Remove AUTOMAKE_OPTIONS from all Makefile.am,
##                               where it doesn't have an effect.
##                               Replace INCLUDES variables by per-target
##                               _CPPFLAGS variables in all Makefile.am files
##                               to fix deprecation warnings.
##
## ****************************************************************************

AUTOMAKE_OPTIONS = foreign

BUILT_SOURCES = \
	scv_config.h

SUBDIRS = \
	scripts \
	src \
	docs \
	examples

TEXTDOCS = LICENSE README AUTHORS COPYING INSTALL NEWS RELEASENOTES

my_data_DATA = $(TEXTDOCS:=.scv)

my_datadir = $(prefix)

nodist_my_includes_HEADERS = \
	${buildInc}/scv/scv_config.h

my_includesdir = $(includedir)/scv

%.scv : %
	cp -fp $< $@

EXTRA_DIST = \
	${TEXTDOCS} \
	osci_issues_for_scv.txt \
	msvc71/cudd/cudd.vcproj \
	msvc71/cudd/ReadMe.txt \
	msvc71/mtr/mtr.vcproj \
	msvc71/mtr/ReadMe.txt \
	msvc71/st/st.vcproj \
	msvc71/st/ReadMe.txt \
	msvc71/dddmp/dddmp.vcproj \
	msvc71/dddmp/ReadMe.txt \
	msvc71/obj/ReadMe.txt \
	msvc71/obj/obj.vcproj \
	msvc71/util/util.vcproj \
	msvc71/util/ReadMe.txt \
	msvc71/scv_config.h \
	msvc71/README \
	msvc71/scv.vcproj

${buildInc}/scv/scv_config.h : config.h
	rm -f $@ $@.tmp
	mkdir -p ${buildInc}/scv
	cp $< $@.tmp
	echo "#undef PACKAGE" >>$@.tmp
	mv $@.tmp $@

scv_config.h : ${buildInc}/scv/scv_config.h
	cp -fp $< $@

CLEANFILES = \
	scv_config.h \
	${buildInc}/scv/scv_config.h

debug:
	$(MAKE) all CXXFLAGS="$(CXXFLAGS_DEBUG)" CFLAGS="$(CFLAGS_DEBUG)"

opt:
	$(MAKE) all CXXFLAGS="$(CXXFLAGS_OPT)" CFLAGS="$(CFLAGS_OPT)"
