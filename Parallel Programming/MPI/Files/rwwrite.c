#include <stdio.h>
#define LENGTH 200
main()
{
	int i=0; double n2, n6;
	char line[LENGTH];
	FILE *fr, *fw;
	//open file for reading
	fr=fopen("table.txt", "r");
	//open file for writing
	fw=fopen("tableout.txt", "w");

	//endless loop
	while(1){
		//if there is nothing to read break
		if(fgets(line, LENGTH,fr) == NULL)break;
		//getting 2nd and 6th number from the line - if unable to read -> break
		if(sscanf(line, "%lf %lf %lf %lf %lf %lf",&n2,&n2,&n6,&n6,&n6,&n6)==-1) break;
		i++;
		//print on the screen
		printf("%i   %lf   %lf\n", i, n6, n2);
		//print to the output file
		fprintf(fw, "%i   %lf   %lf\n", i, n6, n2);
	}

	printf("Read %i rows\n",i);
	//close the input and output file
	fclose(fr);
	fclose(fw);
}
