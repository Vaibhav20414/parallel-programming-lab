#include <stdio.h>
#include <mpi.h>
#include <limits.h>
#include <stdlib.h>

int calculateMax(int* array, int size){
    int max = INT_MIN;

    for(int i = 0; i<size; i++){
        if(array[i] > max) max = array[i];
    }

    return max;

}

int main(int argc, char** argv){
    int N, M;
    int rank;
    int* send_arr = NULL;
    int* recv_arr = NULL;
    void* buffer;
    MPI_Status status;
    int root = 0;
    int buffer_size;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &N);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Step 1 - Get the input from root and send M to all the processes
    if(rank == root){
        printf("Enter the value of M: ");
        scanf("%d", &M);

        send_arr = (int*)malloc(M*(N-1)*sizeof(int));

        printf("Enter M*(N-1) values: \n");
        for(int i = 0; i< M*(N-1); i++){
            scanf("%d", &send_arr[i]);
        }

        //Ssend is used to ensure syncronization

        for(int i = 1; i<N; i++){
            MPI_Ssend(&M, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }

    //Step 2 - Receive the value of M and allocate the memory 
    if(rank != root){
        MPI_Recv(&M, 1, MPI_INT, root, 0, MPI_COMM_WORLD, &status);
        recv_arr = (int*)malloc(M*sizeof(int));
    }

    //Step 3 - Use the Buffer and Bsend for data distribution using a buffer.
    if(rank == root){
        //this is not the correct way to initialize the buffer.
        // buffer_size = sizeof(M*(N-1)) + MPI_BSEND_OVERHEAD;
        buffer_size = (N-1) * (M * sizeof(int) + MPI_BSEND_OVERHEAD);
        buffer = (int*)malloc(buffer_size);

        MPI_Buffer_attach(buffer, buffer_size);

        for(int i = 1; i<N; i++){
            MPI_Bsend(send_arr + (i-1)*M, M, MPI_INT, i, 1, MPI_COMM_WORLD);
        }

    }

    //Step 4 - Receive the data in non-root processes, compute the maxima and send to root.
    if(rank != root){
        MPI_Recv(recv_arr, M, MPI_INT, root, 1, MPI_COMM_WORLD, &status);

        int max = calculateMax(recv_arr, M);

        //Ssend is used to ensure syncronization

        MPI_Ssend(&max, 1, MPI_INT, root, 2, MPI_COMM_WORLD);
    }

    //Step 5 - Print the local maxima for each process and compute the global maxima.
    if(rank == root){
        int local_max;
        int global_max = INT_MIN;

        for(int i = 1; i < N; i++){
            MPI_Recv(&local_max, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
            printf("\nMax from the process %d : %d", i, local_max);
            if(local_max > global_max) global_max = local_max;
        }

        printf("\nThe global max: %d\n", global_max);
    }

    //Step 6 - Clean up the allocated memory for all the processes.
    if(rank == root){
        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);
        free(send_arr);
    } else {
        free(recv_arr);
    }

    MPI_Finalize();
    return 0;
}