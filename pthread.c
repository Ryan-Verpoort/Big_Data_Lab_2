

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "omp.h"

#define NTHREADS 4
#define N 8192	
int* A[N];
//pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *Transpose(void *args)
{
    int *argPtr = args;

    //int i,j,sum = 0;
    int threadindex = *argPtr;
 
    for(int i = 0; i < N; i++)
    {
		if (i % NTHREADS != threadindex) continue;
		for(int j = 0; j < i; j++) 
		{
			int temp = A[i][j];
			A[i][j] = A[j][i];
			A[j][i] = temp;
			//printf("TEST");
		}
    }
    //Mutex must go here
	//pthread_mutex_lock( &mutex1 );
  	//pthread_mutex_unlock( &mutex1 );
    //Pass the value back:
    //*argPtr = sum;
}


int main()
{
    //int N = 10;
    pthread_t thread_id[NTHREADS];
    int thread_args[NTHREADS];

		// Fill up all the indices of A
		for (int i = 0; i < N; i++)
		{
			A[i] = malloc(N*sizeof(*A[i]));
			for (int j = 0; j < N; j++)
			{
				//initialize values to 0
				A[i][j] = (N * i) + j;
			}
		}    

    // Prints the original array
    for(int j = 0; j < N; j++) 
    { 
		for(int i = 0; i < N; i++) 
		{
			//printf(" %d", A[j][i]);
		}
		//printf("\n");
    }
	// Some new lines for the output
    //printf("\n \n \n"); 
	//pthread_mutex_init(&mutex1, NULL);

 double begin1 = omp_get_wtime();
		for(int i = 0; i < NTHREADS; i++)
		{
			thread_args[i] = i;
			pthread_create( &thread_id[i], NULL, Transpose, &thread_args[i]);
		}
		for(int i = 0; i < NTHREADS; i++)
		{
			pthread_join( thread_id[i], NULL);
		}
 	double end1 = omp_get_wtime() - begin1;

 double begin2 = omp_get_wtime();
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < i; j++) 
			{
				int temp = A[i][j];
				A[i][j] = A[j][i];
				A[j][i] = temp;
			}
		}
 	double end2 = omp_get_wtime() - begin2;

	// Prints out the transposed array now
    for(int j = 0; j < N; j++)
    {
		for(int i = 0; i < N; i++) 
		{
			//printf(" %d", A[j][i]);
		}
		//printf("\n");
    }

	// frees all the memory in the matrix A
    for(int i = 0; i < N; i++) 
	{ 
		free(A[i]);
    }
    
    printf("%lf \n", end1);
 	printf("%lf \n", end2);
    return 0;
}
