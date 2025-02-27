#include<stdio.h>
#include<math.h>
#include<mpi.h>

int exponent = 2;

double f(double x) {
return pow(x,exponent);
}

int main(int argc, char *argv[])
{
	int npoints, i, nproc, me, dest, source = 0,tag =101;
	double x,a,b,sum =0, total;
	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&nproc);
	MPI_Comm_rank(MPI_COMM_WORLD, &me);
	
	if(me==0){
		printf(" Input number of points for calculation of integral:\n ");
		scanf("%i", &npoints);
  		printf(" Input lower/higher bound of integration: \n");
  		scanf("%lf", &a);scanf("%lf", &b);
		}
		
	if(me == 0){
		for(dest=1; dest <= nproc-1; dest++){
			MPI_Send(&npoints, 1, MPI_INT, dest,100,MPI_COMM_WORLD);
			MPI_Send(&a, 1, MPI_DOUBLE,dest,103,MPI_COMM_WORLD);
			MPI_Send(&b, 1, MPI_DOUBLE, dest, 102, MPI_COMM_WORLD);
		}
	}
	else{
		MPI_Recv(&npoints,1 ,MPI_INT, source,100, MPI_COMM_WORLD, &status);
		MPI_Recv(&a,1 ,MPI_DOUBLE, source,103, MPI_COMM_WORLD, &status);
		MPI_Recv(&b,1 ,MPI_DOUBLE, source,102, MPI_COMM_WORLD, &status);
	} 

	for(i=me+1;i<=npoints-1;i=i+nproc) {
    	x=a+i*(b-a)/npoints; // x is the real argument, point where the function is evaluated
    	sum=sum+f(x);
  	}

	if(me!=0){
		MPI_Send(&sum, 1,MPI_DOUBLE, 0,tag,MPI_COMM_WORLD);
	}
	else{
		total = sum;
		for(source = 1; source <=nproc-1; source++){
			MPI_Recv(&sum,1,MPI_DOUBLE,source,tag,MPI_COMM_WORLD, &status);
			total = total + sum;
		}
	}
	if(me == 0){
		for(dest=1; dest <=nproc-1; dest++){
			MPI_Send(&total, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
		}
	}
	else{
			MPI_Recv(&total, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
		}
	if(me==2){
	total=total+(f(a)+f(b))/2; // add first/last points 				
	total=total*(b-a)/npoints; // result of integration
	printf(" The integral equals numerically %f \n",total);
	printf(" The integral equals analytically %f \n",(pow(b,exponent+1)-pow(a, exponent+1))/(exponent+1));
	}

	MPI_Finalize();
	return 0;
}

