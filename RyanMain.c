#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"

int main()
{



    int** A;
    int N = 4;
    A = malloc(N * sizeof(int*)); // pointer to pointer array

    // allocate the memory for the entire array

    for(int k = 0; k < N; k++) {
	A[k] = malloc(N * sizeof(int));
    }
	
	clock_t begin1 = clock();
    for(int j = 0; j < N; j++) { // Fill up all the indices of A
	for(int i = 0; i < N; i++) {
	    A[j][i] = (N * i) + j;
	}
    }
	clock_t end1 = clock();
    for(int j = 0; j < N; j++) { // Prints the original array
	for(int i = 0; i < N; i++) {
	    printf(" %d", A[j][i]);
	}
	printf("\n");
    }

    printf("\n"); // Some new lines for the output
    printf("\n");
    printf("\n");

	clock_t begin2 = clock();
#pragma omp parallel sections
{

	#pragma omp section  
   {
   		int j =0;
	for(int i=j; i<N;i++)
	{
		if(i!=j)
		{
		int temp = A[j][i];
		A[j][i] = A[i][j];
		A[i][j] = temp;
		temp = 0;
		}
	}
	} 
	#pragma omp section  
   {		int j =1;
	for(int i=j; i<N;i++)
	{

		if(i!=j)
		{
		int temp = A[j][i];
		A[j][i] = A[i][j];
		A[i][j] = temp;
		temp = 0;
		}
	}
	}
		#pragma omp section  
   {		
   int j =2;
	for(int i=j; i<N;i++)
	{

		if(i!=j)
		{
		int temp = A[j][i];
		A[j][i] = A[i][j];
		A[i][j] = temp;
		temp = 0;
		}
	}
	} 
}
	 	clock_t end2 = clock();
 printf("Transposed Array \n");
    for(int j = 0; j < N; j++) { // Prints out the transposed array now

	for(int i = 0; i < N; i++) {
	    printf(" %d", A[j][i]);
	}
	printf("\n");
    }
    printf("\n");




    for(int i = 0; i < N; i++) { // frees all the memory in teh matrix A
	free(A[i]);
    }
	
    free(A);

    //clock_t end = clock();
	double time_spent1 = (double)(end1 - begin1) / CLOCKS_PER_SEC;
    double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
    printf("%lf \n",time_spent1+ time_spent2);
 

    return 0;
}
