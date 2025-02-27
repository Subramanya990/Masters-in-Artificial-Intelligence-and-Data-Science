// compilation: cc  -lm integral.c
// compilation: icc -lm integral.c
// compilation: icc     integral.c

//calculates integral of a function

// libraries
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#define LENGTH 100

// global variable - to be used in main and function f
int exponent=2; // assign exponent of the power function

double f(double x) {
	return pow(x,exponent);
} // end of function

int main(int argc, char *argv[]) 
{
	int npoints,i, me, nproc;
	double x,a,b,sum=0,total; // the variable sum is nulled before summation
	char line[LENGTH]; 
	FILE *fp, *fw;
	
	fw = fopen("op.txt","w");
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &me);
	
	if(me==0){
		fp = fopen("input.txt","r");
		fgets(line, LENGTH,fp);
		sscanf(line, "%i",&npoints);
		
		fgets(line, LENGTH,fp);
		sscanf(line, "%lf %lf", &a,&b);
		
		fclose(fp);
	}
	MPI_Bcast(&npoints,1,MPI_INT,0,MPI_COMM_WORLD);	
	MPI_Bcast(&a,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
	MPI_Bcast(&b,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
	
	// loop over all interior points
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
	fprintf(fw," The integral equals numerically %f \n",total);
	fprintf(fw," The integral equals analytically %f \n",(pow(b,exponent+1)-pow(a, exponent+1))/(exponent+1));
	}
	MPI_Finalize();
	return 0;
}

