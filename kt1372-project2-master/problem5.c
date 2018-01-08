/*
Author: Klevsi Tefa

For function4 we can see that the return register is initialized to 0
at first. We see that there are some registers being used to perform
some arithmetical operations, we can see that there's dereferincing
so one of the parameters is a pointer to a long value, We can also
see that there's also two local variable one long, and one pointer
to long. The pointer parameter can be treated as an array and we
see that the assembly is accessing result away indexes from the pointer
and putting it to local declared pointer. Then the long variable takes
the value of the dereference local long pointer; Multiple lines of lea
result to updating the value of long pointer to 201 time the local long
variable, we increment the counter and the loop will start again if the
condition is true. From the assembly of problem5 we can see that there's
no return value of this function

For problem5 we can see that there's just one parameter of int type that
is stored first locally to another int variable. The next flew lines of 
code create space for the new long pointer to be declared which will have
space the amount of the first parameter. Then the assembly checks if the
allocation of space was successful, and the next few lines treat the pointer
as an array initializing all its indexes with the value of index, the next few
lines load the parameters for function5 and then call it. At the end the
function returns the long pointer that was created.

*/
  

#include <stdlib.h> 
#include <stdio.h>
#include "project2.h"

//This function multiplies all the values in arr with 201;
void function5(long *arr, int y) {
	int counter = 0;
	long temp;
	long *temp2;

	while (counter < y){

		temp2 = &(arr[counter]); //storing the address of the current value of the array 
		temp = *temp2; //storing the value of the previous stored address
		*temp2 = 201*temp; //updating the value stored at the address by multiplying it by 201
		
		counter++;
	}

		
}

//This function creates an array of size x and initializes all its values with their corresponding index.
//Then it calls function5 which is describe above
long* problem5(int x) {
	
	//creating an pointer of long type and allocating x entries of long type
	long *arr =  (long*)malloc(x*sizeof(long));
	//checking if malloc was successful
	if (arr == 0) return 0;
	
	int y = 0;
	while (y < x){
		arr[y] = y;//initializing the array with values of 0 to x-1
		y++;
	}

	function5(arr, x);

	return arr;

}
