// sump.c
// sums first N integers
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int me,nproc,i,n,sum=0,total;
	
	printf("me =%i Print A, nproc=%i, n=%i, sum=%i\n",me,nproc,n,sum);
	
	MPI_Init(&argc,&argv); // initialise MPI
	MPI_Comm_size(MPI_COMM_WORLD,&nproc); // return total number of processors
	MPI_Comm_rank(MPI_COMM_WORLD,&me); // return number of this processor, me=0..nproc-1
	
	printf("me =%i Print B, nproc=%i, n=%i, sum=%i\n",me,nproc,n,sum);
	
	if(me==0){
		printf("Program for summing first N integer numbers\n ");
		printf("Enter N: ");scanf("%i", &n);
	}

	printf("me =%i Print C, nproc=%i, n=%i, sum=%i\n",me,nproc,n,sum);
	
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD); //broadcast the input from thread 0 to all threads

	printf("me =%i Print D, nproc=%i, n=%i, sum=%i\n",me,nproc,n,sum);
	
	int low = (me*n/nproc)+1;
	int high = (me+1)*n/nproc;
	
	for(i=low;i<=high;i=i++){ 
		sum=sum+i;
	}
	
	printf("me =%i Print E, nproc=%i, n=%i, sum=%i\n",me,nproc, n,sum);
	
	MPI_Reduce(&sum,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD); //sum the partial sums from threads to total
	if(me==0){
		printf("Sum of first %i integers equals   : %i\n",n,total);
		printf("Sum of first %i integers should be: %i\n",n,(n*(n+1))/2);

	}

	printf("me =%i Print F, nproc=%i, n=%i, sum=%i\n",me,nproc, n,sum);
	
	MPI_Finalize(); // finalize MPI peacefully (the system would kill the processes otherwise)

	return 0;
}

