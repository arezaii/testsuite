#!/bin/bash

. ../../setup.sh
spackLoadUnique ascent

if ! command -v cmake >/dev/null 2>&1 ; then
  spackLoadUniqueNoX cmake
fi
