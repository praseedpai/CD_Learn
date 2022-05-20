// eleventh.cpp
//
//
//g++ -o test.exe eleventh.cpp
//./test.exe
//
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
  FILE *fp=0;
  //--------- open a pipe to the ls command
  //--------- second parameter (r) indicates read
  if ( ( fp = popen("ls -l","r") ) == 0 ) { return -1;}
  char bfr[8192];
  //--------- Read line at a time and spit to the console
  while ( !feof(fp) ){
       fgets(bfr,8192,fp);
       printf("%s",bfr);
  }           
  //-----------close the file
  fclose(fp); 
}
//EOF eleventh.cpp