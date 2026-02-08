***Questions***

**Point to Point Communication**

**Question-1**


Question

Write an MPI program using N processes to perform the following task:

The root process (rank 0) reads an integer M and then reads M × N integers into a 1D array.

The root process sends exactly M elements to each process using point-to-point communication.

Process 0 also keeps its own M elements.

Each process:

Computes the maximum of the M elements it received.

All non-root processes send their local maximum back to the root using point-to-point communication.

The root process:

Prints the maximum computed by each process.

Prints the global maximum.

**Question - 2**

Question

Write an MPI program using N processes to perform the following task:

The root process (rank 0) reads an integer M.
The root process then reads M × (N − 1) integers into a 1D array.
The root process sends exactly M integers to each non-root process using MPI_Ssend.

Each non-root process:

Receives its M integers
Computes the sum of the received elements
Sends the sum back to the root using MPI_Ssend

The root process:

Receives the sum from each non-root process
Prints the sum computed by each process
Prints the total sum of all values

Constraints

Only MPI_Ssend and MPI_Recv are allowed
Root process must not compute any local sum
No collective communication routines allowed

**Question - 3**

Question

Write an MPI program using N processes to perform the following task:
The root process (rank 0) reads an integer M.
The root process reads M × (N − 1) integers into a 1D array.
The root process attaches a user-defined buffer using MPI_Buffer_attach.

The root process sends exactly M integers to each non-root process using MPI_Bsend.

Each non-root process:
Receives its M integers
Computes the maximum of the received elements
Sends the maximum back to the root using MPI_Send

The root process:
Receives the maximum from each process
Prints the maximum from each process
Prints the global maximum

The root process detaches the buffer before terminating.

Constraints

MPI_Bsend must be used for data distribution
MPI_Buffer_attach and MPI_Buffer_detach are mandatory
No collective routines allowed