#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    int rank, size, value = 10;
    int err, err_class;
    char err_string[MPI_MAX_ERROR_STRING];
    int err_len;

    MPI_Init(&argc, &argv);
    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        err = MPI_Send(&value, 1, MPI_INT, size, 0, MPI_COMM_WORLD);

        if(err != MPI_SUCCESS){
            MPI_Error_class(err, &err_class);
            MPI_Error_string(err, err_string, &err_len);

            printf("MPI Error Class: %d\n", err_class);
            printf("MPI Error Message: %s\n", err_string);
        }
    }

    MPI_Finalize();
    return 0;
}
