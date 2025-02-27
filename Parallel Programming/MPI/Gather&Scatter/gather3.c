#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int me, nproc, i;
    double sum[1], gathered[4];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);

	if (me == 0) {
        printf("Element of Array\n");
        printf("Thread  0      1      2      3\n");
	}
    for (i = 0; i < 10; i++) {
        sum[0] = i + (me * 0.1);

    MPI_Gather(&sum, 1, MPI_DOUBLE, &gathered, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        if(me==0){
            printf("%d     ", i);
            for (int j = 0; j < nproc; j++) {
                printf("%.1f   ", gathered[j]);
            }
            printf("\n");	
        }
    }

    MPI_Finalize();
    return 0;
}
