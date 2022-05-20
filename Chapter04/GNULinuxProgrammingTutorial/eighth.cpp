// eighth.cpp
// g++ -oeighth.exe eighth.cpp 
// ./eighth.exe < eighth.cpp > eight.dup
// cat eight.dup
#include <stdio.h>
#include <ctype.h>
int main(){
 int c;
 while ( ( c = getchar() ) != EOF )
           putchar(c);
 return 0;
}