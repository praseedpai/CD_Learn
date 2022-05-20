//
// fifth_a.cpp
// -fpic => pic stands for position independent code
// g++ -fpic fifth_a.cpp -shared -o libFiftha.so
#include <stdio.h>

extern "C" int Add( int x , int y ) { return x + y;}
