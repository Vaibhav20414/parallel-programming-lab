#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv){
    int rank, size;
    int val = 10;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        MPI_Send(&val, 1, MPI_INT, size, 0, MPI_COMM_WORLD);
        printf("this text will not be printed");
    }

    MPI_Finalize();

    return 0;


}

//OUTPUT
// [Vaibhav:18242] *** An error occurred in MPI_Send
// [Vaibhav:18242] *** reported by process [2438725633,0]
// [Vaibhav:18242] *** on communicator MPI_COMM_WORLD
// [Vaibhav:18242] *** MPI_ERR_RANK: invalid rank
// [Vaibhav:18242] *** MPI_ERRORS_ARE_FATAL (processes in this communicator will now abort,
// [Vaibhav:18242] ***    and potentially your MPI job)

//HERE ALL THE PROCESSES ARE ABORTED