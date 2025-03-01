###############################################################################
# Copyright (c) 2015-2019, Lawrence Livermore National Security, LLC.
#
# Produced at the Lawrence Livermore National Laboratory
#
# LLNL-CODE-716457
#
# All rights reserved.
#
# This file is part of Ascent.
#
# For details, see: http://ascent.readthedocs.io/.
#
# Please also read ascent/LICENSE
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the disclaimer below.
#
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the disclaimer (as noted below) in the
#   documentation and/or other materials provided with the distribution.
#
# * Neither the name of the LLNS/LLNL nor the names of its contributors may
#   be used to endorse or promote products derived from this software without
#   specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY,
# LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
# IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
###############################################################################

###############################################################################
#
# Example that shows how to use an installed instance of Ascent in another
# CMake-based build system.
#
# To build:
#  mkdir build
#  cd build
#  cmake \
#   -DAscent_DIR={ascent install path}   \
#   -DConduit_DIR={conduit install path} \
#   -DVTKH_DIR={vtkh install path}          
#   ../
# make
# ./ascent_render_example
#
# In order to run directly in a sub directory below using-with-cmake in an ascent install, 
# set Ascent_DIR to ../../..
# 
#  mkdir build
#  cd build
#  cmake .. -DAscent_DIR=../../..
#  make
#  ./ascent_render_example
#
###############################################################################

cmake_minimum_required(VERSION 3.14)

project(using_with_cmake)

#
# Use CMake's find_package to import ascent's targets
#
# PATHS is just a hint if someone runs this example from the Ascent install
# tree without setting up an environment hint to find Ascent
find_package(Ascent REQUIRED)
#find_package(MPI REQUIRED)
#find_package(Ascent REQUIRED
#             PATHS ${CMAKE_SOURCE_DIR}/../../../)

# create our example
add_executable(ascent_render_example ascent_render_example.cpp)

# link to ascent
target_link_libraries(ascent_render_example ascent::ascent)

# create our cinema example
add_executable(ascent_render_cinema_example ascent_render_cinema_example.cpp)

# link to ascent
target_link_libraries(ascent_render_cinema_example ascent::ascent)


