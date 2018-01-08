/*
 * author: Klevis Tefa
 * 
 */
  
#include <stdlib.h>
#include <stdio.h>

#include "proj3.h"


// Implement a C function called level_0_opt. It should perform the same 
// task as the implemented level_0 function. 
// In the comments for the function describe why your changes make the
// function more cache friendly. 

// Note: this is a warmup level. It will not be graded. 

int level_0( int * B, int x, int y )
{
    if (!B) return -1; 
    
    int c, r; 

    for(c = 0; c < N; c++)
        for(r = 0; r < N; r++)
            B[ r*N + c ] = 2*(B[ r*N + c ] + 2);

    
    return  B[ x*N + y ];
}

/*changing the order of the loops makes the program more cache friendly because
if r is on the outer loop then r*N will be stored in the cache till the first iteration
of the inner loop. In the previous case r*N changed every loop iteration because r was in
the inner loop.
*/
int level_0_opt( int * B, int x, int y )
{
	if (!B) return -1; //checking if B is null

	int c,r;

	for(r = 0; r < N; r++)
		for(c = 0; c < N; c++)
			B[r*N+c] = 2*(B[r*N+c] + 2); //updating B

    return  B[x*N+y];
}
