// sumo.c
// sums first N integers
#include <stdio.h>
#include <omp.h>
int main(){
	int i,n,sum=0;

	printf("Program for summing first N integer numbers\n ");
	printf("Enter N: ");scanf("%i", &n);
	
	
	#pragma omp parallel for reduction(+:sum)
	for(int i=1;i<=n;i=i+1) { 
		printf("Number of threads %i\n",omp_get_num_threads());
		sum=sum+i;
	}
	
	printf("Sum of first %i integers equals   : %i\n",n,sum);
	printf("Sum of first %i integers should be: %i\n",n,(n*(n+1))/2);

	return 0;
}

