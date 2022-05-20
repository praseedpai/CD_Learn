// sixteenth.cpp
// A program to copy file to another using Linux System Calls
// These are conveniently packaged as C called routine by glibc
// g++ -o sysfile sixteenth.cpp
// ./sysfile sixteenth.cpp sysfile.out
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main( int argc , char **argv ){
  if ( argc != 3 ) {
    fprintf( stdout,"usage: sysfile <srcfile> <destfile> \n");
    return -1;
  }
  int inp_fd; // input file descriptor
  int out_fd; // output file descriptor
  // use Linux System calls to open file... 
  // O_RDONLY => Read only access
  if ( ( inp_fd = open(argv[1],O_RDONLY) ) == -1 ){
    fprintf(stdout,"Failed to Open src file\n");
    return -2;
  }
  // This file should not exist when the call is made
  if ( ( out_fd = open(argv[2],O_WRONLY | O_CREAT | O_EXCL) ) == -1 ){
    close(inp_fd);
    fprintf(stdout,"Failed to Open desitnation file\n");
    return -2;
  }
  char bfr[8192];
  int num = -1;
  while ( ( num = read(inp_fd,bfr,8192) ) == 8192 ){
    write(out_fd,bfr,8192);
  }
  if ( num > 0 )
    write(out_fd,bfr,num); // write the remaining bytes
  close(inp_fd);
  close(out_fd);
}
//EOF: Sixteenth.cpp