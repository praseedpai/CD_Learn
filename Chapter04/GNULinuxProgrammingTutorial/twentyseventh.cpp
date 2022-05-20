/////////////////////////////////////////
// twentyseventh.cpp
// A Simple POSIX thread program to demonstrate
// passing of parameters to the thread entry point
// g++ -o thread_second.exe twentyseventh.cpp -lpthread
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
// Thread Entry Point
void *PrintFunction( void *temp ){
     int s = *((int *)temp)  ;
     printf("Hello World from Worker Thread %d\n",s); 
     return 0;
}
// User Entry Point for the Application
int main( int argc , char **argv ){
  //  Thread Handle
  pthread_t th;
  // Create a Thread and start the execution
  int param = 100;
  int re_val = pthread_create( &th, NULL, PrintFunction,
      (void *)&param  // Thread parameter 
   );
   printf("Hello World from the main Thread\n"); 
  // Wait for Worker thread to finish
  pthread_join( th, NULL);
  return 0; 
}
//EOF:twentyseventh.cpp