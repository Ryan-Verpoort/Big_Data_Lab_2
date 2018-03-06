#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "omp.h"

#define NTHREADS 4
#define N 10
int* A[N];
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *Transpose()//void *args)
{
    //int *argPtr = args;

    //int i,j,sum = 0;
    //int threadindex = *argPtr;
 
    for(int i = 0; i < N; i++)
    {
	//if (i % NTHREADS != threadindex) continue;
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
    // Pass the value back:
    //*argPtr = sum;
}


int main()
{
        //int N = 10;
    pthread_t thread_id[NTHREADS];
    //int thread_args[NTHREADS];

	clock_t begin1 = clock();
	// Fill up all the indices of A
	for (int j = 0; j < N; j++)
	{
		A[j] = malloc(N*sizeof(*A[j]));
		for (int i = 0; i < N; i++)
		{
			//initialize values to 0
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
 //pthread_mutex_init(&mutex1, NULL);
    clock_t begin2 = clock();
    
    	
	for(int i=0; i < NTHREADS; i++)
	{
		thread_args[i] = i;
		pthread_create( &thread_id[i], NULL, Transpose, NULL);
	}
    for(int j=0; j < NTHREADS; j++)
    {
        pthread_join( thread_id[j], NULL);

    }
//////////////////
    
    clock_t end2 = clock();

    clock_t begin3 = clock();
    for(int i = 0; i < N; i++)
    {
	for(int j = 0; j < i; j++) 
	{
		int temp = A[i][j];
		A[i][j] = A[j][i];
		A[j][i] = temp;
	}
    }
    clock_t end3 = clock();
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
    double time_spent3 = (double)(end3 - begin3) / CLOCKS_PER_SEC;
    printf("%lf \n",time_spent1+ time_spent2);
 printf("%lf \n", time_spent1+ time_spent3);
    return 0;
}
