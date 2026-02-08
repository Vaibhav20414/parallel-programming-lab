#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    int size, rank;
    int result;
    int prefix_sum;
    int local_value;

    int err, err_len;
    char err_string[MPI_MAX_ERROR_STRING];

    MPI_Init(&argc, &argv);

    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    local_value = rank + 1;

    err = MPI_Scan(&local_value, &prefix_sum, 1, MPI_SUM, MPI_COMM_WORLD);

    if(err != MP)



    
}