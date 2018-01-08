#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "proj1.h"



/*********************************
 * Problem 3 required functions  *
 *********************************/

int is_normalized ( float f ) {
	
	char *bits_of_numbers = get_bits_float(f);
	int i;
	int num_of_zeros = 0;
	for (i = 1; i < 9; i++){
		//counting the number of zeros in exp field
		if (bits_of_numbers[i] == '0') num_of_zeros++;
	}
	free(bits_of_numbers);
	bits_of_numbers = NULL;
	//if there are 8 zeros or no zeros that means that its either special or denormalized so return 0
	if (num_of_zeros == 8 || num_of_zeros == 0) return 0;
	//otherwise return 1
	return 1;

}

/***********/ 

int is_denormalized ( float f ) {
	
	char *bits_of_numbers = get_bits_float(f);
	int i;
	for (i = 1; i < 9; i++){
		//checking the exp bits if there is a 1 in exp to terminate the method and return 0
		if (bits_of_numbers[i] == '1'){
			free(bits_of_numbers);
			bits_of_numbers = NULL;
			return 0;
		}
	}
	free(bits_of_numbers);
	bits_of_numbers = NULL;
	//passed the no-ones test so we can return 1 now
	return 1;
}

/***********/ 

int is_special ( float f ) {
	
	char *bits_of_numbers = get_bits_float(f);
	int i;
	for (i = 1; i < 9; i++){

		//checking if there's a zero in exp to terminate the method and return 0
		if (bits_of_numbers[i] == '0'){
			free(bits_of_numbers);
			bits_of_numbers = NULL;
			return 0;
		}
	}
	free(bits_of_numbers);
	bits_of_numbers = NULL;
	//no zero-test has passed so we can return 1
	return 1;

}

/***********/ 
char * get_M ( float f ) {
	if (is_special(f)){
		char *bits_of_M = (char*) malloc (1);
		bits_of_M[0] = '\0';
		return bits_of_M;
 	}	
	//Getting the bits of the float and storing that to a char pointer
	char *bits_of_numbers = get_bits_float(f);
	//creating a char pointer the size of M to store the right bits
	char *bits_of_M = (char*) malloc (26);
	//assigning 1 or 0 as the first element in the address depending on the type of encoding
	if (is_normalized(f)){bits_of_M[0] = '1';}
	else{ bits_of_M[0] = '0';}

	bits_of_M[1] = '.';
	int i;
	//copying the right bits 1 by 1
	for (i = 9; i < 32; i++){
		bits_of_M[i - 7] = bits_of_numbers[i];
	}
	free(bits_of_numbers);
	bits_of_numbers = NULL; 

	//terminating the array
	bits_of_M[25] = '\0';
	return bits_of_M;

}

/***********/ 

int get_s ( float f ) {
	
	char *bits_of_numbers = get_bits_float(f);
	char s = bits_of_numbers[0];
	free(bits_of_numbers);
	bits_of_numbers = NULL;
	if (s == '1') return 1;
	return 0;
}

/***********/ 

int get_E ( float f ) {
	if (is_denormalized(f)) return -126;
	if (is_special(f)) return 255;
	//storing the bit vector to a pointer
    char *bits_of_numbers = get_bits_float(f);
	int e = 0;
	int pow2;

	int i;
	int j;
	//for-loop that converts from binary (in array form) to decimal (as an int)
	for (i = 8; i > 0; i--){
		pow2 = 1;
		//The following if statement with the for-loop inside is calculate
		//the specific demical value for each 1 on the exp
		if(bits_of_numbers[i] == '1'){
			for(j = 0; j < 8 - i; j++){
				pow2*=2;
			}
			e += pow2;
		}
	}
	free(bits_of_numbers);
	bits_of_numbers = NULL;
	return (e - 127);
}





/*********************************
 * Problem 4 required functions  *
 *********************************/

float get_float_from_bits( char * bits ) {
    
    int s = get_s_from_bits(bits);
    float M = get_M_from_bits(bits);
    int E;
    if (get_type_from_bits(bits) == NORM){
    	M = M + 1.0;
    	E = get_E_from_bits(bits) - 127;
    } else {
    	E = -126;
    }	
    return (pow(-1, s) * M * pow(2, E));
}

/***********/ 

type get_type_from_bits( char * bits ) {
    
    int i;
	int num_of_zeros = 0;
	for (i = 1; i < 9; i++){
		//counting the number of zeros in exp field
		if (bits[i] == '0') num_of_zeros++;
	}
	if (num_of_zeros == 8) return DENORM;
	// num_of_zeros = 0 means its all ones
	if (num_of_zeros == 0) return SPECIAL;
	//0 < num of zeros < 8
	return NORM;
}

/***********/ 

int get_s_from_bits ( char * bits ){
        
    if (bits[0] == '1') return 1;
    return 0;
}

/***********/ 

int get_E_from_bits ( char * bits ) {
    if (get_type_from_bits(bits) == SPECIAL) return 255;
       
    int e = 0;
	int pow2;

	int i;
	int j;
	//for-loop that converts from binary (in array form) to decimal (as an int)
	for (i = 8; i > 0; i--){
		pow2 = 1;
		//The following if statement with the for-loop inside is calculate
		//the specific demical value for each 1 on the exp
		if(bits[i] == '1'){
			for(j = 0; j < 8 - i; j++){
				pow2*=2;
			}
			e += pow2;
		}
	}
	return e;
}

/***********/ 

float get_M_from_bits ( char * bits ) {
    if (get_type_from_bits(bits) == SPECIAL){
    	int i;
    	for(i = 9; i < 32; i++){
    		if (bits[i] == '1'){
    			if (bits[1] == '1') return -NAN;
    			return NAN;
    		}
    	}
    	if (bits[i] == '1') return -INFINITY;
    	return INFINITY;
    }
    float M = 0;
	float pow2;

	int i;
	int j;
	//for-loop that converts from binary (in array form) to decimal fraction
	for (i = 9; i < 32; i++){
		pow2 = 1;
		//The following if statement with the for-loop inside is calculate
		//the specific demical value for each 1 on the exp
		if(bits[i] == '1'){
			for(j = 0; j < i - 8; j++){
				pow2/=2;
			}
			M += pow2;
		}
	}
    return M;
}




/********************************************************************
 * Problem 3 and 4 additional functions  
 ********************************************************************
 * 
 * Specify an additional function declarations in this section.
 ********************************************************************/


  











/********************************************************************
 * Other functions   
 ********************************************************************
 *
 * You do not have to use the following functions in your own code, 
 * but do not remove them from this file. 
 ********************************************************************/


char* get_bits_int ( int n ) {
	//allocate memory to store the string 
	int num_of_bits =  sizeof(int) * 8;  //*8 since there are 8 bits per byte 
	char * bits_of_numbers = (char*) malloc( num_of_bits + 1);
	
	short bit ; 
	
	int i;
	//convert value of n to bits 
	for ( i = 0; i < num_of_bits; i++ ) {
		bit = n & 1; //grab the last bit
		bits_of_numbers[num_of_bits-i-1] = '0' + bit;
		n = n>>1;    //remove the last bit
	}
	
	bits_of_numbers[num_of_bits] = '\0'; //end with a null character
	return bits_of_numbers; 
}

/***********/ 

char* get_bits_float ( float f ) {
	//allocate memory to store the string
	int num_of_bits =  sizeof(float) * 8;  //*8 since there are 8 bits per byte 
	char * bits_of_numbers = (char*) malloc( num_of_bits + 1);
	
	//interpret the bits as int (this is not equivalent to casting to int) 
	int  p = *((int*) (&f) );
	short bit ; 
	
	int i;
	//convert value of n to bits 
	for ( i = 0; i < sizeof(float)*8; i++ ) {
		bit = p & 1;  //grab the last bit
		bits_of_numbers[num_of_bits-i-1] = '0' + bit;
		p = p>>1;    //remove the last bit
	}
	
	bits_of_numbers[num_of_bits] = '\0'; //end with a null character
	return bits_of_numbers; 
	
}


/***********/ 

int  assert_equals_int(int a, int b){
	if (((unsigned)(a) ^ (unsigned)(b)) == 0 ){
		return 1; 
	}
	else{
		return 0; 
	}
}

/***********/ 

int assert_equals_float(float a, float b){
    unsigned * pa = (unsigned *)(&a);
    unsigned * pb = (unsigned *) (&b);
    if ( ( (*pa) ^ (*pb) ) == 0 ){
		return 1; 
	}
	else{
		return 0; 
	}
}
 
/***********/ 

int assert_equals_string(char* a, char * b){
	return ! strcmp(a,b);
}

/***********/ 














    





    

    






      



    
    
