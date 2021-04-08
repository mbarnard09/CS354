////////////////////////////////////////////////////////////////////////////////
// Main File:        makeMagic.c
// This File:        makeMagic.c
// Other Files:      none
// Semester:         CS 354 Spring 2020
//
// Author:           Mathew
// Email:            mbarnard3@wisc.edu
// CS Login:         mbarnard
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None
//                   
//
// Online sources:   StackOverflow- Scanner help
//                   
//                   
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
    int size;     // dimension of the square
    int **msquare; // pointer to heap allocated magic square
} MSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the required
 * error message and exit), and returns the valid number.
 */
int getSize() {
    //variable to store user int
    int size;
    
    //user input
    printf("Enter magic square's size (odd integer >=3)\n");
    scanf("%d", &size);
    
    //check if user input is correct
    if(size % 2 == 0) {
        printf("Size must be odd.\n");
	exit(1);		
    }
    else if(size < 3) {
    	printf("Size must be >= 3.\n");
	exit(1);
    }
    else {
	return size;
    }	
   
} 
   
/* TODO:
 * Makes a magic square of size n using the Siamese algorithm
 * and returns a pointer to the completed MSquare struct.
 *
 * n the number of rosw and columns
 */
MSquare *generateMSquare(int n) {
    //setting up data for struct
    MSquare *s;
    s = (MSquare*)malloc(sizeof(MSquare));
    s->size = n;
    //memory allocation error handling
    if(s == NULL) {
        printf("memory not allocated\n");
	exit(1);
    }

    s->msquare  = (int**)malloc(sizeof(int*) * s->size);
    for(int i = 0; i < s->size; i++) {
        *(s->msquare + i) = (int*)malloc(sizeof(int)*s->size);
    }
    //intializing all elements to zero
    for(int i = 0; i < s->size; i++){
        for(int j = 0; j< s->size; j++) {
	    *(*(s->msquare + i) + j) = 0;
	}
    }
    //starting position will be the far colomn in the central row
    int i = (s->size/2);
    int j = (s->size-1);
    
   

    //iterate through all numbers to be put in square
    for(int sqNum = 1; sqNum <= (s->size)*(s->size); ) {
        //If the row is above the array and the coloum is to the right of it
	//resets row to 1 and coloumn to size -2
        if(i == -1 && j == (s->size)) {
	    i = 0;
	    j = (s->size)-2;
 	}
	//if only the row is above array or only comlumn is to the right
	//row will be set to size-1 or col will be set to 0
        else {
	    if(i == -1) {
	        i = (s->size-1);
	    }   
	    if(j == s->size) {
	        j = 0;
	    } 
	}
        //If the occupied i j spot already has number coloumn goes left 2 and 
	//row goes up 1 amd loop continues from top 
	if(((*(*(s->msquare + i) + j)) != 0)) {
	    j = j-2;
	    i++;
	    continue;
	}
        else {
	    *(*(s->msquare + i) + j) = sqNum;
	    sqNum++;
	}
        //decrease row increase coloumn... up and to the right	
        i--;
        j++;	
    }
    return s;    
} 

/* TODO:  
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * msquare the magic square to output
 * filename the name of the output file
 */
void outputMSquare(MSquare *msquare, char *filename) {
    //CREATING FILE
    FILE *fptr = fopen(filename, "w");
    //Error handling for open file
    if(fptr == NULL) {
        printf("Error:Empty file\n");
	exit(1);
    }	    
	
    fprintf(fptr, "%d\n", msquare->size);
    for(int i = 0; i< msquare->size; i++) {
        for(int j=0; j< msquare->size; j++) {
            fprintf(fptr,"%d" , *(*(msquare->msquare + i) + j));
            if(j != (msquare->size - 1)) {
	        fprintf(fptr, ",");
	    }
	}
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    //CLose file ERROR CHECK
    if(fclose(fptr) != 0) {
        printf("Error: Close file\n");
	exit(1);
    }
	
}

/* TODO:
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 */
int main(int argc, char *argv[]) {
    // TODO: Check input arguments to get output filename
    if(argc != 2) {
        printf("Usage: ./makeMagic <output_filename>\n");
	exit(1);
    }

    // TODO: Get magin square's size from user
    int size = getSize();

    // TODO: Generate the magic square
    MSquare helper= *generateMSquare(size);
   

    // TODO: Output the magic square
    outputMSquare(&helper,argv[1]);
    
    //FREE
    MSquare *s = generateMSquare(size);
    free(s);
    

    return 0;
} 


   
