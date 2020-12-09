dnl aclocal.m4 generated automatically by aclocal 1.4

dnl Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY, to the extent permitted by law; without
dnl even the implied warranty of MERCHANTABILITY or FITNESS FOR A
dnl PARTICULAR PURPOSE.

dnl
dnl Careful: don't use unquoted commas or double quotes in AC_MSG_ERROR, quote with [ and ]
dnl

AC_DEFUN(SC_VERSION_CHECK,
  [
  AC_CACHE_CHECK("for systemc version", sc_version,
    [
    cat > testsc.sh <<EOF
    #! /bin/sh
    $CXX scver.cc $1 -I[$2] -L[$3] -lsystemc -o scver 2>&5 || exit 1
    exit 0
EOF
    chmod +x testsc.sh
    cat > scver.cc <<EOF
[//
// A program to get the version info from libsystemc.a
//
#include "systemc.h"
int main() {
  int maj=0, min=0, kit=0;
  sscanf(sc_version()," SystemC %d.%d.%d ",&maj,&min,&kit);
  printf("%d%03d%03d\n",maj,min,kit);
  return 0;
}]
EOF
    if eval ./testsc.sh; then
      sc_version=`./scver`
    else
      sc_version="unknown"
      AC_MSG_WARN(Unable to determine the systemC version.
Please check your SystemC installation. )
      date
    fi;
    rm testsc.sh scver.cc scver

    ]
  )
  ]
)

AC_DEFUN(SCV_TEST_CC_SANITY,
  [
  AC_CACHE_CHECK("for working C++ compiler", scv_cv_cc_sanity,
    [
    cat > test.sh <<EOF
    #! /bin/sh
    $CXX conftest.cc [$1] -o test.exe 2>&5
    if test -x test.exe; then
      ./test.exe
    else
      exit 1
    fi;
EOF
    chmod +x test.sh
    cat > conftest.cc <<EOF
[//
// A program to determine if a C++ installation is basically sane
// Use some STL and standard library functions
//
/* HP-UX's aCC doesn't have std defined until it sees a std lib header file */
/* (unlike g++ and SunWorks CC.) */
/* So define it here empty.  Namespaces are extensible, so this is harmless. */
namespace std {}
using namespace std;
#include <string>
#include <stdio.h>
#include <strstream.h>
int main()
{
#define STRING_SIZE 100
  char buf[STRING_SIZE];
  int i = 1;
  sprintf(buf, "hello world %i", i);
  if (strcmp(buf,"hello world 1") != 0)
  {
    exit(1);
  }

  ostrstream outString(buf, STRING_SIZE);
  outString << "hello world " << i;
  if (strcmp(buf,"hello world 1") != 0)
  {
    exit(1);
  }

  string str = "hello world";
  str = str + " 1";
  if (str != "hello world 1")
  {
     exit(1);
  }
  //
  // OK!
  //
  exit(0);
}]
EOF
    if eval ./test.sh; then
      scv_cv_cc_sanity="ok"
      rm test.sh conftest.cc test.exe
    else
      scv_cv_cc_sanity="bad"
      AC_MSG_ERROR(A bad C++ compiler or library or linker found.
Please check your C++ installation.
The testfile that failed: ./conftest.cc may be useful in helping you find the problem.)
      date
    fi;
    ]
  )
  ]
)

AC_DEFUN(SCV_TEST_AUTO_NEQ,
  [
  AC_CACHE_CHECK("for compiler-provided operator!=", scv_have_auto_neq,
    [
    cat > test.sh <<EOF
    #! /bin/sh
    $CXX noteq.cpp [$1] -c -o noteq.o 2>&5 || exit 1
    exit 0
EOF
    chmod +x test.sh
    cat > noteq.cpp <<EOF
[//
// A program to determine whether we need to explicitly define
// operator!= when we define operator==.
//
#include "systemc.h"
struct pppp {
public:
  pppp(int v1, int v2) : _v1(v1), _v2(v2) {}
  friend bool operator ==(const pppp& o1, const pppp& o2) {
    return ( o1._v1 == o2._v1 ) && ( o1._v2 == o2._v2 );
  }
private:
  int _v1, _v2;
};
int main(int argc, char *argv[])
{
  pppp p1(0,1), p2(10,12);
  return p1 != p2;
}]
EOF
    if eval ./test.sh; then
      scv_have_auto_neq="yes"
    else
      scv_have_auto_neq="no"
    fi;
    rm -f test.sh noteq.cpp noteq.o
    ]
  )
  ]
)

AC_DEFUN(SCV_TEST_ULL_WRITE,
  [
  AC_CACHE_CHECK("for unsigned long long stream support", scv_have_ull_write,
    [
    cat > test.sh <<EOF
    #! /bin/sh
    $CXX writeull.cc [$1] -o test.exe 2>&5 || exit 1
    exit 0
EOF
    chmod +x test.sh
    cat > writeull.cc <<EOF
[//
// A program to determine whether we need to roll our own
//   cout << unsigned long long
//
/* HP-UX's aCC doesn't have std defined until it sees a std lib header file */
/* (unlike g++ and SunWorks CC.) */
/* So define it here empty.  Namespaces are extensible, so this is harmless. */
namespace std {}
using namespace std;
#include <stdlib.h>
#include <iostream.h>
int main()
{
  unsigned long long hold = 10;
  cout << hold << endl;
  exit(0);
}]
EOF
    if eval ./test.sh; then
      scv_have_ull_write="yes"
    else
      scv_have_ull_write="no"
    fi;
    rm -f test.sh writeull.cc test.exe
    ]
  )
  ]
)

AC_DEFUN(SCV_TEST_LD_SO,
  [
  AC_CACHE_CHECK("for ability to dynamically load libraries and access data", scv_cv_ld_so,
    [
    cat > test.sh <<EOF
    #! /bin/sh
    $CXX t1conftest.cc [$1] -o libtest$SHLIB_EXT [$2] 2>&5
    $CXX t2conftest.cc -o test.exe -L. -ltest 2>&5
    if test -x test.exe; then
      (LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./test.exe)
    else
      exit 1
    fi;
EOF
    chmod +x test.sh
    cat > t1conftest.cc <<EOF
struct testT { const char* name; int i; int j; };
testT test[[]] = {{"test0",5,2},{"test1",3,3},{0}};
EOF
    cat > t2conftest.cc <<EOF
[#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
struct testT { const char* name; int i; int j;};
static testT (*testP)[];
extern testT test[];
int main() {
  testP=(testT(*)[])(&test);
  static char str[10];
  int i=0, failed=0;
  while((*testP)[i].name){
    sprintf(str, "test%d",i);
    if(strcmp(str, (*testP)[i].name) != 0) ++failed;
    i++;
  }
  if(failed) { exit (1); }
  exit (0);
}]
EOF
    if eval ./test.sh; then
      scv_cv_ld_so="ok"
      rm test.sh t*conftest.cc libtest$SHLIB_EXT test.exe
    else
      scv_cv_ld_so="bad"
      AC_MSG_ERROR("unable to access data in shared library")
      date
    fi;
    ]
  )
  ]
)

AC_DEFUN(SCV_HP_CHECK,
[
dummy=dummy-$$
UNAME_MACHINE=`(uname -m) 2>/dev/null` || UNAME_MACHINE=unknown
UNAME_RELEASE=`(uname -r) 2>/dev/null` || UNAME_RELEASE=unknown
UNAME_SYSTEM=`(uname -s) 2>/dev/null` || UNAME_SYSTEM=unknown
UNAME_VERSION=`(uname -v) 2>/dev/null` || UNAME_VERSION=unknown
sed 's/^              //' << EOF >$dummy.c
#include <stdlib.h>
#include <unistd.h>
int main ()
{
#if defined(_SC_KERNEL_BITS)
  long bits = sysconf(_SC_KERNEL_BITS);
#endif 
  long cpu  = sysconf (_SC_CPU_VERSION);
  switch (cpu) 
  {
    case CPU_PA_RISC1_0: puts ("hppa1.0"); break;
    case CPU_PA_RISC1_1: puts ("hppa1.1"); break;
    case CPU_PA_RISC2_0: 
#if defined(_SC_KERNEL_BITS)
    switch (bits) 
    {
      case 64: puts ("hppa2.0w"); break;
      case 32: puts ("hppa2.0n"); break;
      default: puts ("hppa2.0"); break;
    } break;
#else  /* !defined(_SC_KERNEL_BITS) */
    puts ("hppa2.0"); break;
#endif 
    default: puts ("hppa1.0"); break;
  }
  exit (0);
}
EOF
(${CC-cc} $dummy.c -o $dummy 2>/dev/null ) && HP_ARCH=`./$dummy`
rm -f $dummy.c $dummy
export HP_ARCH
]
)

# Do all the work for Automake.  This macro actually does too much --
# some checks are only needed if your package does certain things.
# But this isn't really a big deal.

# serial 1

dnl Usage:
dnl AM_INIT_AUTOMAKE(package,version, [no-define])

AC_DEFUN(AM_INIT_AUTOMAKE,
[AC_REQUIRE([AC_PROG_INSTALL])
PACKAGE=[$1]
AC_SUBST(PACKAGE)
VERSION=[$2]
AC_SUBST(VERSION)
dnl test to see if srcdir already configured
if test "`cd $srcdir && pwd`" != "`pwd`" && test -f $srcdir/config.status; then
  AC_MSG_ERROR([source directory already configured; run "make distclean" there first])
fi
ifelse([$3],,
AC_DEFINE_UNQUOTED(PACKAGE, "$PACKAGE", [Name of package])
AC_DEFINE_UNQUOTED(VERSION, "$VERSION", [Version number of package]))
AC_REQUIRE([AM_SANITY_CHECK])
AC_REQUIRE([AC_ARG_PROGRAM])
dnl FIXME This is truly gross.
missing_dir=`cd $ac_aux_dir && pwd`
AM_MISSING_PROG(ACLOCAL, aclocal, $missing_dir)
AM_MISSING_PROG(AUTOCONF, autoconf, $missing_dir)
AM_MISSING_PROG(AUTOMAKE, automake, $missing_dir)
AM_MISSING_PROG(AUTOHEADER, autoheader, $missing_dir)
AM_MISSING_PROG(MAKEINFO, makeinfo, $missing_dir)
AC_REQUIRE([AC_PROG_MAKE_SET])])

#
# Check to make sure that the build environment is sane.
#

AC_DEFUN(AM_SANITY_CHECK,
[AC_MSG_CHECKING([whether build environment is sane])
# Just in case
sleep 1
echo timestamp > conftestfile
# Do `set' in a subshell so we don't clobber the current shell's
# arguments.  Must try -L first in case configure is actually a
# symlink; some systems play weird games with the mod time of symlinks
# (eg FreeBSD returns the mod time of the symlink's containing
# directory).
if (
   set X `ls -Lt $srcdir/configure conftestfile 2> /dev/null`
   if test "[$]*" = "X"; then
      # -L didn't work.
      set X `ls -t $srcdir/configure conftestfile`
   fi
   if test "[$]*" != "X $srcdir/configure conftestfile" \
      && test "[$]*" != "X conftestfile $srcdir/configure"; then

      # If neither matched, then we have a broken ls.  This can happen
      # if, for instance, CONFIG_SHELL is bash and it inherits a
      # broken ls alias from the environment.  This has actually
      # happened.  Such a system could not be considered "sane".
      AC_MSG_ERROR([ls -t appears to fail.  Make sure there is not a broken
alias in your environment])
   fi

   test "[$]2" = conftestfile
   )
then
   # Ok.
   :
else
   AC_MSG_ERROR([newly created file is older than distributed files!
Check your system clock])
fi
rm -f conftest*
AC_MSG_RESULT(yes)])

dnl AM_MISSING_PROG(NAME, PROGRAM, DIRECTORY)
dnl The program must properly implement --version.
AC_DEFUN(AM_MISSING_PROG,
[AC_MSG_CHECKING(for working $2)
# Run test in a subshell; some versions of sh will print an error if
# an executable is not found, even if stderr is redirected.
# Redirect stdin to placate older versions of autoconf.  Sigh.
if ($2 --version) < /dev/null > /dev/null 2>&1; then
   $1=$2
   AC_MSG_RESULT(found)
else
   $1="$3/missing $2"
   AC_MSG_RESULT(missing)
fi
AC_SUBST($1)])

# Like AC_CONFIG_HEADER, but automatically create stamp file.

AC_DEFUN(AM_CONFIG_HEADER,
[AC_PREREQ([2.12])
AC_CONFIG_HEADER([$1])
dnl When config.status generates a header, we must update the stamp-h file.
dnl This file resides in the same directory as the config header
dnl that is generated.  We must strip everything past the first ":",
dnl and everything past the last "/".
AC_OUTPUT_COMMANDS(changequote(<<,>>)dnl
ifelse(patsubst(<<$1>>, <<[^ ]>>, <<>>), <<>>,
<<test -z "<<$>>CONFIG_HEADERS" || echo timestamp > patsubst(<<$1>>, <<^\([^:]*/\)?.*>>, <<\1>>)stamp-h<<>>dnl>>,
<<am_indx=1
for am_file in <<$1>>; do
  case " <<$>>CONFIG_HEADERS " in
  *" <<$>>am_file "*<<)>>
    echo timestamp > `echo <<$>>am_file | sed -e 's%:.*%%' -e 's%[^/]*$%%'`stamp-h$am_indx
    ;;
  esac
  am_indx=`expr "<<$>>am_indx" + 1`
done<<>>dnl>>)
changequote([,]))])

