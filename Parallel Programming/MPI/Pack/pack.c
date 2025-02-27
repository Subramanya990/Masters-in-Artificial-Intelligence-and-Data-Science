// sump.c
// sums first N integers
#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int me,nproc,i;
	int m, n, position;
	float p; double q, r;
	m=1; n=2;
	p=1.2; q=1.23e10; r=0.456;
	char buffer[1000];

	
	MPI_Init(&argc,&argv); // initialise MPI
	MPI_Comm_size(MPI_COMM_WORLD,&nproc); // return total number of processors
	MPI_Comm_rank(MPI_COMM_WORLD,&me); // return number of this processor, me=0..nproc-1
	
	if(me==0){
		position =0;
		MPI_Pack(&m,1,MPI_INT,&buffer,1000,&position,MPI_COMM_WORLD);
		MPI_Pack(&n,1,MPI_INT,&buffer,1000,&position,MPI_COMM_WORLD);
		MPI_Pack(&p,1,MPI_FLOAT,&buffer,1000,&position,MPI_COMM_WORLD);
		MPI_Pack(&q,1,MPI_DOUBLE,&buffer,1000,&position,MPI_COMM_WORLD);
		MPI_Pack(&r,1,MPI_DOUBLE,&buffer,1000,&position,MPI_COMM_WORLD);
	}
	
	MPI_Bcast(buffer,1000,MPI_CHAR,0,MPI_COMM_WORLD);
	
	if(me!=0){
		position=0;
		MPI_Unpack(&buffer,1000,&position,&m,1,MPI_INT,MPI_COMM_WORLD);
		MPI_Unpack(&buffer,1000,&position,&n,1,MPI_INT,MPI_COMM_WORLD);
		MPI_Unpack(&buffer,1000,&position,&p,1,MPI_FLOAT,MPI_COMM_WORLD);
		MPI_Unpack(&buffer,1000,&position,&q,1,MPI_DOUBLE,MPI_COMM_WORLD);
		MPI_Unpack(&buffer,1000,&position,&r,1,MPI_DOUBLE,MPI_COMM_WORLD);
	}
	
	if(me==3){
		printf("%i \n",n);
	}
	
	MPI_Finalize();
	return 0;
}