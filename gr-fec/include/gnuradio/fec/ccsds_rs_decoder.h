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

#ifndef INCLUDED_FEC_CCSDS_RS_DECODER_H
#define INCLUDED_FEC_CCSDS_RS_DECODER_H

#include <gnuradio/fec/api.h>
#include <gnuradio/fec/generic_decoder.h>

namespace gr {
  namespace fec {
    namespace code {

      /*!
       * \brief CCSDS Reed-Solomon Decoding class.
       * \ingroup error_coding_blk
       *
       * \details
       * A CCSDS Reed-Solomon decoder class.
       */
      class FEC_API ccsds_rs_decoder : virtual public generic_decoder
      {
      public:

        /*!
         * Build a CCSDS Reed-Solomon decoding FEC API object.
         *
         */
        static generic_decoder::sptr make(unsigned int frame_size=0);
        /*!
         * Returns the coding rate of this encoder (it will always be < 1).
         */
        virtual double rate() = 0;

        /*!
         * Returns the total error count
         */
        virtual int error_count() = 0;

        /*!
         * Updates the size of a decoded frame, must be integer mult of RS codeword size.
         */
        virtual bool set_frame_size(unsigned int frame_size) = 0;

      };

    } /* namespace code */
  } /* namespace fec */
} /* namespace gr */

#endif /* INCLUDED_FEC_REPETITION_DECODER_H */
