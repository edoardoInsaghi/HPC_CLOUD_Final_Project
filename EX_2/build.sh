#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: ./build.sh <numprocs, warmup, iters, size, algo>"
    exit 1
fi

NUM_PROCESSORS=$1
WARMUP=$2
TOTAL=$3
SIZE=$4
ALGO=$5

SCRIPT="Broadcast"

echo "Compiling $SCRIPT..."
mpicc -o ${SCRIPT} ${SCRIPT}.c
if [ $? -ne 0 ]; then
    echo "Failed to compile $SCRIPT."
    exit 1
fi

echo "Running $SCRIPT with $NUM_PROCESSORS processors..."
mpirun -np $NUM_PROCESSORS  --mca coll_tuned_use_dynamic_rules true --mca coll_tuned_bcast_algorithm $ALGO ./${SCRIPT} $WARMUP $TOTAL $SIZE $ALGO
if [ $? -ne 0 ]; then
    echo "Failed to run $SCRIPT."
    exit 1
fi

echo "$SCRIPT completed successfully with $NUM_PROCESSORS processors."
exit 0
