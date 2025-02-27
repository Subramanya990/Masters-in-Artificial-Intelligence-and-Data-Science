// sump.c
// sums first N integers
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int me,nproc,i,n,sum=0,total,dest, source = 0, tag =101;
	MPI_Status status;
	
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
	
	if(me == 0){
		for(dest=1; dest < nproc; dest++){
			MPI_Send(&n, 1, MPI_INT, dest,tag,MPI_COMM_WORLD);
		}
	}
	else{
		MPI_Recv(&n,1 ,MPI_INT, source,tag, MPI_COMM_WORLD, &status);
	}
	

	printf("me =%i Print D, nproc=%i, n=%i, sum=%i\n",me,nproc,n,sum);
	
	for(i=me+1;i<=n;i=i+nproc) { 
		sum=sum+i;
	}
	
	printf("me =%i Print E, nproc=%i, n=%i, sum=%i\n",me,nproc, n,sum);
	
	if(me!=0){
		MPI_Send(&sum, 1,MPI_INT, 0,tag,MPI_COMM_WORLD);
	}
	else{
		total = sum;
		for(source = 1; source < nproc;source++){
			MPI_Recv(&sum, 1, MPI_INT, source, tag, MPI_COMM_WORLD,&status);
			total = total + sum;
		}
		printf("Sum of first %i integers equals   : %i\n",n,total);
		printf("Sum of first %i integers should be: %i\n",n,(n*(n+1))/2);
	}

	printf("me =%i Print F, nproc=%i, n=%i, sum=%i\n",me,nproc, n,sum);
	
	MPI_Finalize(); // finalize MPI peacefully (the system would kill the processes otherwise)

	return 0;
}

