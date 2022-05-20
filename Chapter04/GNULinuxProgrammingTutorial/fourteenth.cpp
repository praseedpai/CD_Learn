//  fourteenth.cpp
//      Demonstrates C standard I/O which is portable across platforms
//  g++ -o txtfiledump fourteenth.cpp
//  ./txtfiledump fourteenth.cpp
#include <stdio.h>
int main( int argc , char **argv ){
    //----------- the program expects one argument
    //----------- if there are more or less..it is considered as error
    if ( argc != 2 ) {
        fprintf(stdout,"Usage: txtfiledump  &lt;filename> \n");
        return -1;
    }
    //--------- argv[1] contains the first argument
    //----------argv[0] contains the executable file name
    FILE *fp = fopen(argv[1],"rt");
    //--------- Failed to  Open the file
    if ( fp == 0 ){
         fprintf(stdout,"Error Opening File %s\n",argv[1] );
         return -2;
    } 
    char bfr[4096];
    //----------- While not the end of file
    //----------- take one line at a time and spit
    while ( !feof(fp) ){
        fgets(bfr,4096,fp);
        fprintf(stdout,"%s",bfr);
    }
    //--------- close the file ...
    fclose(fp);
}
// EOF fourteenth.cpp

