///////////////////////////////////////////////////////////////////////////////
//Name: Mathew Barnard
//Class: Cs354
//email: mbarnard3@wisc.edu
//cs login: mbarnard
//
//main file: intdate.c
//this file: sendsig
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





//int main
//accepts 2 command line arguments
int main (int argc, char* argv[]) {
    //making sure the number of command line arguments including file is 3
    if (argc != 3) {
        printf("Usage: <signal type> <pid>\n");
        exit(1);
    }
    //if command line ar is u we send a sigusr1
    if(strcmp(argv[1], "-u") == 0) {
        kill(atoi(argv[2]), SIGUSR1);
    
    }else if(strcmp(argv[1], "-i") == 0) {
        kill(atoi(argv[2]), SIGINT);
    //error checking
    }else {
        printf("Error");
	exit(1);
    }

    return(0);
}
