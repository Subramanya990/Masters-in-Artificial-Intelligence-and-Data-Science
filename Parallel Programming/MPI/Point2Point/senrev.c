// sump.c
// sums first N integers
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int me,nproc,i,n,sum=0,total;
	MPI_Status status;
	
	MPI_Init(&argc,&argv); // initialise MPI
	MPI_Comm_size(MPI_COMM_WORLD,&nproc); // return total number of processors
	MPI_Comm_rank(MPI_COMM_WORLD,&me); // return number of this processor, me=0..nproc-1
	
	
	if(me==0){
		printf("Program for summing first N integer numbers\n ");
		printf("Enter N: ");scanf("%i", &n);
		
		for(int dest=1;dest<=nproc-1;dest++){
			MPI_Send(&n,1,MPI_INT,dest,101,MPI_COMM_WORLD);	
		}
	}
	else{
		MPI_Recv(&n,1,MPI_INT,0,101,MPI_COMM_WORLD,&status);
	}
	
	int low = (me*n/nproc)+1;
	int high = (me+1)*n/nproc;
	
	for(i=low;i<=high;i=i++){ 
		sum=sum+i;
	}
	
	if(me!=0){
			MPI_Send(&sum,1,MPI_INT,0,102,MPI_COMM_WORLD);
	}
	else{
		total = sum;
		for(int source = 1;source<=nproc-1;source++){
			MPI_Recv(&sum,1,MPI_INT,source,102,MPI_COMM_WORLD,&status);
			total += sum;
		}
	}
	
	
	if(me==0){
		printf("Sum of first %i integers equals   : %i\n",n,total);
		printf("Sum of first %i integers should be: %i\n",n,(n*(n+1))/2);

	}

	
	MPI_Finalize(); // finalize MPI peacefully (the system would kill the processes otherwise)

	return 0;
}

