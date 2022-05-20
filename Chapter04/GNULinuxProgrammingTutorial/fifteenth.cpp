// fifteenth.cpp
// Program To Demonstrate Binary I/O using C run time library function
// fopen/fread/fwrite/fclose family of functions
// g++ -o mycp fifteenth.cpp
//
//  ./mycp fifteenth.cpp mycp.tmp
//
#include <stdio.h>
int main( int argc , char **argv ){
   if ( argc != 3 ) {
         fprintf( stdout,"usage: mycp <srcfile> <destfile> \n");  
         return -1;
   }
   FILE *inp , *outp;
   inp = outp = 0;
   if ( ( inp = fopen(argv[1],"rb") ) == 0 ){
         fprintf(stdout,"Failed to Open src file\n");
         return -2;
   }
   if ( ( outp = fopen(argv[2],"wb") ) == 0 ){
         fclose(inp);
         fprintf(stdout,"Failed to Open desitnation file\n");
         return -2;
   }
   char bfr[8192];
   int num = -1;
   while ( ( num  = fread(bfr,1,8192,inp) ) == 8192 ){
        fwrite(bfr,1,8192,outp);
   }
   if ( num > 0 )
     fwrite(bfr,1,num,outp); // write the remaining bytes
   fclose(inp);
   fclose(outp);
}
//EOF: fifteenth.cpp

