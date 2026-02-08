//using an error handler so that the code does not throw default error
#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    int rank, size;
    int val = 10;
    int err;

    MPI_Init(&argc, &argv);

    MPI_Comm_set_errhandler(MPI_COMM_WORLD, MPI_ERRORS_RETURN);


    // MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
    // This is the old way to do it. API name is outdated now.
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        err = MPI_Send(&val, 1, MPI_INT, size, 0, MPI_COMM_WORLD);
        
        if(err != MPI_SUCCESS){
            printf("Rank 0 has detected an error");
        }
        
    }

    MPI_Finalize();

    return 0;


}