#include "proj4.h"

// execute a command with optional wait
int runcommand(char **cline, int where) {
    pid_t pid;
    int status;

    //Bug #2 fix
    //check if cd is on the command line
    if (strcmp(*cline, "cd") == 0){

        char *path = cline[1]; //storing the second argument of command line as the path

        if (path == NULL || path == ""){ //First case: check if only cd is typed

            chdir(getenv("HOME")); //go to home directory

        } else if (path != NULL) { //Second case: check if there's a second argument in the command line

            if (strcmp(path,"..") == 0){ //check if the second command line argument is '..''
                
                chdir(path); //go to parent directory

            } else if (path[0] == '/'){ //check if the path directory starts with '/'

                if (chdir(path) != 0) printf("The directory %s does not exist.\n", path); //check if the specified directory does not exist

            } else { //check if directory is specified without the '/' (slash symbol) in front

                char properPath[1024]; //declare a string to store the properly written path with '/' in front
                memset (&properPath[0], 0, sizeof(properPath)); //clearing the char array
                properPath[0] = '/'; //putting the forward slash as the first character of the path
                strcat(properPath, path); //concatenate '/' with the path inserted in the command line (in this case the path was entered without '/' in front);

                char currentDirectory[1024]; //declare a string to store the current working directory;
                memset (&currentDirectory[0], 0, sizeof(currentDirectory)); //clearing the char array;

                if (getcwd(currentDirectory, sizeof(currentDirectory)) != NULL){ //check if the function stored the current directory to currentDirectory properly

                    strcat(currentDirectory, properPath); //concatenate current directory with the path to get the full path of the directory specified by the user

                    if (chdir(currentDirectory) != 0) printf("The directory %s does not exits.\n", path); //check if the specified directory does not exist
                }
            }
        }
    } //Bug #2 fix end

    //Bug #3 fix
    else if (strcmp(*cline, "exit") == 0){ //check if the exit is on the command line
        
        exit(0); //exit the shell successfully

    } //Bug #3 fix end

    else {
        switch(pid=fork()) {
            case -1:
                perror(SHELL_NAME);
                return (-1);
            case 0:
                //Bug #4 fix: Make sure that CTRL+C doesn't kill processes running in the background
                if(where != BACKGROUND) signal(SIGINT, SIG_DFL); //if we're not in the background than cath and handle the signal

                execvp(*cline,cline);
                //we should never get to this code, sice execve does not return
                perror(*cline);
                exit(1);
        }
    }
    // code for parent
    // if background process print pid and exit
    // program is running in the background
    if(where == BACKGROUND) {
        printf("[Process id %d]\n",pid);
        return (0);
    }

    wait(NULL); //Bug 5 fix - wait until child process terminates

    // wait until process pid exits
    if (waitpid(pid,&status,0) == -1)
        return (-1);
    else
        return (status);
}
