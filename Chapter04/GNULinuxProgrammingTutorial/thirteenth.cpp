// thirteenth.cpp
// g++ -o psp.exe thirteenth.cpp
// ./psp.exe
#include <stdio.h>
#include <unistd.h>
int main( int argc , char **argv ){
  FILE *fp = 0;
  //---------- open a pipe for writing
  if ( ( fp = popen("sort","w")) == 0 ) { return -1; }
  //------------ write to the pipe
  fprintf(fp,"Ziyad\n");
  fprintf(fp,"Anand\n");
  fprintf(fp,"Arjun\n");
  fprintf(fp,"Ram\n");
  fprintf(fp,"Hooper\n");
  pclose(fp);  // when you close the pipe sorting will happen..
  return 0;
}

// EOF thirteenth.cpp