#include <stdio.h>
#include <stdlib.h>

int main()
{
    int** A;
    int N = 3;
    int ConstN = 2;
    A = malloc(N * sizeof(int*)); // pointer to pointer array

    // allocate the memory for the entire array

    for(int k = 0; k < N; k++) {
	A[k] = malloc(N * sizeof(int));
    }

    for(int j = 0; j < N; j++) { // Fill up all the indices of A
	for(int i = 0; i < N; i++) {
	    A[j][i] = (ConstN * i) + j;
	}
    }

    for(int j = 0; j < N; j++) { // Prints the original array
	for(int i = 0; i < N; i++) {
	    printf(" %d", A[j][i]);
	}
	printf("\n");
    }

    printf("\n"); // Some new lines for the output
    printf("\n");
    printf("\n");

    for(int j = 0; j < N; j++) { // loop indexes only the bottom triangle of matrix and performs the transpose

	for(int i = 0; i < N; i++) {

	    if(i == j) {
		break;
	    } else {
		int temp = A[j][i];
		A[j][i] = A[i][j];
		A[i][j] = temp;
		temp = 0;
	    }
	}
    }

    for(int j = 0; j < N; j++) { // Prints out the transposed array now

	for(int i = 0; i < N; i++) {
	    printf(" %d", A[j][i]);
	}
	printf("\n");
    }

    for(int i = 0; i < N; i++) { // frees all the memory in teh matrix A
	free(A[i]);
    }

    free(A);

    return 0;
}
