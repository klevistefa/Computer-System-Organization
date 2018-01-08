# Problem 1 

1. There is a call to `free()` on line 26 of `prob1.c`. Which function allocates
the memory that is freed be this call? <br>
**Answer:**
	The function that allocates the memory that is freed is the getLine() function.

2. How many times is the function that you named in answer to 1 called? <br>
**Answer:**
	Is called as many time as the number of lines in the file that is being readed plus one more time which is the last call that returns -1 and terminates the while-loop

3. Does the program have a memory leak? Explain your answer. <br>
**Answer:**
	No it does not because the return values of getLine() are allocated in the address of *line and we free that address after we're done with it.



