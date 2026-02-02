***Questions***

**Point to Point Communication**

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