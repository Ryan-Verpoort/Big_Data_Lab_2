#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"

int main()
{
    int N = 10;
	int* A[N];

	for (int j = 0; j < N; j++)
	{
		A[j] = malloc(N*sizeof(*A[j]));
		for (int i = 0; i < N; i++)
		{
			//initialize values to 0
			A[j][i] = 0;
		}
	}    
	 
    clock_t begin1 = clock();
    #pragma omp_set_num_threads(2)
    #pragma omp for collapse(2) 
    
    // Fill up all the indices of A
    for(int j = 0; j < N; j++) 
    { 
		for(int i = 0; i < N; i++) 
		{
			A[j][i] = (N * i) + j;
		}
    }
    
    clock_t end1 = clock();
    
    for(int j = 0; j < N; j++) // Prints the original array
    { 
		for(int i = 0; i < N; i++) 
		{
			printf(" %d", A[j][i]);
		}
	printf("\n");
    }

    printf("\n \n \n"); // Some new lines for the output
 
    clock_t begin2 = clock();
    
    
    //#pragma omp_set_num_threads(2)
    #pragma omp for collapse(2) 
    for(int j = 0; j < N; j++)  // loop indexes only the bottom triangle of matrix and performs the transpose
    {
		for(int i = 0; i < j; i++) 
		{
			int temp = A[j][i];
			A[j][i] = A[i][j];
			A[i][j] = temp;
			temp = 0;
		}
    }
    
    clock_t end2 = clock();
    
    for(int j = 0; j < N; j++)  // Prints out the transposed array now
    {
		for(int i = 0; i < N; i++) 
		{
			printf(" %d", A[j][i]);
		}
	printf("\n");
    }

    for(int i = 0; i < N; i++) { // frees all the memory in the matrix A
	free(A[i]);
    }
    
    double time_spent1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;
    double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("%lf \n",time_spent1+ time_spent2);
 
    return 0;
}
