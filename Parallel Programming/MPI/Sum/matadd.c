#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
	int r, c, a[100][100], b[100][100], sum[100][100]={0},res[100][100]={0}, i, j,me,nproc;
  
	MPI_Init(&argc,&argv); // initialise MPI
	MPI_Comm_size(MPI_COMM_WORLD,&nproc); // return total number of processors
	MPI_Comm_rank(MPI_COMM_WORLD,&me); // return number of this processor, me=0..nproc-1
	if(me==0){
		
		printf("Enter the number of rows (between 1 and 100): ");
		scanf("%d", &r);
		printf("Enter the number of columns (between 1 and 100): ");
		scanf("%d", &c);

		printf("\nEnter elements of 1st matrix:\n");
		for (i = 0; i < r; ++i)
			for (j = 0; j < c; ++j) {
				printf("Enter element a%d%d: ", i + 1, j + 1);
				scanf("%d", &a[i][j]);
			}

		printf("Enter elements of 2nd matrix:\n");
		for (i = 0; i < r; ++i)
			for (j = 0; j < c; ++j) {
				printf("Enter element b%d%d: ", i + 1, j + 1);
				scanf("%d", &b[i][j]);
			}
	}
	
	MPI_Bcast(&r,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&c,1,MPI_INT,0,MPI_COMM_WORLD);
	
	MPI_Bcast(&a,100*100,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&b,100*100,MPI_INT,0,MPI_COMM_WORLD);
	
	
  // adding two matrices
	int rows = r/nproc;
	int start = me * rows;
	int end = (me == nproc-1) ? r: start + rows;
	
	for (i = start; i < end; ++i)
		for (j = 0; j < c; ++j) {
			sum[i][j] = a[i][j] + b[i][j];
		}

  // printing the result
	MPI_Reduce(&sum,&res,100*100,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	
	if(me==0){
		for (i = 0; i < r; ++i){
			for (j = 0; j < c; ++j) {
				printf("%d  ", res[i][j]);
				if (j == c - 1) {
					printf("\n\n");
				}
			}
		}
	}
	
	MPI_Finalize();
  return 0;
}
