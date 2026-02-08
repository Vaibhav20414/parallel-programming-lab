#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int computeSum(int* array, int size){
    int sum = 0;
    for(int i = 0; i<size; i++) sum += array[i];

    return sum;
}

int main(int argc, char** argv){
    int N, rank;
    int M;
    int* send_array;
    int* recv_array;
    int root = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &N);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    recv_array = (int*)malloc(N*sizeof(int));

    printf("Enter the value of M for process %d \n", rank);
    scanf("%d", &M);

    send_array = (int*)malloc(M*sizeof(int));

    printf("Enter the elements of array of process: \n");
    for(int i = 0; i<M; i++){
        scanf("%d", &send_array[i]);
    }

    int local_sum = computeSum(send_array, M);
    MPI_Gather(&local_sum, 1, MPI_INT, recv_array, 1, MPI_INT, root, MPI_COMM_WORLD);

    if(rank == root){
        int total_sum = 0;
        for(int i = 0; i<N; i++){
            printf("\nThe sum receive from process %d : %d\n", i, recv_array[i]);
            total_sum += recv_array[i];
        }
        printf("Total sum : %d \n", total_sum);

        free(recv_array);
    }

    free(send_array);

    MPI_Finalize();

    return 0;
}