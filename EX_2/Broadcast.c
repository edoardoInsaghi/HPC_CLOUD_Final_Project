#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>


void broadcast_flat_tree(void* data, int count, MPI_Datatype datatype,
                         int rank, int size, MPI_Comm communicator)
{
    int i;
    if (rank == 0)
    {   
        for (i = 1; i < size; i++) 
        {    
            MPI_Send(data, count, datatype, i, 42, communicator);
        }
    } 
    else 
    {
        MPI_Recv(data, count, datatype, 0, 42, communicator, MPI_STATUS_IGNORE);   
    }
}


void broadcast_chain_tree(void* data, int count, MPI_Datatype datatype,
                          int rank, int size, MPI_Comm communicator)
{
    if(rank == 0) 
    {
        MPI_Send(data, count, datatype, 1, 42, communicator);
    }
    else if(rank == size-1)
    {
        MPI_Recv(data, count, datatype, rank-1, 42, communicator, MPI_STATUS_IGNORE);
    }
    else
    {
        MPI_Recv(data, count, datatype, rank-1, 42, communicator, MPI_STATUS_IGNORE);
        MPI_Send(data, count, datatype, rank+1, 42, communicator);
    }
}


void broadcast_binary_tree(void* data, int count, MPI_Datatype datatype,
                           int rank, int size, MPI_Comm communicator)
{
    int left = 2 * rank + 1;
    int right = 2 * rank + 2;

    if (rank ==  0) 
    {
        if (left < size) 
        {
            MPI_Send(data, count, datatype, left, 42, communicator);
        }
        if (right < size) 
        {
            MPI_Send(data, count, datatype, right, 42, communicator);
        }
    } 
    else 
    {   
        int parent = (rank%2 == 0) ? (rank-2)/2 : (rank-1)/2;
        MPI_Recv(data, count, datatype, parent, 42, communicator, MPI_STATUS_IGNORE);

        if (left < size) 
        {
            MPI_Send(data, count, datatype, left, 42, communicator);
        }
        if (right < size) 
        {
            MPI_Send(data, count, datatype, right, 42, communicator);
        }
    }
}


// Using the mean results in extremely unstable results
//
int compare(const void *a, const void *b)
{
    const double *da = (const double *)a;
    const double *db = (const double *)b;

    if (*da < *db) return -1;
    if (*da > *db) return 1;
    return 0;
}

// Using the median instead of the mean
//
long double median(double* times, int total)
{
    double temp;
    int med = (total%2 == 0) ? total/2 : (total+1)/2;
    qsort(times, total, sizeof(double), compare);
    temp = times[med];

    return temp;
}




int main(int argc, char* argv[])
{   
    // warmup iterations
    //
    int warmup = atoi(argv[1]);

    // total iterations
    //
    int total = atoi(argv[2]);

    // data size
    //
    int data_size = atoi(argv[3]);

    // aglorithm 
    //
    // 1 - flat tree
    // 2 - chain tree
    // 5 - binary tree
    //
    int algo = atoi(argv[4]);
    if(algo != 1 && algo != 2 && algo != 5)
    {
        printf("Invalid algorithm\n");
        return 1;
    }

    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Each process allocates the buffer, only the root fills it
    //
    int* buffer = (int*) malloc(sizeof(int) * data_size);
    if(rank == 0)
    {
        for(int i=0; i<data_size; i++) 
        {
            buffer[i] = i;
        }
    }


    double* times = (double*) malloc(sizeof(double) * total);
    double* times_default = (double*) malloc(sizeof(double) * total);
    if(rank != 0)
    {
        free(times);
        free(times_default);
    }

    switch(algo) 
    {
        case 1: // flat tree

            for(int i=0; i<warmup; i++) 
            {
                broadcast_flat_tree(buffer, data_size, MPI_INT, rank, size, MPI_COMM_WORLD);
            }

            for (int i=0; i<total; i++) 
            {   
                MPI_Barrier(MPI_COMM_WORLD);
                double start = MPI_Wtime();
                broadcast_flat_tree(buffer, data_size, MPI_INT, rank, size, MPI_COMM_WORLD);
                MPI_Barrier(MPI_COMM_WORLD);
                double end = MPI_Wtime();

                // double max_end;
                // MPI_Reduce(&end, &max_end, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

                if(rank == 0) 
                {   
                    double elapsed = end - start;
                    times[i] = elapsed;
                }
            } 

            // Default algorithm
            //
            for (int i = 0; i < total; i++)
            {
                MPI_Barrier(MPI_COMM_WORLD);
                double start = MPI_Wtime();
                MPI_Bcast(buffer, data_size, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Barrier(MPI_COMM_WORLD);
                double end = MPI_Wtime();

                if (rank == 0)
                {
                    double elapsed = end - start;
                    times_default[i] = elapsed;
                }
            }

            break;



        case 2: // chain tree

            for(int i=0; i<warmup; i++) 
            {
                broadcast_flat_tree(buffer, data_size, MPI_INT, rank, size, MPI_COMM_WORLD);
            }

            for (int i=0; i<total; i++) 
            {   
                MPI_Barrier(MPI_COMM_WORLD);
                double start = MPI_Wtime();
                broadcast_chain_tree(buffer, data_size, MPI_INT, rank, size, MPI_COMM_WORLD);
                MPI_Barrier(MPI_COMM_WORLD);
                double end = MPI_Wtime();

                // double max_end;
                // MPI_Reduce(&end, &max_end, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

                if(rank == 0) 
                {   
                    double elapsed = end - start;
                    times[i] = elapsed;
                }
            }    

            // Default algorithm
            //
            for (int i = 0; i < total; i++)
            {
                MPI_Barrier(MPI_COMM_WORLD);
                double start = MPI_Wtime();
                MPI_Bcast(buffer, data_size, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Barrier(MPI_COMM_WORLD);
                double end = MPI_Wtime();

                if (rank == 0)
                {
                    double elapsed = end - start;
                    times_default[i] = elapsed;
                }
            } 

            break;



        case 5: // binary tree

            for(int i=0; i<warmup; i++) 
            {
                broadcast_flat_tree(buffer, data_size, MPI_INT, rank, size, MPI_COMM_WORLD);
            }

            for (int i=0; i<total; i++) 
            {   
                MPI_Barrier(MPI_COMM_WORLD);
                double start = MPI_Wtime();
                broadcast_binary_tree(buffer, data_size, MPI_INT, rank, size, MPI_COMM_WORLD);
                MPI_Barrier(MPI_COMM_WORLD);
                double end = MPI_Wtime();

                // double max_end;
                // MPI_Reduce(&end, &max_end, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

                if(rank == 0) 
                {   
                    double elapsed = end - start;
                    times[i] = elapsed;
                }
            }

            // Default algorithm
            //
            for (int i = 0; i < total; i++)
            {
                MPI_Barrier(MPI_COMM_WORLD);
                double start = MPI_Wtime();
                MPI_Bcast(buffer, data_size, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Barrier(MPI_COMM_WORLD);
                double end = MPI_Wtime();

                if (rank == 0)
                {
                    double elapsed = end - start;
                    times_default[i] = elapsed;
                }
            }

            break;
    }

    // broadcast_flat_tree(buffer, data_size, MPI_INT, rank, size, MPI_COMM_WORLD);
    // broadcast_chain_tree(buffer, data_size, MPI_INT, rank, size, MPI_COMM_WORLD);
    // broadcast_binary_tree(buffer, data_size, MPI_INT, rank, size, MPI_COMM_WORLD);

    if (rank == 0) 
    {   
        double mean_time = median(times, total);
        double mean_time_default = median(times_default, total);

        printf("Algorithm, MPI_Processes, Data_Size, Latency, Latency_default\n");
        printf("%d,%d,%d,%.10f,%.10f\n", algo, size, data_size, mean_time, mean_time_default);

        free(times);
        free(times_default);
    }

    free(buffer);
    MPI_Finalize();

    return 0;
}