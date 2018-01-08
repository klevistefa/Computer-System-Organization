/*
 * author: Klevis Tefa
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "proj3.h"

// Implement a C function called level_1_opt. It should perform the same 
// task as the implemented level_1 function. 
// In the comments for the function describe why your changes make the
// function more cache friendly. 
//
// Note: your function needs to compute the entire matrix C,
// not only its x entry. 

long level_1(long * B, long * A, int x)
{
    long * C = (long * ) malloc (N*sizeof(long) );
    if (!C) return 0; 
    
    int c, r; 

    for(c = 0; c < N; c++)
        for(r = 0; r < N; r++)
            C[ r ] += B[ r*N + c ] + A[ c*N + r ] ;

    long ret = C[x];
    free (C); C = 0; 
    return ret;
}


/*This one is similar to the previous one except here we're dealing with
addition of two slightyl differently accessed array. In this case B is accessed
through the index r*N+c and A is accessed through the index of c*N+r. So no matter how
we order the loops, one part of both indexes (r*N or c*N) has to be repeatedly missed on the
cache. However if we can seperate the statement in two seperate nested loops and access only the
array that gives us faster reading time this will improve the general performance of the program.
*/
long level_1_opt(long * B, long * A, int x)
{
    // DO NOT modify the following declarations 
    long * C = (long * ) malloc (N*sizeof(long) );
    if (!C) return 0; 
    
    // enter your code here 
    
    int r, c; 

    //In case where elements of B are added to c[r], access time will be faster
    //if r loop is the outer one and c loop the inner one. This because we're
    //accessing index r*N + c;
    for(r = 0; r < N; r++){
        for(c = 0; c < N; c++){
            C[ r ] += B[ r*N + c ];//updating all of C partially
        }
    }

    //In case where elements of A are added to c[r], access time will be faster
    //if c loop is the outer one and r loop the inner one. This because we're
    //accessing index c*N + r;
    for (c = 0; c < N; c++){
        for (r = 0; r < N; r++){
            C[r] += A[ c*N + r];//updating whole of C with the remaining part
        }
    }
    //DO NOT modify the rest of this function 
    long ret = C[x];
    free (C); C=0;
    return ret;
}


