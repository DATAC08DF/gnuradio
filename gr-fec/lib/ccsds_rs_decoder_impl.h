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

#ifndef INCLUDED_FEC_CCSDS_RS_DECODER_IMPL_H
#define INCLUDED_FEC_CCSDS_RS_DECODER_IMPL_H

#include <gnuradio/fec/ccsds_rs_decoder.h>
extern "C" {
#include "reed-solomon/fixed.h"
}

/* ########### TODO: CCSDS dual-basis SHOULD BE A HIER BLOCK with 
MAP[Tal1map] => CCSDS Conventional RS => MAP[Talmap]
############# */

namespace gr {
  namespace fec {
    namespace code {

      class FEC_API ccsds_rs_decoder_impl : public ccsds_rs_decoder
      {
      private:
        int d_error_count;
        int d_input_size;
        DTYPE d_cbuffer[NN];  // buffer for each incoming codeword

        //plug into the generic fec api
        void generic_work(void *inbuffer, void *outbuffer);

      public:
        ccsds_rs_decoder_impl(unsigned int frame_size );
        ~ccsds_rs_decoder_impl();

        double rate() 
        { 
          return static_cast<double>(get_output_size()) / get_input_size(); 
        }

	      bool set_frame_size(unsigned int frame_size)
	      {
          if(frame_size % NN != 0) {
            GR_LOG_ERROR(d_logger, boost::format("Frame size (%1% bytes) must be a "
                                                 "multiple of the RS codeword "
                                                 "size, %2% bytes") % frame_size % NN);
            throw std::runtime_error("ccsds_rs_decoder: cannot set frame size.");
          }
          d_input_size = frame_size;
          return true;
	      }

	      int error_count() { return d_error_count; }

        int get_output_size() 
        { 
          return d_input_size - (d_input_size / NN) * NROOTS; 
        }
        int get_input_size() { return d_input_size; }
        int get_input_item_size() { return MM / 8; }
        float get_shift() {return 0; }
        const char* get_input_conversion() { return "uchar"; }
      };

    } /* namespace code */
  } /* namespace fec */
} /* namespace gr */

#endif /* INCLUDED_FEC_CCSDS_RS_DECODER_IMPL_H */
