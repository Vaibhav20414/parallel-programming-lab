**Questions**


1️⃣ MPI_Bcast — Broadcast - Completed - 9/10
Question
Write an MPI program using N processes to perform the following task:
The root process reads an integer M.
The root process reads M integers into an array.
The root process broadcasts M and the array to all processes using MPI_Bcast.
Each process computes the sum of the array.
Each process prints its rank and the computed sum.

Key intent
All processes must receive identical data
No point-to-point allowed

2️⃣ MPI_Scatter — Scatter - Complete - 9/10
Question
Write an MPI program using N processes to perform the following task:
The root process reads an integer M.
The root process reads M × N integers into a 1D array.
The root process distributes exactly M integers to each process using MPI_Scatter.
Each process computes the maximum of the received elements.
Each process prints its rank and local maximum.

Key intent
One-to-many equal data distribution
Root does not manually send chunks

3️⃣ MPI_Gather — Gather - Complete
🔹 If this were graded STRICTLY on MPI concepts
Score: 7.5 / 10
In MPI input is always taken from the root process.
If this fact is not give it's assumed.

🔹 If this were a THEORY / DESIGN question
Score: 9 / 10
Question


Write an MPI program using N processes to perform the following task:
Each process reads M integers.
Each process computes the sum of its M integers.
All local sums are gathered at the root process using MPI_Gather.
The root process prints the sum from each process and computes the total sum.

Key intent
Many-to-one collection
Root receives structured results

4️⃣ MPI_Reduce — Reduce - Complete

Score: 10 / 10

Question
Write an MPI program using N processes to perform the following task:
Each process reads M integers.
Each process computes the local maximum.
Use MPI_Reduce to compute the global maximum at the root process.
The root process prints the global maximum.

Key intent
Global aggregation
No manual receive loops

5️⃣ MPI_Allgather — Allgather - Compeleted

Score: 9.5 / 10

Question
Write an MPI program using N processes to perform the following task:
Each process reads one integer.
All processes exchange their integers using MPI_Allgather.
Each process computes the maximum of all N integers.
Each process prints its rank and the computed maximum.

Key intent

Everyone needs everyone’s data
No root-centric communication

6️⃣ MPI_Alltoall — All-to-All - Completed (small logical error)

Score: 10 / 10


Question
Write an MPI program using N processes to perform the following task:
Each process creates an array of N integers.
The value at index i of each process’s array is intended for process i.
Use MPI_Alltoall so that each process receives one integer from every other process.
Each process prints the received array.

Key intent

Complete pairwise data exchange
Communication pattern cannot be simplified to scatter/gather

7️⃣ MPI_Scan — Prefix Reduction (Scan) - Completed

Score: 10 / 10

Question

Write an MPI program using N processes to perform the following task:
Each process reads one integer.
Use MPI_Scan to compute the prefix sum of the integers.
Each process prints its rank and the prefix sum up to that rank.
Key intent

Partial reduction
Order-dependent collective

🧠 How to practice these (important advice)
Do them in this order: 
Bcast → Scatter → Gather → Reduce → Allgather → Alltoall → Scan