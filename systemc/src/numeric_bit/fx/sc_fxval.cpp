/******************************************************************************
    Copyright (c) 1996-2001 Synopsys, Inc.    ALL RIGHTS RESERVED

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Community License Software Download and
  Use License Version 1.2 (the "License"); you may not use this file except
  in compliance with such restrictions and limitations. You may obtain
  instructions on how to receive a copy of the License at
  http://www.systemc.org/. Software distributed by Original Contributor
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

******************************************************************************/

/******************************************************************************

    sc_fxval.cpp - 

    Original Author: Martin Janssen. Synopsys, Inc. (mjanssen@synopsys.com)

******************************************************************************/

/******************************************************************************

    MODIFICATION LOG - modifiers, enter your name, affliation and
    changes you are making here:

    Modifier Name & Affiliation:
    Description of Modification:
    

******************************************************************************/


#include <ctype.h>
#include <math.h>
#include <float.h>
#include <string.h>

#include "sc_fxval.h"

#if defined(__BCPLUSPLUS__)
#pragma hdrstop
#endif


// ----------------------------------------------------------------------------
//  CLASS : sc_fxval
//
//  Fixed-point value type; arbitrary precision.
// ----------------------------------------------------------------------------

// explicit conversion to character string

const sc_string
sc_fxval::to_string() const
{
    return sc_string( _rep->to_string( SC_DEC, SC_E ) );
}

const sc_string
sc_fxval::to_string( sc_numrep numrep ) const
{
    return sc_string( _rep->to_string( numrep, SC_E ) );
}

const sc_string
sc_fxval::to_string( sc_fmt fmt ) const
{
    return sc_string( _rep->to_string( SC_DEC, fmt ) );
}

const sc_string
sc_fxval::to_string( sc_numrep numrep, sc_fmt fmt ) const
{
    return sc_string( _rep->to_string( numrep, fmt ) );
}


const sc_string
sc_fxval::to_dec() const
{
    return sc_string( _rep->to_string( SC_DEC, SC_E ) );
}

const sc_string
sc_fxval::to_bin() const
{
    return sc_string( _rep->to_string( SC_BIN, SC_E ) );
}

const sc_string
sc_fxval::to_oct() const
{
    return sc_string( _rep->to_string( SC_OCT, SC_E ) );
}

const sc_string
sc_fxval::to_hex() const
{
    return sc_string( _rep->to_string( SC_HEX, SC_E ) );
}


// print or dump content

void
sc_fxval::print( ostream& os ) const
{
    _rep->print( os );
}

void
sc_fxval::dump( ostream& os ) const
{
    os << "sc_fxval" << endl;
    os << "(" << endl;
    os << "rep = ";
    _rep->dump( os );
    // TO BE COMPLETED
    // os << "r_flag   = " << _r_flag << endl;
    // os << "observer = ";
    // if( _observer != 0 )
    //     _observer->dump( os );
    // else
    //     os << "0" << endl;
    os << ")" << endl;
}


// protected methods and friend functions

sc_fxval_observer*
sc_fxval::lock_observer() const
{
    _SC_ASSERT( _observer != 0, "lock observer failed" );
    sc_fxval_observer* tmp = _observer;
    _observer = 0;
    return tmp;
}

void
sc_fxval::unlock_observer( sc_fxval_observer* observer_ ) const
{
    _SC_ASSERT( observer_ != 0, "unlock observer failed" );
    _observer = observer_;
}


// ----------------------------------------------------------------------------
//  CLASS : sc_fxval_fast
//
//  Fixed-point value types; limited precision.
// ----------------------------------------------------------------------------

static
void
print_dec( scfx_string& s, scfx_ieee_double id, sc_fmt fmt )
{
    if( id.negative() != 0 )
    {
	id.negative( 0 );
	s += '-';
    }

    if( id.is_zero() )
    {
	s += '0';
	return;
    }

    // split 'id' into its integer and fractional part

    double int_part;
    double frac_part = modf( static_cast<double>( id ), &int_part );

    int i;

    // print integer part

    int int_digits = 0;
    int int_zeros  = 0;
    
    if( int_part != 0.0 )
    {
	int_digits = (int) ceil( log10( int_part + 1.0 ) );

	int len = s.length();
	s.append( int_digits );

	bool zero_digits = ( frac_part == 0.0 && fmt != SC_F );

	for( i = int_digits + len - 1; i >= len; i-- )
	{
	    unsigned int remainder = (unsigned int) fmod( int_part, 10.0 );
	    s[i] = '0' + remainder;
	    
	    if( zero_digits )
	    {
		if( remainder == 0 )
		    int_zeros ++;
		else
		    zero_digits = false;
	    }

	    int_part /= 10.0;
	}

	// discard trailing zeros from int_part
	s.discard( int_zeros );

	if( s[len] == '0' )
	{
	    // int_digits was overestimated by one
	    s.remove( len );
	    -- int_digits;
	}
    }

    // print fractional part

    int frac_digits = 0;
    int frac_zeros  = 0;

    if( frac_part != 0.0 )
    {
	s += '.';

	bool zero_digits = ( int_digits == 0 && fmt != SC_F );

	frac_zeros = (int) floor( - log10( frac_part + DBL_EPSILON ) );

	frac_part *= pow( 10.0, frac_zeros );
	
	frac_digits = frac_zeros;
	if( ! zero_digits )
	{
	    for( i = 0; i < frac_zeros; i ++ )
		s += '0';
	    frac_zeros = 0;
	}

	while( frac_part != 0.0 )
	{
	    frac_part *= 10.0;
	    int n = static_cast<int>( frac_part );
	
	    if( zero_digits )
	    {
		if( n == 0 )
		    frac_zeros ++;
		else
		    zero_digits = false;
	    }
	
	    if( ! zero_digits )
		s += '0' + n;

	    frac_part -= n;
	    frac_digits ++;
	}
    }

    // print exponent
    
    if( fmt != SC_F )
    {
        if( frac_digits == 0 )
	    scfx_print_exp( s, int_zeros );
	else if( int_digits == 0 )
	    scfx_print_exp( s, - frac_zeros );
    }
}


static
void
print_other( scfx_string& s, const scfx_ieee_double& id,
	     sc_numrep numrep, sc_fmt fmt, const scfx_params* params )
{
    scfx_ieee_double id2 = id;

    sc_numrep numrep2 = numrep;

    bool numrep_is_sm = ( numrep == SC_BIN_SM ||
			  numrep == SC_OCT_SM ||
			  numrep == SC_HEX_SM );

    if( numrep_is_sm )
    {
	if( id2.negative() != 0 )
	{
	    s += '-';
	    id2.negative( 0 );
	}
	switch( numrep )
	{
	    case SC_BIN_SM:
		numrep2 = SC_BIN_US;
		break;
	    case SC_OCT_SM:
		numrep2 = SC_OCT_US;
		break;
	    case SC_HEX_SM:
		numrep2 = SC_HEX_US;
		break;
	    default:
		;
	}
    }

    scfx_print_prefix( s, numrep );

    numrep = numrep2;

    sc_fxval_fast a( id2 );

    int msb, lsb;

    if( params != 0 )
    {
	msb = params->iwl() - 1;
	lsb = params->iwl() - params->wl();

	if( params->enc() == SC_TC &&
	    ( numrep == SC_BIN_US ||
	      numrep == SC_OCT_US ||
	      numrep == SC_HEX_US ) &&
	    ! numrep_is_sm &&
	    params->wl() > 1 )
	    -- msb;
	else if( params->enc() == SC_US &&
	    ( numrep == SC_BIN ||
	      numrep == SC_OCT ||
	      numrep == SC_HEX ||
	      numrep == SC_CSD ) )
	    ++ msb;
    }
    else
    {
	if( a.is_zero() )
	{
	    msb = 0;
	    lsb = 0;
	}
	else
	{
	    msb = id2.exponent() + 1;
	    while( a.get_bit( msb ) == a.get_bit( msb - 1 ) )
		-- msb;

	    if( numrep == SC_BIN_US ||
		numrep == SC_OCT_US ||
		numrep == SC_HEX_US )
		-- msb;

	    lsb = id2.exponent() - 52;
	    while( ! a.get_bit( lsb ) )
		++ lsb;
	}
    }

    int step;

    switch( numrep )
    {
	case SC_BIN:
	case SC_BIN_US:
	case SC_CSD:
	    step = 1;
	   break;
	case SC_OCT:
	case SC_OCT_US:
	    step = 3;
	    break;
	case SC_HEX:
	case SC_HEX_US:
	    step = 4;
	    break;
	default:
	    step = 0;
    }

    msb = (int) ceil( double( msb + 1 ) / step ) * step - 1;

    lsb = (int) floor( double( lsb ) / step ) * step;

    if( msb < 0 )
    {
	s += '.';
	if( fmt == SC_F )
	{
	    int sign = ( id2.negative() != 0 ) ? ( 1 << step ) - 1 : 0;
	    for( int i = ( msb + 1 ) / step; i < 0; i ++ )
	    {
		if( sign < 10 )
		    s += sign + '0';
		else
		    s += sign + 'a' - 10;
	    }
	}
    }

    int i = msb;
    while( i >= lsb )
    {
        int value = 0;
        for( int j = step - 1; j >= 0; -- j )
	{
            value += static_cast<int>( a.get_bit( i ) ) << j;
            -- i;
        }
        if( value < 10 )
            s += value + '0';
	else
            s += value + 'a' - 10;
	if( i == -1 )
	    s += '.';
    }

    if( lsb > 0 && fmt == SC_F )
    {
	for( int i = lsb / step; i > 0; i -- )
	    s += '0';
    }

    if( s[s.length() - 1] == '.' )
	s.discard( 1 );

    if( fmt != SC_F )
    {
	if( msb < 0 )
	    scfx_print_exp( s, ( msb + 1 ) / step );
	else if( lsb > 0 )
	    scfx_print_exp( s, lsb / step );
    }

    if( numrep == SC_CSD )
	scfx_tc2csd( s );
}


const char*
to_string( const scfx_ieee_double& id, sc_numrep numrep, sc_fmt fmt,
	   const scfx_params* params = 0 )
{
    static scfx_string s;

    s.clear();

    if( id.is_nan() )
        scfx_print_nan( s );
    else if( id.is_inf() )
        scfx_print_inf( s, id.negative() );
    else if( id.negative() && ! id.is_zero() &&
	     ( numrep == SC_BIN_US ||
	       numrep == SC_OCT_US ||
	       numrep == SC_HEX_US ) )
        s += "negative";
    else if( numrep == SC_DEC )
        ::print_dec( s, id, fmt );
    else
        ::print_other( s, id, numrep, fmt, params );

    return s;
}


// explicit conversion to character string

const sc_string
sc_fxval_fast::to_string() const
{
    return sc_string( ::to_string( _val, SC_DEC, SC_E ) );
}

const sc_string
sc_fxval_fast::to_string( sc_numrep numrep ) const
{
    return sc_string( ::to_string( _val, numrep, SC_E ) );
}

const sc_string
sc_fxval_fast::to_string( sc_fmt fmt ) const
{
    return sc_string( ::to_string( _val, SC_DEC, fmt ) );
}

const sc_string
sc_fxval_fast::to_string( sc_numrep numrep, sc_fmt fmt ) const
{
    return sc_string( ::to_string( _val, numrep, fmt ) );
}


const sc_string
sc_fxval_fast::to_dec() const
{
    return sc_string( ::to_string( _val, SC_DEC, SC_E ) );
}

const sc_string
sc_fxval_fast::to_bin() const
{
    return sc_string( ::to_string( _val, SC_BIN, SC_E ) );
}

const sc_string
sc_fxval_fast::to_oct() const
{
    return sc_string( ::to_string( _val, SC_OCT, SC_E ) );
}

const sc_string
sc_fxval_fast::to_hex() const
{
    return sc_string( ::to_string( _val, SC_HEX, SC_E ) );
}


// print or dump content

void
sc_fxval_fast::print( ostream& os ) const
{
    os << ::to_string( _val, SC_DEC, SC_E );
}

void
sc_fxval_fast::dump( ostream& os ) const
{
    os << "sc_fxval_fast" << endl;
    os << "(" << endl;
    os << "val = " << _val << endl;
    // TO BE COMPLETED
    // os << "r_flag   = " << _r_flag << endl;
    // os << "observer = ";
    // if( _observer != 0 )
    //     _observer->dump( os );
    // else
    //     os << "0" << endl;
    os << ")" << endl;
}


// internal use only;
bool
sc_fxval_fast::get_bit( int i ) const
{
    scfx_ieee_double id( _val );
    if( id.is_zero() || id.is_nan() || id.is_inf() )
        return false;

    // convert to two's complement

    unsigned int m0 = id.mantissa0();
    unsigned int m1 = id.mantissa1();

    if( id.is_normal() )
        m0 += 1U << 20;

    if( id.negative() != 0 )
    {
	m0 = ~ m0;
	m1 = ~ m1;
	unsigned int tmp = m1;
	m1 += 1U;
	if( m1 <= tmp )
	    m0 += 1U;
    }

    // get the right bit

    int j = i - id.exponent();
    if( ( j += 20 ) >= 32 )
        return ( ( m0 & 1U << 31 ) != 0 );
    else if( j >= 0 )
        return ( ( m0 & 1U << j ) != 0 );
    else if( ( j += 32 ) >= 0 )
        return ( ( m1 & 1U << j ) != 0 );
    else
        return false;
}


// protected methods and friend functions

sc_fxval_fast_observer*
sc_fxval_fast::lock_observer() const
{
    _SC_ASSERT( _observer != 0, "lock observer failed" );
    sc_fxval_fast_observer* tmp = _observer;
    _observer = 0;
    return tmp;
}

void
sc_fxval_fast::unlock_observer( sc_fxval_fast_observer* observer_ ) const
{
    _SC_ASSERT( observer_ != 0, "unlock observer failed" );
    _observer = observer_;
}


#define _SCFX_FAIL_IF(cnd)                                                    \
{                                                                             \
    if( ( cnd ) )                                                             \
        return static_cast<double>( scfx_ieee_double::nan() );                \
}

double
sc_fxval_fast::from_string( const char* s )
{
    _SCFX_FAIL_IF( s == 0 || *s == 0 );

    scfx_string s2;
    s2 += s;
    s2 += '\0';

    bool sign_char;
    int sign = scfx_parse_sign( s, sign_char );

    sc_numrep numrep = scfx_parse_prefix( s );

    int base = 0;

    switch( numrep )
    {
	case SC_DEC:
	{
	    base = 10;
	    if( scfx_is_nan( s ) )  // special case: NaN
		return static_cast<double>( scfx_ieee_double::nan() );
	    if( scfx_is_inf( s ) )  // special case: Infinity
		return static_cast<double>( scfx_ieee_double::inf( sign ) );
	    break;
	}
	case SC_BIN:
	case SC_BIN_US:
	{
	    _SCFX_FAIL_IF( sign_char );
	    base = 2;
	    break;
	}
	
	case SC_BIN_SM:
	{
	    base = 2;
	    break;
	}
	case SC_OCT:
	case SC_OCT_US:
	{
	    _SCFX_FAIL_IF( sign_char );
	    base = 8;
	    break;
	}
	case SC_OCT_SM:
	{
	    base = 8;
	    break;
	}
	case SC_HEX:
	case SC_HEX_US:
	{
	    _SCFX_FAIL_IF( sign_char );
	    base = 16;
	    break;
	}
	case SC_HEX_SM:
	{
	    base = 16;
	    break;
	}
	case SC_CSD:
	{
	    _SCFX_FAIL_IF( sign_char );
	    base = 2;
	    scfx_csd2tc( s2 );
	    s = (const char*) s2 + 4;
	    numrep = SC_BIN;
	    break;
	}
       default:;// Martin, what is default???
    }

    //
    // find end of mantissa and count the digits and points
    //

    const char *end = s;
    bool based_point = false;
    int int_digits = 0;
    int frac_digits = 0;

    while( *end )
    {
	if( scfx_exp_start( end ) )
	    break;
	
	if( *end == '.' )
	{
	    _SCFX_FAIL_IF( based_point );
	    based_point = true;
	}
	else
	{
	    _SCFX_FAIL_IF( ! scfx_is_digit( *end, numrep ) );
	    if( based_point )
		frac_digits ++;
	    else
		int_digits ++;
	}

	end ++;
    }

    _SCFX_FAIL_IF( int_digits == 0 && frac_digits == 0 );

    // [ exponent ]
    
    int exponent = 0;

    if( *end )
    {
	for( const char *e = end + 2; *e; e ++ )
	    _SCFX_FAIL_IF( ! scfx_is_digit( *e, SC_DEC ) );
	exponent = atoi( end + 1 );
    }

    //
    // convert the mantissa
    //

    double integer = 0.0;

    if( int_digits != 0 )
    {

	bool first_digit = true;

	for( ; s < end; s ++ )
	{
	    if( *s == '.' )
		break;
	    
	    if( first_digit )
	    {
		integer = scfx_to_digit( *s, numrep );
		switch( numrep )
		{
		    case SC_BIN:
		    case SC_OCT:
		    case SC_HEX:
		    {
			if( integer >= ( base >> 1 ) )
			    integer -= base;  // two's complement
			break;
		    }
		    default:
			;
		}
		first_digit = false;
	    }
            else
	    {
		integer *= base;
		integer += scfx_to_digit( *s, numrep );
	    }
	}
    }

    // [ . fraction ]

    double fraction = 0.0;
    
    if( frac_digits != 0 )
    {
	s ++;  // skip '.'

	bool first_digit = ( int_digits == 0 );

	double scale = 1.0;

	for( ; s < end; s ++ )
	{
	    scale /= base;
	    
	    if( first_digit )
	    {
		fraction = scfx_to_digit( *s, numrep );
		switch( numrep )
		{
		    case SC_BIN:
		    case SC_OCT:
		    case SC_HEX:
		    {
			if( fraction >= ( base >> 1 ) )
			    fraction -= base;  // two's complement
			break;
		    }
		    default:
			;
		}
		fraction *= scale;
		first_digit = false;
	    }
	    else
		fraction += scfx_to_digit( *s, numrep ) * scale;
	}
    }

    double exp = ( exponent != 0 ) ? pow( (double) base, (double) exponent )
	                           : 1;

    return ( sign * ( integer + fraction ) * exp );
}

#undef _SCFX_FAIL_IF


// Taf!