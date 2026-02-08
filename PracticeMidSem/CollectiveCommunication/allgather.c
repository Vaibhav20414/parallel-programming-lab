//to practice the non-root centric communication 

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
    int size, rank;
    int* read_int;
    int send_value;

    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    read_int = (int*)malloc(size*(sizeof(int)));

    //Instead of taking input from each one of process, implementing custom logic
    //for the send_value;

    send_value = rank + 1;

    //now using all gather to get all the values in the read_int array

    MPI_Allgather(&send_value, 1, MPI_INT, read_int, 1, MPI_INT, MPI_COMM_WORLD);
    //NOTE- Be especially carefull of the recv_count in this function.




    //Printing the receive array from each process
    printf("\nReceive array from the process %d\n", rank);
    for(int i = 0; i < size; i++){
        printf("[%d] \t", read_int[i]);
    }

    printf("\n");

    free(read_int);
    MPI_Finalize();

    return 0;
}