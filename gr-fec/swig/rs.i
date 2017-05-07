/* -*- c++ -*- */
/*
 * Copyright 2015 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#if PY_MAJOR_VERSION >= 3
    #define PyInt_FromLong PyLong_FromLong
#endif

/* export Taltab and Tal1tab as tuples */
/* TODO: alias from cvar. to, e.g. TALTAB module attribute */
%typemap(varout) unsigned char [ANY] {
    $result = PyTuple_New($1_dim0);
    for (int i = 0; i < $1_dim0; ++i) {
        PyTuple_SET_ITEM($result, i, PyInt_FromLong((long)$1[i]));
    }
}

%{
#include "gnuradio/fec/rs.h"
%}
%include "gnuradio/fec/rs.h"

%pythoncode %{
TALTAB = cvar.Taltab
TAL1TAB = cvar.Tal1tab
%}