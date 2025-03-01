##############################################################################
# Copyright (c) 2016-24, Lawrence Livermore National Security, LLC and Umpire
# project contributors. See the COPYRIGHT file for details.
#
# SPDX-License-Identifier: (MIT)
##############################################################################

cmake_minimum_required(VERSION 3.14)

project(umpire_examples)


if (NOT BLT_LOADED)
  if (DEFINED BLT_SOURCE_DIR)
    if (NOT EXISTS ${BLT_SOURCE_DIR}/SetupBLT.cmake)
        message(FATAL_ERROR "Given BLT_SOURCE_DIR does not contain SetupBLT.cmake")
    endif()
  else ()
    set (BLT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/blt CACHE PATH "")

    if (NOT EXISTS ${BLT_SOURCE_DIR}/SetupBLT.cmake)
      message(FATAL_ERROR
          "The BLT git submodule is not present. "
          "Either run the following two commands in your git repository: \n"
          "    git submodule init\n"
          "    git submodule update\n"
          "Or add -DBLT_SOURCE_DIR=/path/to/blt to your CMake command." )
    endif ()
  endif ()

  message(STATUS "BLT Source Directory: ${BLT_SOURCE_DIR}")
  include(${BLT_SOURCE_DIR}/SetupBLT.cmake)
endif()




find_package(Umpire REQUIRED)

set (example_depends umpire)

if (UMPIRE_ENABLE_OPENMP_TARGET)
  set (example_depends
      ${example_depends}
      openmp)
endif()

blt_add_executable(
  NAME aligned_allocator
  SOURCES aligned_allocator.cpp
  DEPENDS_ON ${example_depends})

blt_add_executable(
  NAME alloc_access
  SOURCES allocator_access.cpp
  DEPENDS_ON ${example_depends})
list(APPEND umpire_examples alloc_access)

blt_add_executable(
  NAME malloc
  SOURCES malloc.cxx
  DEPENDS_ON ${example_depends})
list(APPEND umpire_examples malloc)

if (UMPIRE_ENABLE_HIP)
  if (UMPIRE_ENABLE_DEVICE_ALLOCATOR)
    blt_add_executable(
      NAME device_allocator_example
      SOURCES device-allocator.cpp
      DEPENDS_ON umpire_device umpire blt::hip)
    list(APPEND umpire_examples device_allocator_example)

    target_compile_options(device_allocator_example PUBLIC -fgpu-rdc)
    blt_add_target_link_flags( TO device_allocator_example FLAGS -fgpu-rdc)
  endif()

    blt_add_executable(
    NAME multi_device
    SOURCES multi_device.cpp
    DEPENDS_ON umpire blt::hip)
  list(APPEND umpire_examples multi_device)
endif()

blt_add_executable(
  NAME get_parent 
  SOURCES get_parent.cpp
  DEPENDS_ON ${example_depends})
list(APPEND umpire_examples get_parent)

blt_add_executable(
  NAME strategy_example
  SOURCES strategy_example.cpp
  DEPENDS_ON ${example_depends})
list(APPEND umpire_examples strategy_example)

blt_add_executable(
  NAME allocator
  SOURCES allocator.cxx
  DEPENDS_ON ${example_depends})
list(APPEND umpire_examples allocator)

blt_add_executable(
  NAME backtrace_example
  SOURCES backtrace_example.cpp
  DEPENDS_ON ${example_depends})

if (NOT WIN32 AND NOT APPLE)
  blt_add_target_link_flags( TO backtrace_example FLAGS -rdynamic)
endif()

list(APPEND umpire_examples backtrace_example)

if (UMPIRE_ENABLE_C)
  blt_add_executable(
    NAME allocator_c
    SOURCES allocator.c
    DEPENDS_ON ${example_depends})
  list(APPEND umpire_examples allocator)
endif ()

blt_add_executable(
  NAME vector_allocator
  SOURCES vector_allocator.cpp
  DEPENDS_ON ${example_depends})
list(APPEND umpire_examples vector_allocator)

blt_add_executable(
  NAME size_limiter
  SOURCES size_limiter.cpp
  DEPENDS_ON ${example_depends})
list(APPEND umpire_examples size_limiter)

blt_add_executable(
  NAME use_after_free
  SOURCES use_after_free.cpp
  DEPENDS_ON ${example_depends})
list(APPEND umpire_examples use_after_free)

if (UMPIRE_ENABLE_CUDA)
  if (UMPIRE_ENABLE_DEVICE_ALLOCATOR)
    blt_add_executable(
      NAME device_allocator_example
      SOURCES device-allocator.cpp
      DEPENDS_ON umpire_device umpire cuda
    )

    set_source_files_properties(
      device-allocator.cpp
      PROPERTIES CUDA_SEPARABLE_COMPILATION On)

    set_target_properties(
      device_allocator_example
      PROPERTIES CUDA_SEPARABLE_COMPILATION On)

    list(APPEND umpire_examples device_allocator_example)
  endif()

    blt_add_executable(
    NAME multi_device
    SOURCES multi_device.cpp
    DEPENDS_ON umpire cuda)

    set_source_files_properties(
      multi_device.cpp
      PROPERTIES CUDA_SEPARABLE_COMPILATION On)

    set_target_properties(
      multi_device
      PROPERTIES CUDA_SEPARABLE_COMPILATION On)

  list(APPEND umpire_examples multi_device)
endif()

install(TARGETS ${umpire_examples} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

#add_subdirectory(tutorial)

#add_subdirectory(cookbook)

#umpire_add_code_checks(PREFIX examples)
