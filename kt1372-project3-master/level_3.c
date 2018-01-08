/*
 * author: Klevis Tefa
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "proj3.h"

// Implement a C function called level_3_opt. It should perform the same 
// task as the implemented level_3 function. 
// In the comments for the function describe why your changes make the
// function more cache friendly. 
// Note that this function does not return any value. It modifies the array
// that is passed to it, instead. 

void level_3 (int *A, int n)
{
    int  i, j;
    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
        A[j*n + i] = A[j*n + i] || A[i*n + j];
          
}


/*In this function we see that A[j*n+i] is requested twice so it would be faster
if the outer loop was the j loop and the inner loop was the i loop. It is the same logic
as in level_0 and level_1
*/
void level_3_opt (int *A, int n)
{
    int  i, j;
    //The only difference is the order of the loops
    for (j = 0; j < n; j++)
    	for (i = 0; i < n; i++)
        	A[j*n + i] = A[j*n + i] || A[i*n + j];
}




