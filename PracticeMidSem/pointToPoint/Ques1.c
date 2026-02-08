#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <limits.h>
int calulateMax(int* array, int size){
    int max = INT_MIN;

    for(int i = 0; i<size; i++){
        if(array[i] > max) max = array[i];
    }

    return max;

}
int main(int argc, char** argv){
    int N, rank, M;
    int* send_array;
    int* recv_array;
    MPI_Status status;

    int root = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &N);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Part - 1 is to get the data from the user and send the value of M,
    if(rank == root){
        printf("Enter the values of M: \n");
        scanf("%d", &M);

        send_array = (int*)malloc(N*M*(sizeof(int)));

        printf("N*M values: \n");
        for(int i = 0; i < N*M; i++) scanf("%d", &send_array[i]);

        for(int i = 1; i<N; i++) MPI_Send(&M, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
    //reason for sending M first - memory allocation for the the receiving array

    if(rank != root) MPI_Recv(&M, 1, MPI_INT, root, 0, MPI_COMM_WORLD, &status);

    recv_array = (int*)malloc(M*sizeof(int));

    //Part - 2 is to send the chunks of data to all the processes
    if(rank == root){
        for(int i = 0; i<M; i++) recv_array[i] = send_array[i]; //store the first chunk in the local
        for(int i = 1; i<N; i++) MPI_Send(send_array + i*M, M, MPI_INT, i, 1, MPI_COMM_WORLD);
    }

    //Part - 3 is to receive the array, calculate the max value from the receive arrary and send the maximum
    if(rank != root){
        MPI_Recv(recv_array, M, MPI_INT, root, 1, MPI_COMM_WORLD, &status);
        int max_recv_value = calulateMax(recv_array, M);
        MPI_Send(&max_recv_value, 1, MPI_INT, root, 2, MPI_COMM_WORLD);
    }

    //Part - 4 is to receive all the local maximum and evaluate the global max

    if(rank == root){
        int local_max;
        int global_max = calulateMax(recv_array, M);
        printf("\nThe max from the root process: %d", global_max);

        for(int i = 1; i < N; i++){
            MPI_Recv(&local_max, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
            printf("\nMax from the process %d : %d", i, local_max);
            if(local_max > global_max) global_max = local_max;
        }

        printf("\nThe global max: %d\n", global_max);
    }

    //Part - 5 Clean up the memory after the role of each process is done
    if(rank == root) free(send_array);
    free(recv_array);

    MPI_Finalize();
    return 0;

}

//sucessfully self written code - first time for MPI

