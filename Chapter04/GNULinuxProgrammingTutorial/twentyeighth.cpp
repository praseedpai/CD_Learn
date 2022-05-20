// twentyeighth.cpp
// A Simple POSIX thread program to demonstrate
// mutex for guarding modification to shared variables. 
// g++ -o thread_third.exe thread_third.cpp -lpthread
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
// some global variables;
int Counter=0;
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
// Thread Entry Point
void *PrintFunction( void *temp ){
     pthread_mutex_lock( &m1 ); //guard area
     Counter++; // we can safely modify variable now
     pthread_mutex_unlock(&m1); //remove guard
     int s = *((int *)temp)  ;
     printf("Hello World from Worker Thread %d\n",s); 
     return 0;
}
// User Entry Point for the Application
int main( int argc , char **argv ){
  //  Thread Handle
  pthread_t th;
  pthread_t th1; 
  // Create two Threads and start the execution
  int param = 100;
  int re_val = pthread_create( &th, NULL, PrintFunction,
  (void *)&param  // Thread parameter 
  );
  int param1=200;
  int re_val1 = pthread_create( &th1, NULL, PrintFunction,
  (void *)&param1  // Thread parameter 
  );
  printf("Hello World from the main Thread\n"); 
  // Wait for Worker threads to finish
  pthread_join( th, NULL);
  pthread_join(th1,NULL);
  return 0; 
}
//EOF:twentyeighth.cpp