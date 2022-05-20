////////////////////////////
//seventeenth.cpp
// A Simple Program to Demonstrate Forking of a new process....
// g++ -o forktest.exe seventeenth.cpp
// ./forktest.exe
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
int main( int argc , char **argv ){
  //------------ Every Process has a Process id
  printf("PARENT Process ID = %d\n",getpid() );
  int child_pd;
  // Here we make the fork system call to create a child process
  if (  ( child_pd = fork() )  == 0 ) {

    //---------- We check the return value of Fork call
    //---------  if it is zero , this part is child process
    printf("CHILD Process ID = %d\n",getpid() );
    exit(0);
  }
  // continue with the parent process
  // sleep for 3 seconds 
  sleep(3);
  printf("PARENT Process ID = %d\n",getpid() );
}
//EOF:seventeenth.cpp