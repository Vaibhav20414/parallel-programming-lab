#include <stdio.h>
#include <mpi.h>
#include <limits.h>

int computeMax(int* array , int size){
    int max = INT_MIN;

    for(int i = 0; i<size; i++){
        if(array[i] > max) max = array[i];
    }

    return max;
}

int main(int argc, char** argv){
    int size, rank;
    int matrix[3][3];
    int* recv;
    int global_max;
    int root = 0;
    int err, err_len;
    char err_mess[MPI_MAX_ERROR_STRING];

    MPI_Init(&argc, %argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == root){
        printf("Enter the elements of matrix: ");
        for(int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                scanf("%d", &matrix[i][j]);
            }
        }
    }

    recv = (int*)malloc(3*sizeof(int));

    MPI_Scatter(matrix, 3, MPI_INT, recv, 3, MPI_INT, root, MPI_COMM_WORLD);

    int max = computeMax(recv, 3);

    MPI_Reduce(&max, &global_max, 3, MPI_INT, MPI_MAX, root, MPI_COMM_WORLD);

    if(rank == root){
        printf("The global maxima is %d", global_max);
    }

    free(recv);

    MPI_Finalize();

    return 0;
}