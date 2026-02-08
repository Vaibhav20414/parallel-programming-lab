#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    int size, rank;
    int read_val;
    int prefix_result;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    read_val = rank + 5;

    MPI_Scan(&read_val, &prefix_result, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    printf("\nResultant value from the process %d : %d\n", rank, prefix_result);

    MPI_Finalize();

    return 0;
}