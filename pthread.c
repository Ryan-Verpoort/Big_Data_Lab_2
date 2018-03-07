#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "omp.h"

#define NTHREADS 128
#define N 8192
int* A[N];

void *Transpose(void *args)
{
    int *argPtr = args;
    int i,j,temp = 0;
    int threadindex = *argPtr;
	
	// Loop through the top left quadrant of the array
	for (i = 0; i < N / 2 - 1; i++) 
	{ if (i % NTHREADS != threadindex) continue;
		for (j = i + 1; j < N / 2; j++) 
		{
			temp = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = temp;
		}
	}

	// Loop through the bottom right quadrant of the array
	for (i = N / 2; i < N - 1; i++) 
	{ if (i % NTHREADS != threadindex) continue;
		for (j = i + 1; j < N; j++) 
		{
			temp = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = temp;
		}
	}

	//Loop through the top right and bottom left quadrants of the array
	for (i = N / 2; i < N; i++) 
	{ if (i % NTHREADS != threadindex) continue;
		for (j = 0; j < N / 2; j++) 
		{
			temp = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = temp;
		}
	}
}


int main()
{

    pthread_t thread_id[NTHREADS];
    int thread_args[NTHREADS];

	// Fill up all the indices of A
	for (int i = 0; i < N; i++)
	{
		A[i] = malloc(N*sizeof(*A[i]));
		for (int j = 0; j < N; j++)
		{
			A[i][j] = (N * i) + j;
		}
	}    
	
/*
    printf("\n Printing the intilialised array \n");
    for(int j = 0; j < N; j++) 
    { 
		for(int i = 0; i < N; i++) 
		{
			printf(" %d", A[j][i]);
		}
		printf("\n");
    }
*/

 	double StartPthread = omp_get_wtime();
 	//Create threads and transpose Array
	for(int i = 0; i < NTHREADS; i++)
	{
		thread_args[i] = i;
		pthread_create( &thread_id[i], NULL, Transpose, &thread_args[i]);
	}
	for(int i = 0; i < NTHREADS; i++)
	{
		pthread_join( thread_id[i], NULL);
	}
 	double StopPthread = omp_get_wtime() - StartPthread;

	double StartNaive = omp_get_wtime();
	//Naive approach Transpose array
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < i; j++) 
		{
			int temp = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = temp;
		}
	}
	double StopNaive = omp_get_wtime() - StartNaive;

/*
	printf("\n Printing the transposed array \n");
    for(int j = 0; j < N; j++)
    {
		for(int i = 0; i < N; i++) 
		{
			printf(" %d", A[j][i]);
		}
		printf("\n");
    }
*/
	// frees all the memory in the matrix A
    for(int i = 0; i < N; i++) 
	{ 
		free(A[i]);
    }
    
    //Print Time taken for Parallel and Naive Approach
    printf("Pthread Parallel Time: %lf \n", StopPthread);
 	printf("Naive Time: %lf \n", StopNaive);
    return 0;
}
