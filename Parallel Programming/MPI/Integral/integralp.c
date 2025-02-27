#include<stdio.h>
#include<math.h>
#include<mpi.h>

int exponent = 2;

double f(double x) {
return pow(x,exponent);
}

int main(int argc, char *argv[])
{
	int npoints, i, nproc, me;
	double x,a,b,sum =0, total;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &me);
	
	if(me==0){
		printf(" Input number of points for calculation of integral:\n ");
		scanf("%i", &npoints);
  		printf(" Input lower/higher bound of integration: \n");
  		scanf("%lf", &a);scanf("%lf", &b);
		}

	MPI_Bcast(&npoints,1,MPI_INT,0,MPI_COMM_WORLD);	
	MPI_Bcast(&a,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Bcast(&b,1,MPI_DOUBLE,0,MPI_COMM_WORLD);

	
	for(i=me+1;i<=npoints-1;i=i+nproc) {
    	x=a+i*(b-a)/npoints; // x is the real argument, point where the function is evaluated
    	sum=sum+f(x);
  	}

	MPI_Reduce(&sum,&total,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	
	if(me==0){
	total=total+(f(a)+f(b))/2; // add first/last points 				
	total=total*(b-a)/npoints; // result of integration
	printf(" The integral equals numerically %f \n",total);
	printf(" The integral equals analytically %f \n",(pow(b,exponent+1)-pow(a, exponent+1))/(exponent+1));
	}
	MPI_Finalize();
	return 0;
}

