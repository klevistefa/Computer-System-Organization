/*
Author: Klevis Tefa

For this problem we can see that function4 starts with the return value initilized to 1 and another int local value initialized to 0.
The movsql command shows us that there's a dereferencing of the first parameter, which tells us that it's a pointer to an integer. We
see a loop that compares the y value with the second parameter and increments it by one each step. The value to be returned is multiplied
by the value of the pointer each loop iteration. 
For problem4 method we can see that to return value is initialized to zero and the
two parameters of int type of the function are compared on a loop where the first parameter is incremented each time. Meanwhile the value
to be returned is added the return value of function4 each loop iteration. We can see that the parameters passed to function4 from the 
registers %rdi and %esi are the address of the first parameter of problem4, and number three as the second parameter. After the loop
the assembly frees the stack and returns the rezult.
*/ 
#include "project2.h"

//This function returns a value that it's the value of x to the power of z and then returns it
long function4(int *x, int z) {
	long result = 1; //value to be returned
	
	int y = 0; //counter
	while(y < z){
		result *= *x; //updating the return value
		y++;
	}
	return result;
}

//This function returns a value that adds x-y+1 times the return value of function5
long problem4(int x, int y) {
	long result = 0; // return variable
	
	while(x <= y){
		result += function4(&x, 3); //updating the return value
		x++;
	}
	return result;
}

