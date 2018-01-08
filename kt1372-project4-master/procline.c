
#include "proj4.h"


/* shell input line */
int procline(void)
{

    char *arg[MAXARG + 1];  // pointer array for runcommand
    
    //Bug #1 fix: initialize narg to 0 (number of arguments so far)
    int narg = 0;              // number of arguments 
    
    int toktype = 0;            // type of token in command
    int type = 0;               // type =  FOREGROUND or BACKGROUND


    while ( 1 ) // loop forever
    {
        // take action according to token type
        switch(toktype = gettok(&arg[narg]))
        // gettok finds the type of the token
        {

        case ARG:
            if(narg<MAXARG)
                narg++;
            break;

        case EOL: 
        case SEMICOLON:
        case AMPERSAND:
            if(toktype == AMPERSAND)
                type = BACKGROUND;
            else
                type = FOREGROUND;

            if(narg != 0)
            {
                arg[narg] = 0;
                runcommand(arg,type);
            }
            narg = 0;

            if( toktype == EOL )
                return;
            narg = MAXARG;
            break;
        }
    }
}
