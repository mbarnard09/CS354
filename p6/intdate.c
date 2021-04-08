///////////////////////////////////////////////////////////////////////////////
//Name: Mathew Barnard
//Class: Cs354
//email: mbarnard3@wisc.edu
//cs login: mbarnard
//
//main file: intdate.c
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

//Since both main() and the alarm handler need to know/use the number of seconds//in order to arm the alarm, make this value a global variable.
int globalTime = 3;
int globalCount = 0;



/*signal handling function that prints time message
*/
void signalHandler() {
    //time data type
    time_t now;
    time(&now);
    int pid = getpid();
    //print as demonstrated in the example
    printf("PID: %d", pid);
    printf(" | Current Time: %s", ctime(&now));
    if(alarm(globalTime) != 0) {
        printf("trigger error\n");
	exit(1);
    }
}
//prints message when caught and increments global count
//
void usr1Handler() {
    printf("SIGUSR1 caught!\n");
    globalCount++;

}

//sigint handler to print message and count
void sigintHandler() {
    printf("\nSIGINT received.\n");
    printf("SIGUSR1 was received %d times. Exiting now.\n", globalCount);
    exit(0);

}





//main
int main() {
    //First, it sets up an alarm that will go off 3 seconds later, causing a SIG    //ALRM signal to be sent to the program.
    printf("Pid and time will be printed every 3 seconds.\n");
    printf("Enter ^C to end the program.\n");
    
    //given initialization
    struct sigaction act;
    memset(&act, 0, sizeof(act)); 
    
    //sa_handler comes from sigaction struct
    act.sa_handler = signalHandler;
    
    //alarm trigger and error check
    if(alarm(globalTime) != 0) {
	printf("trigger error\n");
	exit(1);
    }
    
    //sig alarm
    if(sigaction(SIGALRM, &act, NULL) != 0) {
        printf("sigaction error");
        exit(1);
    }
    
    //usr1 signal initialization
    struct sigaction usr1;
    memset (&usr1, 0, sizeof(usr1));
    
    //sa_handler comes from sigaction struct
    usr1.sa_handler = usr1Handler;

    //sig usr1
    if(sigaction(SIGUSR1, &usr1, NULL) != 0) {
        printf("siguser1 error");
	exit(0);
    }

    //third signal handler
    struct sigaction sigint; 
    memset (&sigint, 0, sizeof(sigint));

    //sa_handler comes from sigaction struct
    sigint.sa_handler = sigintHandler;
     
    //sa_handler comes from sigaction struct
    if(sigaction(SIGINT, &sigint, NULL) != 0) {
        printf("sigint error");
	exit(0);
    }
    


    //given while loop
    while (1){
        //infinite
    }

    return(0);
}
