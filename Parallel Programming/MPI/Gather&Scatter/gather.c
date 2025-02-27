#include<stdio.h>
#include<mpi.h>

int main(int argc, char*argv[])
{
 	int me, nproc, i ;
	double sum[10], gather[10*nproc];

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &me);
	
	for(i=0;i<10;i++){
		sum[i] = 1+ i + (me*0.1);
	}

	MPI_Gather(&sum,10,MPI_DOUBLE,&gather,10,MPI_DOUBLE,0,MPI_COMM_WORLD);

	if(me==0){
	printf("Thread    0        1        2        3\n");
	for(i=0;i<10;i++){
	printf("%d    ",i);
		for(int j=0;j<nproc;j++){
		printf("%4.1f    ,Thread:   %i  ",gather[i+j*10],me);
			}
		printf("\n");
		}
	}
	MPI_Finalize();
	return 0;
}	
