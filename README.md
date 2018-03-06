Big_Data_Lab_2

This lab requires the in place transposition of an N*N matrix.

The openMP solution looks at the matrix in three nested for loops:

	1.) The first loop goes through the top left quadrant of the array.
	2.) The second loop goes through the bottom right of the array.
	3.) The third loop goes through the remaining two quadrants.

This process is illstrated below where the numbers represent the three searching loops implemented:

	-------------------------
	| 1 | 1 | 1 | 3 | 3 | 3 | 
	-------------------------
	| 1 | 1 | 1 | 3 | 3 | 3 | 
	-------------------------
	| 1 | 1 | 1 | 3 | 3 | 3 |
	-------------------------
	| 3 | 3 | 3 | 2 | 2 | 2 |
	-------------------------
	| 3 | 3 | 3 | 2 | 2 | 2 |
	-------------------------
	| 3 | 3 | 3 | 2 | 2 | 2 |
	-------------------------






