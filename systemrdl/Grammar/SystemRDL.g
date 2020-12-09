/*
Copyright 2009 The SPIRIT Consortium.

This work forms part of a deliverable of The SPIRIT Consortium.

Use of these materials are governed by the legal terms and conditions
outlined in the disclaimer available from www.spiritconsortium.org.

This source file is provided on an AS IS basis.  The SPIRIT
Consortium disclaims any warranty express or implied including
any warranty of merchantability and fitness for use for a
particular purpose.

The user of the source file shall indemnify and hold The SPIRIT
Consortium and its members harmless from any damages or liability.
Users are requested to provide feedback to The SPIRIT Consortium
using either mailto:feedback@lists.spiritconsortium.org or the forms at
http://www.spiritconsortium.org/about/contact_us/

This file may be copied, and distributed, WITHOUT
modifications; this notice must be included on any copy.
The following code is derived, directly or indirectly, from
source code (C) COPYRIGHT 2009 Denali Software Inc. and is used by
permission under the terms described above.

*/

class SystemRDLParser extends Parser;
options { k = 2; }
tokens  { INST_ID; PROPERTY; }

root
  : ( component_def
    | enum_def
    | explicit_component_inst
    | property_assign
    | property_definition
    )* EOF
  ;

 property_definition
 { track = true; }
   : "property" { rpa->begin_property_def(); }
     id          { rpa->create_property_name(); }
     LBRACE
     property_body
     RBRACE
     SEMI { rpa->end_property_def(); }
   ;

property_body
{ track = true; }
  :  property_type ( property_usage (property_default)?
                   | property_default property_usage
                   )
  |  property_usage ( property_type (property_default)?
                    | property_default property_type
                    )
  |  property_default ( property_type  property_usage
                      | property_usage property_type
                      )
  ;

property_type
{ track = true; }
  :
    "type" EQ
    ( property_string_type
    | property_number_type
    | property_boolean_type
    | property_ref_type
    ) SEMI
  ;

property_default
{ track = true; }
  :
    (
    "default" EQ (str | num | "true" | "false")
    SEMI
    )
  ;

property_usage
{ track = true; }
  :
    "component" EQ property_component (OR property_component)* SEMI
  ;

property_component
  : ("signal" | "addrmap" | "reg" | "regfile" | "field" | "all")
  ;

property_boolean_type
  : "boolean"
  ;

property_string_type
  : "string"
  ;

property_number_type
  : "number"
  ;

property_ref_type
  : ("addrmap" | "reg" | "regfile" | "field" | "ref")
  ;

component_def
  : ( "addrmap" | "regfile" | "reg" | "field" | "signal" )
    ( id
    |
    )
    LBRACE
      ( component_def
      | explicit_component_inst
      | property_assign
      | enum_def
      )*
    RBRACE
    ( anonymous_component_inst_elems )?
    SEMI
  ;

explicit_component_inst
  : ( "external" )?
    ( "internal" )?
    ( "alias" id )?
    id
    component_inst_elem
    (COMMA component_inst_elem)*
    SEMI
  ;

anonymous_component_inst_elems
  : ("external")?
    component_inst_elem
    (COMMA component_inst_elem)*
  ;

component_inst_elem
  : id
    (array)?
    (EQ  num)?   // reset
    (AT  num)?   // address
    (INC num)? //addr inc
    (MOD num)?  //addr mod
  ;

array
  : LSQ num
    (COLON num)?
    RSQ
  ;

instance_ref
  : instance_ref_elem
    (DOT instance_ref_elem)*
    ( DREF property )?
  ;

instance_ref_elem
  : id
    (LSQ num RSQ)?
  ;

property_assign
  : default_property_assign SEMI
  | explicit_property_assign SEMI
  | post_property_assign SEMI
  ;

default_property_assign
  : "default"
    explicit_property_assign
  ;

explicit_property_assign
  : property_modifier
    property

  | property
    ( EQ property_assign_rhs )
  ;

post_property_assign
  : instance_ref
    ( EQ property_assign_rhs )
  ;

property_assign_rhs
  : property_rvalue_constant
  | "enum" enum_body
  | instance_ref
  | concat
  ;

concat
  : LBRACE
    concat_elem
    (COMMA concat_elem)*
    RBRACE
  ;

concat_elem
  : instance_ref
  | num
  ;

property
  : "name"
  | "desc"
  | "arbiter"
  | "rset"
  | "rclr"
  | "woclr"
  | "woset"

  | "we"
  | "wel"

  | "swwe"
  | "swwel"

  | "hwset"
  | "hwclr"

  | "swmod"
  | "swacc"

  | "sticky"
  | "stickybit"
  | "intr"

  | "anded"
  | "ored"
  | "xored"

  | "counter"
  | "overflow"

  | "sharedextbus"
  | "errextbus"

  | "reset"

  | "littleendian"
  | "bigendian"
  | "rsvdset"
  | "rsvdsetX"
  | "bridge"
  | "shared"
  | "msb0"
  | "lsb0"
  | "sync"
  | "async"
  | "cpuif_reset"
  | "field_reset"
  | "activehigh"
  | "activelow"
  | "singlepulse"
  | "underflow"

  | "incr"
  | "decr"

  | "incrwidth"
  | "decrwidth"

  | "incrvalue"
  | "decrvalue"

  | "saturate"
  | "decrsaturate"

  | "threshold"
  | "decrthreshold"

  | "dontcompare"
  | "donttest"
  | "internal"

  | "alignment"
  | "regwidth"
  | "fieldwidth"
  | "signalwidth"
  | "accesswidth"


  | "sw"
  | "hw"
  | "addressing"
  | "precedence"

  | "encode"
  | "resetsignal"
  | "clock"

  | "mask"
  | "enable"

  | "hwenable"
  | "hwmask"

  | "haltmask"
  | "haltenable"


  | "halt"

  | "next"

  | PROPERTY
  ;

property_rvalue_constant
  : "true"
  | "false"

  | "rw"
  | "wr"
  | "r"
  | "w"
  | "na"

  | "compact"
  | "regalign"
  | "fullalign"

  | "hw"
  | "sw"

  | num
  | str
  ;

property_modifier
  : "posedge"
  | "negedge"
  | "bothedge"
  | "level"
  | "nonsticky"
  ;

id
  : ID
  | INST_ID
  ;

num
  : NUM
  ;

str
  : STR
  ;

enum_def
  : "enum" id
    enum_body
    SEMI
  ;

enum_body
  : LBRACE (enum_entry)* RBRACE
  ;

enum_entry
  : id
    EQ num
    ( LBRACE (enum_property_assign)* RBRACE )?
    SEMI
  ;

enum_property_assign
  : ( "name"
    | "desc"
    )
    EQ str
    SEMI
  ;

class SystemRDLLexer extends Lexer;
options { k = 2; }

protected LETTER : ('a'..'z'|'A'..'Z') ;

WS
  : ( ' '
    | '\t'
    | (
      options { generateAmbigWarnings = false; }
      : '\n'
      | '\r'
      | "\r\n"
      )
    )
  ;

SL_COMMENT
  : "//" (~('\n'|'\r'))*
    ( options { generateAmbigWarnings = false; }
    : '\n'
    | '\r'
    | "\r\n"
    )
  ;

ML_COMMENT
  : "/*" (
         options { generateAmbigWarnings = false; }
         : {LA(2) != '/' }? '*'
         | '\n'
         | {LA(2) != '\n' }? '\r'
         | "\r\n"
         | ~('*'|'\n'|'\r')
         )*
    "*/"
  ;

ID
  : ('\\')?
    (LETTER | '_')(LETTER | '_' | '0'..'9')*
  ;

protected VNUM
  : '\'' ( 'b' ('0' | '1' | '_')+
         | 'd' ('0'..'9' | '_')+
         | 'o' ('0'..'7' | '_')+
         | 'h' ('0'..'9' | 'a'..'f' | 'A'..'F' | '_')+
         )
  ;

NUM
  : ('0'..'9')* (VNUM | ('0'..'9'))
  | "0x" ('0'..'9' | 'a'..'f' | 'A'..'F')+
  ;

protected ESC_DQUOTE
  : "\\\""
  ;

STR
  : '"'
      ( ~('"' | '\n' | '\\')
      | ESC_DQUOTE
      | '\n'
      )*
    '"' // "
  ;

LBRACE : '{' ;
RBRAC  : '}' ;
LSQ    : '[' ;
RSQ    : ']' ;

LPAREN : '(' ;
RPAREN : ')' ;

AT     : '@' ;
OR     : '|' ;
SEMI   : ';' ;
COLON  : ':' ;
COMMA  : ',' ;
DOT    : '.' ;

DREF   : "->";

EQ     : '=' ;
INC    : "+=";
MOD    : "%=";

