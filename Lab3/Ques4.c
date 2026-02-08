#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, root = 0;
    int len, chunk;
    char *s1 = NULL, *s2 = NULL;
    char *r1 = NULL, *r2 = NULL;
    char *local = NULL;
    char *result = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == root) {
        s1 = (char*)malloc(1000);
        s2 = (char*)malloc(1000);
        printf("Enter string S1:\n");
        scanf("%s", s1);
        printf("Enter string S2:\n");
        scanf("%s", s2);
        len = strlen(s1);
    }

    MPI_Bcast(&len, 1, MPI_INT, root, MPI_COMM_WORLD);

    chunk = len / size;
    r1 = (char*)malloc(chunk);
    r2 = (char*)malloc(chunk);
    local = (char*)malloc(2 * chunk);

    MPI_Scatter(s1, chunk, MPI_CHAR, r1, chunk, MPI_CHAR, root, MPI_COMM_WORLD);
    MPI_Scatter(s2, chunk, MPI_CHAR, r2, chunk, MPI_CHAR, root, MPI_COMM_WORLD);

    for (int i = 0; i < chunk; i++) {
        local[2*i]     = r1[i];
        local[2*i + 1] = r2[i];
    }

    if (rank == root)
        result = (char*)malloc(2 * len + 1);

    MPI_Gather(local, 2*chunk, MPI_CHAR,
               result, 2*chunk, MPI_CHAR,
               root, MPI_COMM_WORLD);

    if (rank == root) {
        result[2*len] = '\0';
        printf("Resultant string: %s\n", result);
    }

    MPI_Finalize();
    return 0;
}
