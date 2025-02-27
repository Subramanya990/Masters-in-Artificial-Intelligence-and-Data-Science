#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int c, d, k, m, n, p, q, tot;
    int fst[10][10], sec[10][10];
    int partial[10][10] = {0}, result[10][10] = {0};
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0) {
        printf("Enter the number of rows and columns for the first matrix:\n");
        scanf("%d %d", &m, &n);
        printf("Enter the elements of the first matrix:\n");
        for (c = 0; c < m; c++)
            for (d = 0; d < n; d++)
                scanf("%d", &fst[c][d]);

        printf("Enter the number of rows and columns for the second matrix:\n");
        scanf("%d %d", &p, &q);

        if (n != p) {
            printf("Matrix multiplication not possible.\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        printf("Enter the elements of the second matrix:\n");
        for (c = 0; c < p; c++)
            for (d = 0; d < q; d++)
                scanf("%d", &sec[c][d]);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&p, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&q, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(fst, 10 * 10, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(sec, 10 * 10, MPI_INT, 0, MPI_COMM_WORLD);

    int rows_per_proc = m / size;
    int start_row = rank * rows_per_proc;
    int end_row = (rank == size - 1) ? m : start_row + rows_per_proc;

    for (c = start_row; c < end_row; c++) {
        for (d = 0; d < q; d++) {
            tot = 0;
            for (k = 0; k < n; k++) {
                tot += fst[c][k] * sec[k][d];
            }
            partial[c][d] = tot;
        }
    }

    MPI_Reduce(partial, result, 10 * 10, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("The result of matrix multiplication is:\n");
        for (c = 0; c < m; c++) {
            for (d = 0; d < q; d++) {
                printf("%d\t", result[c][d]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();
    return 0;
}
