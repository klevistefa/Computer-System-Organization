/*
Author: Klevis Tefa

In this case we can see that there's only one parameter that is is passed to %eax, which means
that the parameter was of 32-bit and so was the return value. The next assembly instruction was to
rotate left 4 bits of the rightmost byte (since it uses %al). Which is the same as swapping the last 4 
bits with the second to last 4 bits. This can be easily done with shiftin x leftwards by 4 and doing an
bit or with x shifted rightwards by 4. We use unsigned int as a parameter so the rightward shift is logical
instead of arithmetical
*/ 
#include "project2.h"

//This program swaps the last 4 bits with the second to last 4 bits of the paratemeter and then returns the new value
int problem2(unsigned int x) {
	
	//Using logical shifts on an unsigned ints to perform the swap
	return (((x>>8)<<8) | (((x<<24)>>28) | ((x<<28)>>24)));
}
