#include <stdio.h>
#include<mpi.h>
int main(int argc, char *argv[]){
	int me, i ,nproc, n, fact=1,total;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD,&me);
	
	if(me==0){
		printf("Enter the number:");
		scanf("%i",&n);
	}
	
	printf("me =%i Print A, nproc=%i, n=%i, fact=%i\n",me,nproc,n,fact);
	MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
	
	printf("me =%i Print B, nproc=%i, n=%i, fact=%i\n",me,nproc,n,fact);
	for(i=me+1;i<=n;i=i+nproc){
		fact = fact*i;
	}
	
	printf("me =%i Print C, nproc=%i, n=%i, fact=%i\n",me,nproc,n,fact);
	MPI_Reduce(&fact,&total,1,MPI_INT,MPI_PROD,0,MPI_COMM_WORLD);
	
	if(me==0){
	printf("Factorial of %i numbers: %i",n,total);
	}
	
	printf("me =%i Print D, nproc=%i, n=%i, fact=%i\n",me,nproc,n,fact);
	MPI_Finalize();
	return 0;
}