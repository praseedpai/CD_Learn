/////////////////////
// twentythird.cpp
// A Program to demonstrate Memory Mapped files
// g++ -o mmaptest.exe twentythird
//
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

//////////////////////////////
//
// This Function Writes values to a binary file.
// This function will write values from 0-19 
// Total file size will be 80 bytes 
// 20*sizeof(int)
// 
void PopulateValues()
{
   unlink("TEST.tmp");  
   int fd = open("TEST.tmp",O_RDWR | O_CREAT );

   if ( fd == -1 )
    {
       fprintf(stdout,"P9:Failed to open TEST.bin %d\n",fd);
       exit(0); 
    }    

    int val;

    for( val = 0; val < 20; ++val )
       write(fd,&val,4 );

   close(fd);   
}

//////////////////////////////
//
//
//
int main()
{
   PopulateValues();

   int fd;
   if ( ( fd = open("TEST.tmp",O_RDWR) ) == -1 )
   {
        fprintf(stdout,"Failed to open TEST.tmp %d\n",fd);
        exit(-1); 
   }

   ////////////////////////////////////////////
   //  Map the entire contents of a file to a pointer...
   //
   int *mapped_values = (int *)
              mmap(0,
                   20*sizeof(int),
                   PROT_READ | PROT_WRITE,
                   MAP_SHARED,fd,0 );

  /////////////////////////////////////////////
  //
  //  Now we can treat the whole file as an array of integer
  //  
  int val;
  for(val=0; val<20; ++val )
         mapped_values[val] *= 2; // double the value...

  msync((void *)mapped_values,20*sizeof(int),MS_ASYNC);
  munmap((void *)mapped_values,20*sizeof(int));
  
  //////////////////////////////////////////////////////
  // Now reset the file pointer and dump the values...
  //
  lseek(fd,0,0);

  for( int i=0; i<20; ++i )
  {
      read(fd,&val,4);
      printf("%d\n",val); 
  }  
  close(fd);
  unlink("TEST.tmp");  
}
//EOF: twentythird.cpp