////////////////////////////
//eighteenth.cpp
// A Demonstrate Forking of a new process....
// The Program waits for the status of the child process to continue
// g++ -o forktest2.exe eighteenth.cpp
// ./forktest2.exe
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
int main( int argc , char **argv ){
  //------------ Every Process has a Process id
  printf("PARENT Process ID = %d\n",getpid() );
  int child_pd;
  int ps_status;
  // Here we make the fork system call to create a child process
  if (  ( child_pd = fork() )  == 0 ) {
    //---------- We check the return value of Fork call
    //---------  if it is zero , this part is child process
    printf("CHILD Process ID = %d\n",getpid() );
    exit(3);
  }
  // continue with the parent process
  // if the waitpid call succeded , we will get the 
  // child process id as return value
  if ( waitpid(child_pd,&ps_status,0) != child_pd ){
    // if there is no error , we should not reach here
    printf("Error In execution of Child Process\n");
  }
  if ( WIFEXITED(ps_status) ) {
    printf("The child process terminated properly with status %d\n",
    WEXITSTATUS(ps_status));
  }
  printf("PARENT Process ID = %d\n",getpid() );
}
//EOF: eighteenth.cpp
