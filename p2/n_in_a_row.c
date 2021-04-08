////////////////////////////////////////////////////////////////////////////////
// Main File:        N_in_a_row
// This File:        n_in_a_row
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Spring 2020
//
// Author:           Mathew barnard
// Email:            Mbarnard3@wisc.edu
// CS Login:         mbarnard
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None
//                   
//
// Online sources:   None
//                   
//                   
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *COMMA = ",";  
     
/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size) {      
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1) {
        printf("Error in reading the file.\n");
        exit(1);
    }

    char *token = NULL;
    token = strtok(line, COMMA);
    *size = atoi(token);
}       
 
   
  
/* TODO:
 * Returns 1 if and only if the board is in a valid state.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * size: number of rows and columns
 */
int n_in_a_row(int **board, int size) {
 	
    //declaring local variables
    int numX = 0;
    int numO = 0;
    int numB = 0;
    //Case where board size is even returns invalid
    if(size % 2 == 0){
       	return 0; 
    }
    
    //Case where number of O's is greater than number of X's-invalid
    for(int i=0; i<size; i++) {
	for(int j=0; j<size; j++) {
	    if((*(*(board + i) + j)) == 2) {
	        numO++;
	    }
	    else if((*(*(board + i) + j)) == 1) {
 	        numX++;    
	    }
	    else {
	        numB++;
	    }
	}

    }
    
    //case where number of o's is greater than x's-invalid
    if(numO > numX) {
        return 0;
    }

    //case where number of x's is two greater than o's
    if(numX > numO + 1) {
        return 0;
    }
    //Number of wins for o and x
    int oWin = 0;
    int xWin= 0;
    //Counting winners vertically
    int xcounter = 0;
    int ocounter = 0;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if((*(*(board + j) + i)) == 1) {
	        xcounter++;
	    }
	    else if((*(*(board + j) + i)) == 2){
		ocounter++; 
            }
	   
	}
	
	//xWin gets added if either of the coloumns
	//are made up of number of x equal to size
	if(xcounter == size) {
	    xWin++;
	}
	//owin gets added if number of os are
	//equal to size
	if(ocounter == size) {
	    oWin++;
	}
	//reseting counters in prep for new column
	xcounter = 0;
	ocounter = 0;
    }
    
    //counting winners horizontally
    xcounter = 0;
    ocounter= 0;
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
	    if((*(*(board + i) + j)) == 1) {
	        xcounter++;
	    }
	    else if((*(*(board + i) + j)) == 2){
	        ocounter++;
	    }
	}
	
        if(xcounter == size) {
	    xWin++;
	}
	if(ocounter == size) {
	    oWin++;
	}
	//reseting counters in prep for new row
	xcounter = 0;
	ocounter = 0;
    }
    
    
    //left right diagnol wins
    for(int i=0; i<size; i++) {
    	if((*(*(board + i) + i)) == 1){
	    xcounter++;	
        }
	if((*(*(board + i) + i)) == 2){
	    ocounter++;
	}
	
    }
    if(xcounter == size) {
        xWin++;
    }
    if(ocounter == size) {
        oWin++;
    }
    

    //Right to left diag winner
    xcounter = 0;
    ocounter = 0;
    for(int i= 0; i<size; i++) {
        for(int j=0; j<size; j++) {
	    if((i+j) == (size-1)) {        
		if((*(*(board + j) + i)) == 1){
	            xcounter++;
		}  
		else if((*(*(board + j) + i)) == 2){
	            ocounter++;
	        }

	
	    }
	}
    }
    //adding number of wins for each mark
    if(xcounter == size) {
        xWin++;
    }
    if(ocounter == size) {
        oWin++;
    }
    
    //case where x and o both win
    if(xWin > 0 && oWin > 0) {
        return 0;
    }
    //case where x or o has more than one winner
    if(xWin > 1 || oWin > 1) {
        return 0;
    }
    else{
        return 1;
    }	
}    
  
 
   
/* PARTIALLY COMPLETED:
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {              
     
    //Checks if number of command-line arguments is correct.
    if (argc != 2) {
	printf("Error: Incorrect number of arguments\n ");
   	exit(1);
    }
    		    
    //Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    //Declare local variables.
    int size;	 
    //TODO: Call get_dimensions to retrieve the board size.
    get_dimensions(fp , &size);
    	
    //TODO: Dynamically allocate a 2D array of dimensions retrieved above.
    int **board;
    board =(int**)malloc(sizeof(int*)*size);

    for(int i=0; i<size; i++) {
	*(board + i) =(int*)malloc(sizeof(int)*size);
    }


    
    //Read the file line by line.
    //Tokenize each line wrt comma to store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading the file.\n");
            exit(1);
        }

        token = strtok(line, COMMA);
        for (int j = 0; j < size; j++) {
            //TODO: Complete the line of code below
            //to initialize your 2D array.
            *(*(board + i) + j) = atoi(token);
            token = strtok(NULL, COMMA);
        }
    }
    
    

    //TODO: Call the function n_in_a_row and print the appropriate
    //output depending on the function's return value.
    char v[] = "valid";
    char iv[] = "invalid";
    
    if(n_in_a_row(board, size) == 1){
	printf("%s\n", v);
    }else {
	printf("%s\n", iv);
    }

    //TODO: Free all dynamically allocated memory.
    free(board);
    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    } 
     
    return 0;       
}       
