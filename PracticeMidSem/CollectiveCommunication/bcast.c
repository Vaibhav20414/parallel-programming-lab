#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int computeSum(int* array, int size){
    int sum = 0;
    for(int i = 0; i<size; i++) sum += array[i];

    return sum;
}

int main(int argc, char** argv){
    int size, rank;
    int root = 0;
    int M;
    int* bcast_array;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Part - 1 - Root Process reading.
    if(rank == root){

        //Step - 1 - Read the value of M.
        printf("Enter the value of M : \n");
        scanf("%d", &M);

        //Step - 2 - Allocate and read the bcast array.
        bcast_array = (int*)malloc(M*sizeof(int));
        printf("Enter the M values: \n");
        for(int i = 0; i<M; i++){
            scanf("%d", &bcast_array[i]);
        }
    }
    //Part - 2 - Broadcasting
    //Step - 1 - Broadcast M value and allocate the memory for non root processes
    MPI_Bcast(&M, 1, MPI_INT, root, MPI_COMM_WORLD);
    printf("\nValue of M for the process %d : %d \n", rank, M);

    if(rank != root) bcast_array = (int*)malloc(M*sizeof(int));

    //Step - 2 Broadcast the array.
    MPI_Bcast(bcast_array, M, MPI_INT, root, MPI_COMM_WORLD);

    //Part - 3 - Sum calculations and print result.
    int array_sum = computeSum(bcast_array, M);

    printf("\nCalcualted sum from process %d : %d\n", rank, array_sum);

    //Part - 4 - Free the memory.
    free(bcast_array);
    MPI_Finalize();

    return 0;
}