#!/bin/bash

#SBATCH --job-name=get_data
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=128
#SBATCH --cpus-per-task=1
#SBATCH --time=2:00:00
#SBATCH --partition=EPYC
#SBATCH --output=data_linear.out
#SBATCH --error=data_linear.err
#SBATCH --exclusive

ALGORITHM="1"
SIZE="2000"
MPI_PROCS=($(seq 2 1 256))
ALLOCATIONS=("core" "node")
OUTPUT_FILE="data_linear.csv"

echo "Algorithm,MPI_Processes,Data_Size,Allocation,Latency" > $OUTPUT_FILE

mpicc -o Broadcast Broadcast.c

for num_procs in "${MPI_PROCS[@]}"; do
        for allocation in "${ALLOCATIONS[@]}"; do
        output=$(mpirun -n $num_procs --map-by $allocation ./Broadcast 5000 20000 ${SIZE} ${ALGORITHM})
        output="$ALGORITHM,$num_procs,$SIZE,$allocation,$output"
        echo "$output" >> $OUTPUT_FILE
        done
done