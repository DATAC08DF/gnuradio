# Copyright 2010-2012 Free Software Foundation, Inc.
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

########################################################################
# This file included, use CMake directory variables
########################################################################
#MSVC workaround: we cant have dynamically sized arrays.
#So ifdef a max array bounds that is larger than NN and NROOTS
#Its a bit of a hack, but if you look at the code, its so full of ifdefs,
#and lacks optimization where it should be pre-allocating these arrays.
if(MSVC)
    set_source_files_properties(
        ${CMAKE_CURRENT_SOURCE_DIR}/exercise.c
        ${CMAKE_CURRENT_SOURCE_DIR}/decode_rs.c
        PROPERTIES COMPILE_DEFINITIONS "MAX_ARRAY=256;"
    )
endif(MSVC)

# These are really template files
set(gr_fec_rs_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/encode_rs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/decode_rs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/init_rs.c
)

########################################################################
# Generate sources
########################################################################

# CCSDS tables
add_executable(gen_ccsds 
  ${CMAKE_CURRENT_SOURCE_DIR}/gen_ccsds.c
  ${CMAKE_CURRENT_SOURCE_DIR}/init_rs.c)
target_include_directories(gen_ccsds PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ccsds.c
  COMMAND gen_ccsds > ${CMAKE_CURRENT_BINARY_DIR}/ccsds.c
  COMMENT "Generating ccsds.c"
)

add_executable(gen_ccsds_tal ${CMAKE_CURRENT_SOURCE_DIR}/gen_ccsds_tal.c)
target_include_directories(gen_ccsds_tal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/ccsds_tal.c
  COMMAND gen_ccsds_tal > ${CMAKE_CURRENT_BINARY_DIR}/ccsds_tal.c
  COMMENT "Generating ccsds_tal.c"
)

########################################################################
# Setup library sources and includes
########################################################################
# create a lib for each type of RS codec, don't do CCSDS explicitly,
# rather add ccsds and ccsds_tal files to rs-8 (fixed) lib
add_library(gnuradio-fec-rs-8 SHARED 
    ${gr_fec_rs_sources}
    ${CMAKE_CURRENT_BINARY_DIR}/ccsds.c 
    ${CMAKE_CURRENT_BINARY_DIR}/ccsds_tal.c)
target_compile_definitions(gnuradio-fec-rs-8 PUBLIC -DFIXED)
add_library(gnuradio-fec-rs-int SHARED ${gr_fec_rs_sources})
target_compile_definitions(gnuradio-fec-rs-int PUBLIC -DBIGSYM)
add_library(gnuradio-fec-rs-char SHARED ${gr_fec_rs_sources})
target_compile_definitions(gnuradio-fec-rs-char PUBLIC -DCHAR)

#GR_LIBRARY_FOO(gnuradio-fec-rs-8 RUNTIME_COMPONENT "fec_runtime" DEVEL_COMPONENT "fec_devel")
#GR_LIBRARY_FOO(gnuradio-fec-rs-int RUNTIME_COMPONENT "fec_runtime" DEVEL_COMPONENT "fec_devel")
#GR_LIBRARY_FOO(gnuradio-fec-rs-char RUNTIME_COMPONENT "fec_runtime" DEVEL_COMPONENT "fec_devel")

list(APPEND gnuradio_fec_libs 
    gnuradio-fec-rs-8
    gnuradio-fec-rs-int
    gnuradio-fec-rs-char)

########################################################################
# Register unit tests
########################################################################

if(ENABLE_TESTING)
    # char is the only active test by default
    add_executable(gr_fec_rstest_char
        ${gr_fec_rs_sources}
        ${CMAKE_CURRENT_SOURCE_DIR}/rstest.c
        ${CMAKE_CURRENT_SOURCE_DIR}/exercise.c
    )
    target_compile_definitions(gr_fec_rstest_char PUBLIC -DCHAR)
    add_test(gr-fec-reed-solomon-char-test gr_fec_rstest_char)
endif(ENABLE_TESTING)
