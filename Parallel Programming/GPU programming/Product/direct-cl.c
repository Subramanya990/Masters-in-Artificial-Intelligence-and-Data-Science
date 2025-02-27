// nthreads = number of GPU threads
#pragma OPENCL EXTENSION cl_khr_fp64 : enable
// #pragma CL_USE_DEPRECATED_OPENCL_1_0_APIS 
__kernel void energy(
     __global double *matrix_a, 
	   __global double *matrix_b,
	   __global double *matrix_c,
		uint matsize)
{
	// obtaining the index of a thread - analogue to  MPI_Comm_rank
	int me = get_global_id(0);
	int row = me/matsize;
	int column = me - row*matsize;
	double sum =0;
	for(int k=0; k<matsize; k++)
		sum += matrix_a[row*matsize+k]*matrix_b[k*matsize + column];
	matrix_c[me] = sum;
}
