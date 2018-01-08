/*
 * author: Klevis Tefa
 * 
 */
  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "proj3.h"

// Implement a C function called level_2_opt. It should perform the same 
// task as the implemented level_2 function. 
// In the comments for the function describe why your changes make the
// function more cache friendly. 

// Note: you may observe that this function performs "useless" looping
// over an array of structures that are all filled with zero bits. 
// Your task is not to remove that "useless" code, but modify it 
// so that it is more cache friendly. 
// You also should not be removing any parts of the structures.
//
// (In an actual application, the structures would be populated with
// real data and the loop would be computing some real results.) 


char * level_2()
{    
    data_2 * B = (data_2 * ) calloc( LARGER, sizeof(data_2) ) ;
    if (!B) return 0; 
    double sum_f = 0.0;
    double sum_n = 0; 
    char * sum_c = (char*) malloc( (2*LARGER + 1) * sizeof(char) );    
    sum_c[2*LARGER] = '\0'; 
    
    int i; 

    for(i = 0; i < LARGER; i++){
        sum_f += B[i].f1 + B[i].f2; 
    }

    for(i = 0; i < LARGER; i++){
        sum_n += B[i].n1 + B[i].n2; 
    }

    for(i = 0; i < LARGER; i++){ 
        sum_c[2*i] = B[i].c1;
    }

    for(i = 0; i < LARGER; i++){
        sum_c[2*i+1] = B[i].c2;
    }
    
    
    free(B); 
    return sum_c;
}


/*For this level I used my own data structure that I have explained in proj3.h why it's better to use.
For further optimization of the level since we're accessing some element of B[i] in each loop we can
easily include all of those operation of the 4 loops in a single loop, which would reduce the significantly
the cache misses.
*/
char * level_2_opt()
{    
    // create the array of structures (same or equivalent to the one
    // in the function above: 
    data_2_opt * B = (data_2_opt * ) calloc( LARGER, sizeof(data_2_opt) ) ;
    if (!B) return 0; 
    // DO NOT modify the following declarations 
    double sum_f = 0.0;
    double sum_n = 0; 
    char * sum_c = (char*) malloc( (2*LARGER + 1) * sizeof(char) );    
    sum_c[2*LARGER] = '\0';     
    
    // enter your code here (make sure to free the array B once 
    // before returning) 
    int i; 

    //the merged loop of the four loops in level_2
    for(i = 0; i < LARGER; i++){
        //the following are the same statements as the ones in level_2
        sum_f += B[i].f1 + B[i].f2;
        sum_n += B[i].n1 + B[i].n2;
        sum_c[2*i] = B[i].c1;
        sum_c[2*i+1] = B[i].c2;
    }  
    
    free(B); 
    
    //DO NOT modify the rest of this function 
    return sum_c;
}

