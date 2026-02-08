#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <ctype.h>

int is_vowel(char c) {
    c = tolower(c);
    return (c=='a'||c=='e'||c=='i'||c=='o'||c=='u');
}

int main(int argc, char** argv) {
    int rank, size, root = 0;
    int len, chunk;
    char *str = NULL, *recv = NULL;
    int local_count = 0, total_count;
    int *counts = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == root) {
        str = (char*)malloc(1000);
        printf("Enter string:\n");
        scanf("%s", str);
        len = strlen(str);
    }

    MPI_Bcast(&len, 1, MPI_INT, root, MPI_COMM_WORLD);

    chunk = len / size;
    recv = (char*)malloc(chunk);

    MPI_Scatter(str, chunk, MPI_CHAR, recv, chunk, MPI_CHAR, root, MPI_COMM_WORLD);

    for (int i = 0; i < chunk; i++) {
        if (!is_vowel(recv[i])) local_count++;
    }

    if (rank == root)
        counts = (int*)malloc(size * sizeof(int));

    MPI_Gather(&local_count, 1, MPI_INT, counts, 1, MPI_INT, root, MPI_COMM_WORLD);

    MPI_Reduce(&local_count, &total_count, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

    if (rank == root) {
        for (int i = 0; i < size; i++)
            printf("Process %d non-vowels = %d\n", i, counts[i]);
        printf("Total non-vowels = %d\n", total_count);
    }

    MPI_Finalize();
    return 0;
}
