//fifth.cpp
// g++ -c -o fifth.o fifth.cpp (will produce fifth.o )
// g++ -ofifth.exe fifth.o ./libFiftha.so
#include <stdio.h>

// ------------- The Add function will be packaged in
// a shared library (.so ) by the name "libFiftha.so"

extern "C" int Add( int x , int y );

int main(){
  int r = Add(3,4);
  printf("%d\n",r);
  return 0;
}
