/*Author: Klevis Tefa

For this problem we can see that there are two variables assigned to zero,
an int parameter that we'll use it throughout the function and an int return
value. The jmp instruction and the cmp, jl tell us that there's a loop in there
we can see that %r12d stores x which is compared with b. We can also see from
the assembly that the return value of the called function (which happens to be rand)
is added to a. This constitutes the loop. The last thing to take care of is 
the return value which we can see that is a/x from the instruction idiv %r12d
*/
#include <stdlib.h>
#include "project2.h"
#include <stdio.h>

//This method is a calculation of the expected value of rand().
//We call it x times and sum the values and then return that sum divided by x.
int problem3(int x) {
	
	int a = 0; //part of return value
	int b = 0; //counter

	while(b < x){
		a += rand(); //summing up all the rands
		b++;

	}
	
	return (a/x); //returning the average
}
