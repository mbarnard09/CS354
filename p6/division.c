//Class: Cs354
//email: mbarnard3@wisc.edu
//cs login: mbarnard
//
//main file: intdate.c
//this file: division.c
//
///////////////////////////////////////////////////////////////////////////////
///////////////////// Other sources ///////////////////////////////////////////
//
//People: None
//
///////////////////////////////////////////////////////////////////////////////



#include <string.h>
#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>


//global counter variable
int globalCounter;

//this fucntion is handler for control c
void sigintHandler(){
    printf("\nTotal number of operations completed succesfully: %d\n", 
		    globalCounter);
    printf("The program will be terminated.\n");
    exit(0);


}

//this function handles divide by zero signal
void divzeroHandler() {
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %d\n", 
		    globalCounter);
    printf("The program will be terminated.\n");
    exit(0);

}




int main() {
    //Use fgets() to read each line of input (use a buffer of 100 bytes)
    char buffer[100];

    // Implement two independent handlers; do not combine the handlers. Do not p    //lace the calls to sigaction() within the loop! These calls should be compl    //eted before entering the loop that requests and does division on the two 
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = sigintHandler;
    if(sigaction(SIGINT, &act, NULL) != 0) {
        printf("sigint error");
	exit(0);
    }


    struct sigaction divZero;
    memset(&divZero, 0, sizeof(divZero));
    divZero.sa_handler = divzeroHandler;
    if(sigaction(SIGFPE, &divZero, NULL) != 0) {
        printf("sigfpe error");
	exit(0);
    
    }


    //while loop varibales
    int firstN;
    int secondN;
    int soln;
    int remain;

    //infinite while
    while(1) {
        printf("Enter first integer: ");
	fgets(buffer, 100, stdin);
        firstN = atoi(buffer);
	
	printf("Enter second integer: ");
	fgets(buffer, 100, stdin);
	secondN = atoi(buffer);
	
	soln = firstN/secondN;
	globalCounter++;
	remain= firstN%secondN;
	printf("%d / %d is %d with a remainder of %d\n", firstN, secondN, soln,
			remain);
    
    }
    return(0);

}
