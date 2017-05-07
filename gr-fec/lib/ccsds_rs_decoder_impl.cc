/* -*- c++ -*- */
/*
 * Copyright 2014 Free Software Foundation, Inc.
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ccsds_rs_decoder_impl.h"

namespace gr {
  namespace fec {
    namespace code {

      ccsds_rs_decoder::sptr
      ccsds_rs_decoder::make(unsigned int frame_size)
      {
        return generic_decoder::sptr(new ccsds_rs_decoder_impl(frame_size));
      }

      ccsds_rs_decoder_impl::ccsds_rs_decoder_impl(unsigned int frame_size)
        : generic_decoder("ccsds_rs_decoder")
        , d_error_count(0)
        , d_input_size(NN)
      {
        if (frame_size > 0) set_frame_size(frame_size);
      }

      ccsds_rs_decoder_impl::~ccsds_rs_decoder_impl()
      {
      }

      void
      ccsds_rs_decoder_impl::generic_work(void *inbuffer, void *outbuffer)
      {
        // DTYPE = unsigned char in fixed.h
        const DTYPE *in = (const unsigned char *)inbuffer;
        unsigned char *out = (unsigned char *) outbuffer;

        d_error_count = 0;
        // TODO: check input/output sizes?
        for (const DTYPE *end = in + d_input_size; in < end; in += NN) {
          std::copy(in, in + NN, d_cbuffer);            // TODO: can this be done w/o temp buffer?
          d_error_count += DECODE_RS(d_cbuffer, 0, 0);  // DECODER operates in-place
          out = std::copy(d_cbuffer, d_cbuffer + NN - NROOTS, out);
        }
      }

    } /* namespace code */
  } /* namespace fec */
} /* namespace gr */
