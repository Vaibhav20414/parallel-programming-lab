#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <limits.h>

int calcMax(int* array, int M){
    int max = INT_MIN;
    for(int i = 0; i<M; i++){
        if(array[i] > max) max = array[i];
    }

    return max;
}
int main(int argc, char** argv){

    int N, rank;
    int root = 0;
    int M;
    int* send_arr = NULL;
    int* recv_arr = NULL;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &N);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == root){
        printf("Enter the value of M: \n");
        scanf("%d", &M);

        send_arr = (int*)malloc(M*N*(sizeof(int)));

        printf("Enter M*N values: \n");
        for(int i = 0; i<M*N; i++) scanf("%d", &send_arr[i]);
    }

    MPI_Bcast(&M, 1, MPI_INT, root, MPI_COMM_WORLD);
    recv_arr = (int*)malloc(M*sizeof(int));

    MPI_Scatter(send_arr, M, MPI_INT, recv_arr, M, MPI_INT, root, MPI_COMM_WORLD);

    int local_max = calcMax(recv_arr, M);
    
    printf("Local max for the process %d : %d\n", rank, local_max);

    if(rank == root) free(send_arr);

    free(recv_arr);

    MPI_Finalize();

    return 0;
}