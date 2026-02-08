#include <stdio.h>
#include <mpi.h>

int factorial(int number){
    int factorial = 1;

    for(int i = 2; i<=number; i++){
        factorial *= i;
    }

    return factorial;
}

int main(int argc, char** argv){

    int rank, size, N, first_send_array[10], i, recv_val;
    int root = 0;
    int global_result;

    MPI_Init(&argc, &argv); //The order of intialization matters for the MPI commands and function, 
    //variable declartion order doesn't matter


    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == root){ //this is the root process, by convention
        N = size;
        printf("Enter %d values:\n", N);
        for(i = 0; i<N; i++) scanf("%d", &first_send_array[i]);
    }
    MPI_Scatter(first_send_array, 1,MPI_INT, &recv_val, 1, MPI_INT, 0, MPI_COMM_WORLD);
    //first send array is the one getting scatter among all the processes
    //1 -> count of values which are going to be sent to each of the processes
    //&recv_val -> recv buffer for each process, 
//     MPI programs use multiple processes, not shared-memory threads.
// Each process has:
// Its own address space
// Its own stack
// Its own heap
// Variables are not shared unless explicitly placed in shared memory (which MPI does not do by default)

// So this line:
// int recv_value;
// creates:
// One recv_value in process 0
// One recv_value in process 1
// One recv_value in process 2
// …
// They just happen to have the same name.
    int fact = factorial(recv_val);
    MPI_Reduce(&fact, &global_result, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

    if(rank == root){
        printf("Sum of the factorial = %d", global_result);
    }

    MPI_Finalize();
    if(rank == 1) printf("\nName: Vaibhav, Reg No.: 230962202, Roll No. : 43 \n");
    return 0;

}