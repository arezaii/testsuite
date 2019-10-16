#!/bin/bash
. ./setup.sh
#ldd ./lulesh.host
ulimit -c unlimited
mpirun -np 8 ./lulesh.host -i 4
result=$?
if [ $result = 0 ]; then
  echo "Running with TAU:" 
  mpirun -np 8 tau_exec -ebs ./lulesh.host -i 4 
  result=$?
  echo "To view performance data, please use:"
  echo "pprof -a | more "
fi
exit $result

