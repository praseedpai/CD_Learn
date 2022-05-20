//  twentysixth.cpp
// A Simple POSIX thread program
// g++ -o thread_first.exe twentysixth.cpp -lpthread
// ./thread_first.exe
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
// Thread Entry Point
void *PrintFunction( void *temp ) {
     printf("Hello World from Worker Thread\n"); 
     return 0;
}
// User Entry Point for the Application
int main( int argc , char **argv ){
        //  Thread Handle
        pthread_t th;
        // -------------- Create a Thread and start the execution
        int re_val = pthread_create( &th, NULL, PrintFunction, 0);
        printf("Hello World from the main Thread\n"); 
        // ----------------- Wait for Worker thread to finish
        pthread_join( th, NULL);
        return 0; 
}