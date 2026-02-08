//Lab - 2 - Question 3

#include <stdio.h>
#include <stdlib.h> 
#include <mpi.h>

int square(int value){
    return value*value;
}

int cube(int value){
    return value*value*value;
}

int main(int argc, char** argv){
    int N, rank;
    int* send_array;
    void* buffer;
    int buffer_size;
    int recv_value;
    int root = 0;



    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &N);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Status status;

    if(rank == root){
        send_array = (int*)malloc(N*sizeof(int));

        printf("Enter the send elements: ");
        for(int i = 0; i < N; i++){
            scanf("%d", &send_array[i]);
        }
        buffer_size = N * (sizeof(int) + MPI_BUFFER_OVERHEAD);

        buffer = (int*)malloc(buffer_size);

        MPI_Buffer_attach(buffer, buffer_size);

        for(int i = 1; i<N; i++){
            MPI_Bsend(send_array + i, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        
    }

    if(rank % 2 == 0 && rank != 0){
        MPI_Recv(&recv_value, 1, MPI_INT, root, 0, MPI_COMM_WORLD, &status);
        printf("\n Received Value for process %d = %d", rank, square(recv_value));
    }

    if(rank % 2 != 0){
         MPI_Recv(&recv_value, 1, MPI_INT, root, 0, MPI_COMM_WORLD, &status);
        printf("\n Received Value for process %d = %d", rank, cube(recv_value));
    }

    if(rank == 0){
        MPI_Buffer_detach(&buffer, &buffer_size);
        free(buffer);
        free(send_array);
    }

    MPI_Finalize();
    return 0;

}