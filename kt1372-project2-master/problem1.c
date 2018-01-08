/*
Author: Klevis Tefa

We can see that second parameter + 3 is added to rcx then tested if second parameter >= 0
which overides rcx with second parameter value. This happens because we want to get the upperbound
when we devide it by 4 if the second parameter is negative. The +3 part allows us that. Then the following
assembly instructions are arithmetic operations which result in x+y/4+12*z which is then returned.
*/
#include "project2.h"

//A method that does arithmetic operations on its four parameters
long problem1(long x, long y, long z) {
	
	return (x+(y/4)+(12*z));	
}
