/*
 * Hydrogen
 * Copyright(c) 2002-2008 by Alex >Comix< Cominu [comix@users.sourceforge.net]
 *
 * http://www.hydrogen-music.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY, without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <hydrogen/SeqEvent.h>
#include <cmath>

#define THIS_NAMESPACE t_SeqEvent
#include "test_macros.h"

using namespace H2Core;

namespace THIS_NAMESPACE
{

    struct Fixture
    {
	SeqEvent ev;  // This is the "normal" one.
	SeqEvent xev; // This is the odd one.

	Fixture() : ev(), xev() {

	    xev.frame = 0xFEEEEEEE;
	    xev.type = SeqEvent::ALL_OFF;
	    xev.quantize = true;
	    xev.instrument_index = 0xFF;
	}

	~Fixture() {}
    };

} // namespace THIS_NAMESPACE

TEST_BEGIN( Fixture );

TEST_CASE( 001_defaults )
{
    // Test the defaults
    CK( ev.frame == 0 );
    CK( ev.type == SeqEvent::NOTE_ON );
    CK( ev.quantize == false );
    CK( ev.instrument_index == 0 );
}

TEST_CASE( 002_copy )
{
    SeqEvent cp;
    cp = ev;
    CK( cp.frame == ev.frame );
    CK( cp.type == ev.type );
    // CK( cp.note == ev.note );  // TODO
    CK( cp.quantize == ev.quantize );
    CK( cp.instrument_index == ev.instrument_index );

    cp = xev;
    CK( cp.frame == xev.frame );
    CK( cp.type == xev.type );
    // CK( cp.note == xev.note ); // TODO
    CK( cp.quantize == xev.quantize );
    CK( cp.instrument_index == xev.instrument_index );

    // Verify independence
    ++cp.frame;
    cp.type = SeqEvent::NOTE_OFF;
    cp.quantize = !cp.quantize;
    ++cp.instrument_index;
    CK( cp.frame != xev.frame );
    CK( cp.type != xev.type );
    // CK( cp.note != xev.note ); // TODO
    CK( cp.quantize != xev.quantize );
    CK( cp.instrument_index != xev.instrument_index );

    xev = ev;
    CK( ev.frame == xev.frame );
    CK( ev.type == xev.type );
    // CK( ev.note == xev.note ); // TODO
    CK( ev.quantize == xev.quantize );
    CK( ev.instrument_index == xev.instrument_index );

    // Confirm xev
    CK( xev.frame == 0 );
    CK( xev.type == SeqEvent::NOTE_ON );
    CK( xev.quantize == false );
    CK( xev.instrument_index == 0 );
}

TEST_CASE( 003_less )
{
    CK( less(ev, xev) );    
    CK( ! less(xev, ev) );
    xev.frame = ev.frame;
    CK( ! less(ev, xev) );
    CK( ! less(ev, xev) );
    ev.frame = xev.frame+1;
    CK( ! less(ev, xev) );
    CK( less(xev, ev) );
}

TEST_END()