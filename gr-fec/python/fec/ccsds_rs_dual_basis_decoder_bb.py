#!/usr/bin/env python
#
# Copyright 2014 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

from gnuradio import gr, blocks, digital
import fec_swig as fec
import math

class ccsds_rs_dual_basis_decoder_bb(gr.hier_block2):
    """Execute CCSDS RS decoder over dual-basis"""
    def __init__(self, decoder_obj):
        super(ccsds_rs_dual_basis_decoder_bb, self).__init__(
            "Capillary Threaded Decoder",
            gr.io_signature(1, 1, gr.sizeof_char),
            gr.io_signature(1, 1, gr.sizeof_char))

        # TODO: use one of the other decoders (extended? threaded?)
        decoder_block = fec.decoder(decoder_obj, gr.sizeof_char, gr.sizeof_char)
        
        # invert the encoder input and output maps for decoding
        input_mapping = fec.TAL1TAB
        output_mapping = fec.TALTAB

        input_map = digital.map_bb(input_mapping)
        output_map = digital.map_bb(output_mapping)
        self.connect(self, input_map, decoder_block, output_map, self)
