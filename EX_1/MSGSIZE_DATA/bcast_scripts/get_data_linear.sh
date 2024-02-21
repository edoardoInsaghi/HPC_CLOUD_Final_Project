#!/bin/bash

#SBATCH --job-name=get_data_bcast_linear
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=128
#SBATCH --cpus-per-task=1
#SBATCH --time=2:00:00
#SBATCH --partition=EPYC
#SBATCH --output=bcast_data_linear.out
#SBATCH --error=bcast_data_linear.err
#SBATCH --exclusive   

ALGORITHM="1"
MPI_PROCS=("2" "4" "8" "16" "32" "64" "128")
ALLOCATIONS=("socket" "node")
OUTPUT_FILE="data_bcast_linear.csv"

echo "Algorithm,MPI_Procs,Allocation,Size,Avg_Latency" > $OUTPUT_FILE

for num_procs in "${MPI_PROCS[@]}"; do
    for allocation in "${ALLOCATIONS[@]}"; do
        output=$(mpirun -n $num_procs --map-by $allocation --mca coll_tuned_use_dynamic_rules true --mca coll_tuned_bcast_algorithm $ALGORITHM ../osu_bcast -x 1000 -i 20000 -m 1:1048576 | awk -v algo=$ALGORITHM -v num_procs=$num_procs -v allocation=$allocation -F' ' '{if ($1 ~ /^[0-9]+$/) print algo "," num_procs "," allocation "," $1 "," $2}')
        echo "$output" >> $OUTPUT_FILE
    done
done
