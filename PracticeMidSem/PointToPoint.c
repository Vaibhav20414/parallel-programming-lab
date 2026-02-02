#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int computeMax(int* arr, int n){
    int max_element = -__INT_MAX__;
    for(int i = 0; i<n; i++){
        if(arr[i] > max_element) max_element = arr[i];
    }

    return max_element;
}


int main(int argc, char** argv){

    int* recv_arry;
    int N, rank;
    int root = 0;
    int M;


    MPI_Init(&argc, &argv);
    MPI_Status status;
    MPI_Comm_size(MPI_COMM_WORLD, &N);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == root){
        printf("\nEnter the number of element to put in each array: \n");
        scanf("%d", &M);
        for(int i = 1; i<N; i++){
            MPI_Send(&M, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
        }
        int* send_array = (int*)malloc(N*M*(sizeof(int)));
        for(int i = 0; i< N*M ; i++){
            scanf("%d", send_array[i]);
        }
        int j = 0;
        for(int i = 0; i<N*M; i = i + M){
            MPI_Send(send_array+ i*M, M, MPI_INT, j, 1, MPI_COMM_WORLD);
            j++;
        }
    }
    if(rank != root)  MPI_Recv(&M, 1, MPI_INT, root, 2, MPI_COMM_WORLD, status);


    recv_arry = (int*)malloc(M*sizeof(int));

    MPI_Recv(recv_arry, M, MPI_INT, root, 1, MPI_COMM_WORLD, status);

    int max_element = computeMax(recv_arry, M);

    MPI_Send(&max_element, 1, MPI_INT, root, 3, MPI_COMM_WORLD);

    if(rank == root){
        int globalMaximum = 0;
        int max;

        for(int i = 0; i<N; i++){
            MPI_Recv(&max, 1, MPI_INT, i, 3, MPI_COMM_WORLD, status);
            printf("Max element from process %d : %d\n", i, max);
            if(max > globalMaximum) globalMaximum = max;
        }
        printf("Global maximum is : %d", globalMaximum);
    }
    MPI_Finialize();
    return 0;
}