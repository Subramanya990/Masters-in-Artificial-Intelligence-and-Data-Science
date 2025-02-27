#include <stdio.h>
#include <math.h>
#include <mpi.h>

#define MAX_RANGES 100

int exponent = 2;

double f(double x) {
    return pow(x, exponent);
}

int main(int argc, char *argv[]) {
    int npoints, n_ranges, i, j, me, nproc;
    double x, local_sum[10]={0}, global_sum[10];
    double a[10], b[10];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);

    if (me == 0) {
        printf("Input number of points for calculation of integral: \n");
        scanf("%i", &npoints);

        printf("Input number of ranges for integration: \n");
        scanf("%i", &n_ranges);

        printf("Input lower and higher bounds for each range of integration:\n");
        for (i = 0; i < n_ranges; i++) {
            printf("Range %d:\n", i + 1);
            scanf("%lf %lf", &a[i], &b[i]);
        }
    }

    MPI_Bcast(&npoints, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n_ranges, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&a, n_ranges, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b, n_ranges, MPI_DOUBLE, 0, MPI_COMM_WORLD);


    for (j = me; j < n_ranges; j += nproc) {
        //local_sum[j] = 0.0; // Reset local sum for the assigned range

        for (i = 1; i <= npoints - 1; i++) {
            x = a[j] + i * (b[j] - a[j]) / npoints;
            local_sum[j] += f(x);
        }
    }

    // Reduce results for all ranges
    MPI_Reduce(local_sum, global_sum, n_ranges, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print results on rank 0
    if (me == 0) {
        for (j = 0; j < n_ranges; j++) {
			global_sum[j] += (f(a[j]) + f(b[j])) / 2;
			global_sum[j] *= (b[j] - a[j]) / npoints;
            printf("Range %d: Numerical Integral = %lf, Analytical Integral = %lf\n",j + 1,global_sum[j],
                   (pow(b[j], exponent + 1) - pow(a[j], exponent + 1)) / (exponent + 1));
        }
    }

    MPI_Finalize();
    return 0;
}
