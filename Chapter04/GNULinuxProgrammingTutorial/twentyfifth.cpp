/////////////////////////////////////////
//twentyfifth.cpp
// Program to demonstrate Named Pipes
// g++ -o np_server.exe twentyfifth.cpp
// ./np_server.exe  &  ( Run in the back ground )
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
//-------------- Entrypoint
int main( int argc , char ** ){
   //-------------- if named pipe does not exist
   //-------------- create one  
   if ( access("named_pipe@786",F_OK ) == -1 ){
      int stat =  mkfifo("named_pipe@786",0777);

      if ( stat != 0 )
      {
          fprintf(stdout,"Failed to create named pipe\n");
          exit(-1);
      }

   } 

  //----------- open the fifo queue in read only mode ...
  int pipe_handle = open("named_pipe@786",O_RDONLY  );

  if ( pipe_handle == -1 )
  {
       fprintf(stdout,"Failed to open the named pipe\n");
       exit(-2);
  } 

  int num_read; 
  char buffer[128];
  memset(buffer,0,128);

  while (( num_read = read( pipe_handle,buffer,127)) != -1 )
  {
         //------ nothing has been read from the client
         if ( num_read == 0 ) {
              sleep(5);
         }
       
     

         if ( strcmp(buffer,"QUIT\n") == 0 )
                 exit(0);

         if ( buffer[0] == 0 ) 
                continue;
         printf("%s \n",buffer);
         memset(buffer,0,128);    
  }

  close(pipe_handle);

} 
//twentyfifth.cpp