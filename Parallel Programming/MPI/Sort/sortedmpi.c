#include <stdio.h>
#include <sys/time.h>
#include <mpi.h>
#define max_len 400000
#define LENGTH 40

double timediff(struct timeval start, struct timeval end)
{
	return ((end.tv_sec  - start.tv_sec)+(end.tv_usec - start.tv_usec)/1e6);
}

int main(int argc, char* argv[]){
	int number_of_lines=0,me,nproc,gather[max_len]={0};
	int swap;
	char in_name[] = "sort.txt";
	char out_name[] = "sortedmpi.txt";
	char line[LENGTH];
	int items[max_len];
	FILE *fp;
	struct timeval t1,t2;
	double time;
	
	
	MPI_Init(&argc,&argv); // initialise MPI
	MPI_Comm_size(MPI_COMM_WORLD,&nproc); // return total number of processors
	MPI_Comm_rank(MPI_COMM_WORLD,&me);

	//read the input
	fp=fopen(in_name,"r");
	if(fp==NULL){printf("Input file %s not found\n",in_name);  return 0;}

	while(1)
	{
		if(fgets(line, LENGTH,fp)==NULL) break; // finish reading when empty line is read
		if(sscanf(line, "%d",&items[number_of_lines])==-1) break; // finish reading after error
			
		number_of_lines++;
	}

	printf("Number of items: %i\n",number_of_lines);

	gettimeofday(&t1, NULL);
	
	MPI_Bcast(&number_of_lines,1,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&items,number_of_lines,MPI_INT,0,MPI_COMM_WORLD);
	
	//sorting bubble sort
	for (int i = me; i < number_of_lines - 1; i=i+nproc)
	{
		for (int j = 0; j < number_of_lines - i - 1; j++)
		{	
			if (items[j] > items[j+1])
			{
				swap = items[j];
				items[j] = items[j+1];
				items[j+1] = swap;
				
			}

		}
	}
	
	MPI_Gather(&items,number_of_lines,MPI_INT,&gather,number_of_lines,MPI_INT,0,MPI_COMM_WORLD);
	
	gettimeofday(&t2, NULL);
	time = timediff(t1,t2);

	printf("time: %lf\n", time);

	if(me==0){
		fp = fopen(out_name, "w");
		for(int i = 0; i < number_of_lines; i++) 
		{
			fprintf(fp,"%d\n",items[i]);
		}
		fclose(fp);
	}
	MPI_Finalize();
	return 0;
}

