// ninth.cpp
// g++ -oninth.exe ninth.cpp 
// ./ninth.exe < ninth.cpp > ninth.dup
// cat eight.dup
#include <stdio.h>
#include <ctype.h>
int main(){
 int c;
 while ( ( c = getchar() ) != EOF )
           putchar(toupper(c));
 return 0;
}