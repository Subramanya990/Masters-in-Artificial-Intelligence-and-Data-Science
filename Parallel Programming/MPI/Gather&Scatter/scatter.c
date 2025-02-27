#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
	int me, nproc, i;
	double sum[40], scatter[10];
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &me);
	
	if(me==0){
		for(i=0;i<=40;i++){
			sum[i] = (i+1)*0.1;
			printf("%d \n", i);
		}
	}
	
	MPI_Scatter(sum,10,MPI_DOUBLE,scatter,10,MPI_DOUBLE,0,MPI_COMM_WORLD);
	
	for(i =0; i< nproc; i++){
		if(me==i){
			for (int j=0; j<10; j++){
					printf("Thread %d has value %f \n", me, scatter[j]);
			}
		}
		MPI_Barrier(MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
	return 0;
}