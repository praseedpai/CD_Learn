// sixth_a.cpp
// g++ -fpic sixtha_a.cpp -shared -o libSixtha.so
#include <stdio.h>

extern "C" int Add( int x , int y ) { return x + y;}

// Eof sixth_a.cpp
