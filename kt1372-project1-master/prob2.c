
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[] )  {
	FILE *fpi;
	FILE *fpo;
	fpo = fopen(argv[2], "w");
	int c;
	//int temp;

	fpi = fopen(argv[1], "r");
	while((c=fgetc(fpi)) != EOF){
		int temp1 = c >> 4;
		int temp2 = c << 4;
		c = temp1 | temp2;
		putc(c, fpo);
	}
	fclose(fpi);
	fclose(fpo);    
    
    return 0;
}
