
#include "proj4.h"


int main()
{

	//Bug #4 fix
	signal(SIGINT, sigint_handler); //installing the SIGINT handler


    //run the shell until EOF (keyboard Ctrl+D) is detected
    while (userinput(  ) != EOF ) {

        procline();
    }
    return 0;
}

//Bug #4 fix
//function created to catch and handle SIGINT; the function just returns;
void sigint_handler(){
		return; //just return
}

//Author: Klevis Tefa

/*
Bug #1 Fix (procline.c: lines 11-12) ->
	Bug #1 was fixed by initializing number of arguments (variable narg) to 0.
	We can see that each argument is assigned in integer which corresponds to
	the type of argument that it is (variable toktype). Depending on the character
	type (i.e., ampersand), the executable is either run in the foreground (i.e.,
	toktype != AMPERSAND) or background (i.e., toktype == AMPERSAND). This is 
	defined by the type variable. Now all command line arguments will have a value
	assigned, and the array of command line arguments along with its address is
	passed to runcommand. After return, narg is reassigned to 0, so that the next
	set of command line can be assessed correctly. The reason we need this is because
	procline() is being called continously from the main function in proj4.c.

Bug #2 Fix (runcommand.c: lines 8-46) ->
	Bug #2 was fixed by implementing the cd command manually like the prompt required
	The way that this was done was by making the code recognize when the cd command was
	passed to the command line and based on the three scenarios that were asked to be fixed
	by the promp the code reacted differently. For example if there was no other argument 
	that followed cd, the user goes to home directory. If there's an argument then the code
	tries to figure it out if it's '..' or a path name. For the first case the code take you
	to the parent directory of the current working directory. For the second case the code
	sees if that directory exists and if it does it takes you there. Otherwise it gives you
	an error message.

Bug #3 Fix (runcommand.c: lines 48-53) ->
	Bug #3 was fixed by implmeneting the exit command manually. The way that this was done
	was by making the code recognize when the user passes the exit command to the command
	line argument. Once the code recognizes the command the function exit(0) is called, so
	the successfull termination of the shell occurs.

Bug #4 Fix (proj4.c: lines 9, 20-24; runcommand.c: 61-62; proj4.h: lines 38) ->
	Bug #4 was fixed by catching and handling SIGINT signal received manually rather than
	using its default functionality. In this case the prompt required to terminate the current
	process as opposed to the shell itself so by making the handler function just return as the
	signal is received, the handler will terminate the current process. Also by including the lines
	of code 61-62 in runcommand.c we make sure that CTRL+C doesn't terminate background processes
	since those are supposed to be terminated by kill pid function.

Bug #5 Fix (proj4.c: lines 75) ->
	Bug #5 was fixed by adding the wait function that makes sure that the parent process
	reaps its respective child processes running on the background. By including the wait(NULL)
	function the code makes sure that a parent process waits until its child processes are
	terminated. When the child processes are terminated, the next pieces of code reap all the
	terminated child processes making sure there are no more "zombies".


*/