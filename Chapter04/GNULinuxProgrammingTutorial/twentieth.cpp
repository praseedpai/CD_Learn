/////////////////////////////////
//twentieth.cpp
// This Program demonstrates Recursive Directory Traversal
// g++ -o Directory.exe twentieth.cpp
// ./Directory.exe 
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>


// A Recursive Directory Traversal Routine
//
void TraverseDirectory( char *DirName , int level ){
  DIR *dir = 0;
  struct stat status;
  struct dirent *direntry;
  //---------------- open the directory
  if (( dir = opendir(DirName) ) == 0 ) {
    fprintf(stdout,"Failed to Get into %s\n",
      DirName);
    return;
  }
  //---------- change the directory 
  chdir(DirName);
  //------------ Try to read the contents of the 
  // current directory
  while ( ( direntry = readdir(dir) ) != 0 )
  {
    lstat(direntry->d_name,&status);

    if ( S_ISDIR( status.st_mode ) )
    {
      if ( direntry->d_name[0] == '.')
        continue;
      fprintf(stdout,"%*s%s/\n",level ,"", 
      direntry->d_name );

      //---------- Recurse to Process the Sub directory
      TraverseDirectory(direntry->d_name,level + 4 );
    } 
  
    else {
      fprintf(stdout,"%*s%s/\n",level , 
      "",direntry->d_name ); 

    }

  }
  //------------ move to the previous directory
  chdir("..");
  //------------ close the directory 
  closedir(dir);
  return; 
}
//-------------------entry point
int main( int argc , char **argv ){
  char directory_buffer[8192];
  strcpy(directory_buffer,"/usr/lib/"); 
  TraverseDirectory(directory_buffer,0);
} 
//EOF: twentieth.cpp