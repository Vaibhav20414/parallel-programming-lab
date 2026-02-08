#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int N, rank;
    int* send_array = NULL;
    int* recv_array = NULL;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &N);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    send_array = (int*)malloc(N*sizeof(int));
    recv_array = (int*)malloc(N*sizeof(int));

    //custom logical message for all to all communication
    for(int i = 0; i<N ;i ++){
        send_array[i] = i + rank;
    }

    MPI_Alltoall(send_array, 1, MPI_INT, recv_array, 1, MPI_INT, MPI_COMM_WORLD);


    printf("\nReceived array from the process %d\n", rank);
    for(int i = 0; i < N; i++){
        printf("[%d] \t", recv_array[i]);
    }
    printf("\n");

    free(recv_array);
    free(send_array);

    MPI_Finalize();

    return 0;
}