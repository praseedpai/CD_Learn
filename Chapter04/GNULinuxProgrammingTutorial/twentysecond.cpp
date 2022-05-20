///////////////////
//twentysecond.cpp
// Press CTRL-C three times to terminate this program
// g++ -o Signal.exe twentysecond.cpp
// ./Signal.exe
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
void interrupt_handler( int cause ){
  static int test = 0;
  test++;
  #if 0 // make this 1 to compile #if part
    if ( test == 3 )
      exit(0);
    else
      printf("Press CTRL-C %d times\n", 
        3-test );
  #else

    if ( test == 2 ) {
      //--------- Reset to the defualt behaviour
      signal(SIGINT,SIG_DFL);
    }
    else
      printf("Press CTRL-C %d times\n", 3-test );
  #endif

}


int main( int argc , char **argv )
{
  signal( SIGINT , interrupt_handler);
  while (1)
  {
    //----------- an infinite loop to demonstrate signal
    //------------ handling
  }
  return 0;
} 
//EOF:twentysecond.cpp