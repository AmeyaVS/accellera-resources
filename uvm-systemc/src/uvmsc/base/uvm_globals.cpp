//----------------------------------------------------------------------
//   Copyright 2014 Université Pierre et Marie Curie, Paris
//   Copyright 2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
//   Copyright 2007-2011 Mentor Graphics Corporation
//   Copyright 2007-2011 Cadence Design Systems, Inc.
//   Copyright 2010-2011 Synopsys, Inc.
//   Copyright 2012-2014 NXP B.V.
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

#include <cstdio>
#include <cstring>

#include <systemc>
#include "sysc/kernel/sc_module.h"
#include "sysc/kernel/sc_process_handle.h"

#include "uvmsc/base/uvm_globals.h"
#include "uvmsc/base/uvm_root.h"
#include "uvmsc/conf/uvm_config_db.h"

#if !defined(_MSC_VER)
#include "config.h"
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1500)
#define HAVE_CXX11_REGEX
#endif

#if defined(HAVE_CXX11_REGEX)
#include <regex>
#elif defined(HAVE_POSIX_REGEX)
#include <cstdlib>   // for std::malloc
#include <regex.h>
#elif defined(HAVE_PCRE_REGEX)
#include <cstdlib>   // for std::malloc
#include <pcreposix.h>
#else
#error missing regular expression library
#endif

using namespace sc_core;

namespace uvm {

//------------------------------------------------------------------------------
// function: run_test
//
//! Global helper function to use some uvm_root methods in sc_main
//------------------------------------------------------------------------------

void run_test( const std::string& test_name )
{
  uvm_root::get()->run_test(test_name);
}

//------------------------------------------------------------------------------
// function: print_topology
//
//! Global helper function print the UVM hierarchy
//------------------------------------------------------------------------------

void print_topology( uvm_printer* printer )
{
  uvm_root::get()->print_topology(printer);
}

//------------------------------------------------------------------------------
// global variable to get a handle to the top
//
// note: this variable is being initialized as soon as the uvm_root module
// becomes part of the design hierarchy
//------------------------------------------------------------------------------

// TODO recommended not to use, therefore disabled
//uvm_root* uvm_top = NULL;

//------------------------------------------------------------------------------
//
// Global reporting
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Function: uvm_report_enabled
//
//! Returns true if the configured verbosity in ~uvm_top~ is greater than
//! ~verbosity~ and the action associated with the given ~severity~ and ~id~
//! is not UVM_NO_ACTION, else returns false.
//------------------------------------------------------------------------------

bool uvm_report_enabled( const int& verbosity,
                         const uvm_severity& severity,
                         const std::string& id )
{
  return uvm_root::get()->uvm_report_enabled(verbosity,severity,id);
}


// Function: uvm_report_info

void uvm_report_info( const std::string& id,
                      const std::string& message,
                      int verbosity,
                      const std::string& fname,
                      int line )
{
  uvm_root::get()->uvm_report_info(id, message, verbosity, fname, line);
}


void uvm_report_warning( const std::string& id,
                         const std::string& message,
                         int verbosity,
                         const std::string& fname,
                         int line )
{
  uvm_root::get()->uvm_report_warning(id, message, verbosity, fname, line);
}

void uvm_report_error( const std::string& id,
                       const std::string& message,
                       int verbosity,
                       const std::string& fname,
                       int line )
{
  uvm_root::get()->uvm_report_error(id, message, verbosity, fname, line);
}

void uvm_report_fatal( const std::string& id,
                       const std::string& message,
                       int verbosity,
                       const std::string& fname,
                       int line )
{
  uvm_root::get()->uvm_report_fatal(id, message, verbosity, fname, line);
}

// TODO temporary set verbosity level. Should be moved to
// command line interface

void uvm_set_verbosity_level(int verbosity_level)
{
  uvm_root::get()->set_report_verbosity_level_hier(verbosity_level);
}


//----------------------------------------------------------------------------
//
// Configuration
//
//----------------------------------------------------------------------------

void uvm_set_config_int( const std::string& inst_name,
                         const std::string& field_name,
                         int value )
{
  uvm_config_int::set(NULL, inst_name, field_name, value);
}

void uvm_set_config_string( const std::string& inst_name,
                            const std::string& field_name,
                            const std::string& value )
{
  uvm_config_string::set(NULL, inst_name, field_name, value);
}


//----------------------------------------------------------------------------
//
// Group: Miscellaneous
//
//----------------------------------------------------------------------------

void uvm_wait_for_nba_region()
{
  // TODO uvm_wait_for_nba_region
  for (int i = 0; i < UVM_POUND_ZERO_COUNT; i++)
    sc_core::wait(SC_ZERO_TIME);
}


//----------------------------------------------------------------------------
// Function: uvm_is_match
//
// Returns 1 if the two strings match, 0 otherwise.
//
// The first string, ~expr~, is a string that may contain '*' and '?'
// characters. A * matches zero or more characters, and ? matches any single
// character. The 2nd argument, ~str~, is the string begin matched against.
// It must not contain any wildcards.
//
//----------------------------------------------------------------------------

bool uvm_is_match ( const std::string& expr, const std::string& str )
{
  std::string s;
  s = uvm_glob_to_re(expr);
  return (uvm_re_match(s, str) == 0);
}

bool uvm_has_wildcard ( const std::string& arg )
{
  // check if it has globs
  size_t found;
  found = arg.find("*");
  if ( found != std::string::npos ) return true;
  found = arg.find("?");
  if ( found != std::string::npos ) return true;
  found = arg.find("+");
  if ( found != std::string::npos ) return true;

  // if it is a regex (starts with '/') then return true as well
  found = arg.find("/");
  if ( int(found) == 0 ) // first '/' found
    return true;

  // if none of the above
  return false;
}


const char uvm_re_bracket_char = '/';
static char uvm_re[2048];


//--------------------------------------------------------------------
// uvm_glob_to_re
//
// Convert a glob expression to a normal regular expression.
//--------------------------------------------------------------------

std::string uvm_glob_to_re( const std::string& s )
{
  return (std::string)uvm_glob_to_re_char(s.c_str());
}

const char* uvm_glob_to_re_char(const char *glob)
{
  const char *p;
  int len;

  // safety check.  Glob should never be NULL
  if(glob == NULL)
    return NULL;

  len = std::strlen(glob);

  if (len > 2040) {
    std::ostringstream msg;
    msg << "Glob expression greater than max 2040 characters (length = " << len << ").";
    UVM_ERROR("GLOBERR", msg.str());
    return glob;
  }

  // If either of the following cases appear then return an empty string
  //
  //  1.  The glob string is empty (it has zero characters)
  //  2.  The glob string has a single character that is the
  //      uvm_re_bracket_char  (i.e. "/")
  if(len == 0 || (len == 1 && *glob == uvm_re_bracket_char))
  {
    uvm_re[0] = '\0';
    return &uvm_re[0];  // return an empty string
  }

  // If bracketed with the /glob/, then it's already a regex
  if(glob[0] == uvm_re_bracket_char && glob[len-1] == uvm_re_bracket_char)
  {
    std::strcpy(uvm_re, glob);
    return &uvm_re[0];
  }
  else
  {
    // Convert the glob to a true regular expression (Posix syntax)
    len = 0;

#if !defined(_MSC_VER)
	uvm_re[len++] = uvm_re_bracket_char;
#endif

    // ^ goes at the beginning...
    if (*glob != '^')
      uvm_re[len++] = '^';

    for(p = glob; *p; p++)
    {
      // Replace the glob metacharacters with corresponding regular
      // expression metacharacters.
      switch(*p)
      {
      case '*':
        uvm_re[len++] = '.';
        uvm_re[len++] = '*';
        break;

      case '+':
        uvm_re[len++] = '.';
        uvm_re[len++] = '+';
        break;

      case '.':
        uvm_re[len++] = '\\';
        uvm_re[len++] = '.';
        break;

      case '?':
        uvm_re[len++] = '.';
        break;

      case '[':
        uvm_re[len++] = '\\';
        uvm_re[len++] = '[';
        break;

      case ']':
        uvm_re[len++] = '\\';
        uvm_re[len++] = ']';
        break;

      case '(':
        uvm_re[len++] = '\\';
        uvm_re[len++] = '(';
        break;

      case ')':
        uvm_re[len++] = '\\';
        uvm_re[len++] = ')';
        break;

      default:
        uvm_re[len++] = *p;
        break;
      }
    }
  }

  // Let's check to see if the regular expression is bounded by ^ at
  // the beginning and $ at the end.  If not, add those characters in
  // the appropriate position.

  if (uvm_re[len-1] != '$')
    uvm_re[len++] = '$';

#if !defined(_MSC_VER)
  uvm_re[len++] = uvm_re_bracket_char;
#endif

  uvm_re[len++] = '\0';

  return &uvm_re[0];
}

//--------------------------------------------------------------------
// uvm_re_match
//
// Match a string to a regular expression.  The regex is first lookup
// up in the regex cache to see if it has already been compiled.  If
// so, the compile version is retrieved from the cache.  Otherwise, it
// is compiled and cached for future use.  After compilation the
// matching is done using regexec().
//--------------------------------------------------------------------

int uvm_re_match( const std::string& re, const std::string& str )
{
  int err;

#if defined(HAVE_CXX11_REGEX)
  int match;
#if defined(_MSC_VER) && (_MSC_VER >= 1500) && (_MSC_VER < 1700)
  // MSVC 2008 and 2010: regex is in nested namespace std::tr1
  std::tr1::regex regex(re, std::tr1::regex::extended);
  match = std::tr1::regex_match(str.begin(), str.end(), regex);
#else
  std::regex regex(re, std::regex::extended);
  match = std::regex_match(str.begin(), str.end(), regex);
#endif
  err = !match;
#else
  err = uvm_re_match_char(re.c_str(), str.c_str() );
#endif

  return err;
}

#if !defined(HAVE_CXX11_REGEX)
int uvm_re_match_char(const char *re, const char *str)
{
  regex_t *rexp;
  
  int err;
  int len = std::strlen(re);
  char * rex = &uvm_re[0];

  // safety check.  Args should never be null since this is called
  // from DPI.  But we'll check anyway.
  if(re == NULL)
    return 1;
  if(str == NULL)
    return 1;

  /*
  if (len == 0) {
    UVM_ERROR("REGEXERR", "Regular expression empty.");
    return 1;
  }
  */
  if (len > 2040) {
    std::ostringstream msg;
    msg << "Glob expression greater than max 2040 characters (length = " << len << ").";
    UVM_ERROR("GLOBERR", msg.str());
    return 1;
  }

  // we copy the regexp because we need to remove any brackets around it
  std::strcpy(&uvm_re[0], re);
  if (len>1 && (re[0] == uvm_re_bracket_char) && re[len-1] == uvm_re_bracket_char) {
    uvm_re[len-1] = '\0';
    rex++;
  }

  rexp = static_cast<regex_t*>(std::malloc(sizeof(regex_t)));

  if (rexp == NULL) {
    UVM_ERROR("REGEXERR", "Internal memory allocation error.");
    return 1;
  }

  err = regcomp(rexp, rex, REG_EXTENDED);

  if (err != 0) {
    std::ostringstream msg;
    msg << "Invalid glob or regular expression: |" << re << "|";
    UVM_ERROR("REGEXERR", msg.str());
    regfree(rexp);
    return err;
  }

  err = regexec(rexp, str, 0, NULL, 0);

  std::ostringstream info;
  info << "re = " << rex
       << " str = " << str
       << " ERR = " << err
       << " |" << re << "|";
  UVM_INFO("REGEX", info.str(), UVM_DEBUG);

  regfree(rexp);

  return err;
}
#endif // HAVE_CXX11_REGEX


} // namespace uvm
