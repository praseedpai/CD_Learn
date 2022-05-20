//fourth.cpp
// g++ -c -ofourth.o fourth.cpp 
// g++ -ofourth.exe fourth.o fourth_a.cpp
//----------------------------------
////home/praseed/gnu_linux$ g++ -o fourth.exe fourth.o fourth_a.cpp
////home/praseed/gnu_linux$ ./fourth.exe
//The absolute value of -1 is 1
////home/praseed/gnu_linux$ g++ -c -o fourth_a.o fourth_a.cpp
////home/praseed/gnu_linux$ g++ -o fourth.exe fourth.o fourth_a.o
////home/praseed/gnu_linux$ ./fourth.exe
//The absolute value of -1 is 1
#include <stdio.h>

long myabs(long a );   // implementation in fourth_a.cpp

int main( int argc , char **argv ){
  printf("The absolute value of %d is %ld\n",-1,myabs(-1));
}

// EOF fourth.cpp