///////////////////////
//first.cpp
//
// A hello world program using GNU C/C++ under Linux
//
// g++ first.cpp => a.out
// if you want to give another name (say test.exe ) for
// the executable
//
// g++ -otest.exe first.cpp
//
// ./test.exe
// test.exe will give you error , to avoid the error
// reset the enviornment variable
//  export PATH=.:$PATH
// test.exe ( will print hello world on to the console )
// Console output
// -------------------
//praseed@LAPTOP-QIG6F4HD://home/praseed/gnu_linux$ g++ -otest.exe first.cpp
//praseed@LAPTOP-QIG6F4HD://home/praseed/gnu_linux$ test.exe
//Hello world
//praseed@LAPTOP-QIG6F4HD://home/praseed/gnu_linux$

#include <stdio.h>
//---- user entry point 
int main( int argc , char **argv ){
  	printf("Hello world \n" );
} 