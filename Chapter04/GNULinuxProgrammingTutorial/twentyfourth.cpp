/////////////////////////////////////
// twentyfourth.cpp
// POSIX Signaling API demo
// g++ twentyfourth.cpp
// ./a.out
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
// CTRL-C handler
//
void SigIntHandler( int sig , siginfo_t *siginfo , void *ign ){
        printf("Pressed CTRL-C to exit \n");
        exit(0);
}
//---- Entry Point
int main(){
   struct sigaction action;
   memset(&action,0,sizeof(action));
   action.sa_flags = SA_SIGINFO;
   action.sa_sigaction = SigIntHandler;
   sigaction(SIGINT,&action,0);
   while ( 1 )
      ;
}