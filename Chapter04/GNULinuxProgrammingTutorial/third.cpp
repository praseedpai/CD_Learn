///////////////////////////////////
// third.cpp
// A C/C++ program to spit the environmental variables
// 
// g++ -oenvspitter.exe third.cpp 
// ./envspitter.exe

#include <stdio.h>

int  main( int argc , char **argv , char **envp ){
  //  env1\0\0env2\0\0env3\0\0\0\0
  char **temp = envp;
  while (*(temp+1) != 0 ) {
           puts(*temp);
           temp++;
   }
   return 0;
}