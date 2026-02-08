#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int sumArray(int* array, int m){
    int sum = 0;
    for(int i = 0; i<m; i++) sum += array[i];

    return sum;
}

int main(int argc, char** argv){
    int N, M, rank;
    int* send_array = NULL;
    int* recv_array = NULL;
    int root = 0;
    MPI_Status status;

    MPI_Init(&argc,&argv);

    MPI_Comm_size(MPI_COMM_WORLD, &N);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == root){
        //Step 1 - Inputs from the root
        
        printf("Enter the value of M: ");
        scanf("%d", &M);

        send_array = (int*)malloc(M*(N-1)*sizeof(int));

        printf("Enter M*(N-1) values: \n");
        for(int i = 0; i< M*(N-1); i++){
            scanf("%d", &send_array[i]);
        }

        //Step 2 - Sending the M value and the array 

        for(int i = 1; i<N; i++){
            MPI_Ssend(&M, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

        //Two for loops because S send blocks the sending process

        for(int i = 1; i<N; i++){
            MPI_Ssend(send_array + (i-1)*M, M, MPI_INT, i, 1, MPI_COMM_WORLD);
        }
    }

    if(rank != root){
        //Step 3 - Receiving the value of M and elements


        //first receive the value of M from the root first for loop 
        //allocate memory for the receive array
        MPI_Recv(&M, 1, MPI_INT, root, 0, MPI_COMM_WORLD, &status);
        recv_array = (int*)malloc(M*sizeof(int));

        //receive the element
        MPI_Recv(recv_array, M, MPI_INT, root, 1, MPI_COMM_WORLD, &status);
        int sum = sumArray(recv_array, M);

        //each process will send the local sum 
        MPI_Ssend(&sum, 1, MPI_INT, root, 2, MPI_COMM_WORLD);
    }

    if(rank == root){

        //Step 4 - Printing the local sum and computing the global sum
        int local_sum;
        int total_global_sum = 0;

        for(int i = 1; i<N; i++){
            MPI_Recv(&local_sum, 1, MPI_INT, i, 2, MPI_COMM_WORLD, &status);
            printf("\nSum from the process %d: %d", i, local_sum);
            total_global_sum += local_sum;
        }

        printf("\nGlobal num : %d \n", total_global_sum);
    }

    //Step 5 - Clean up the memory
    if(rank == root){
        free(send_array);
    }else{
        free(recv_array);
    }

    MPI_Finalize();
    return 0;
}