/////////////////////////////////
//twentyfirst.cpp
// This Program demonstrates Recursive Directory Traversal
// g++ -o Directory2.exe twnetyfirst.cpp
// ./Directory2.exe 


#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

//////////////////////
//
// This Routine does not change directories to traverse the
// directory for it's entries.
//

void TraverseDirectory( char *DirName , int level )
{
  DIR *dir = 0;
  struct stat status;
  struct dirent *direntry;
  char TempDir[8192]; 

  strcpy(TempDir,DirName);
  if (( dir = opendir(TempDir) ) == 0 ) {
    fprintf(stdout,"Failed to Get into %s\n",DirName);
    return;
  }

  while ( ( direntry = readdir(dir) ) != 0 )
  {
    //------------- Copy the Directory name to Temp Dir
    //------------- Add the entry (can be directory or file )
    strcpy(TempDir,DirName);
    strcat(TempDir,direntry->d_name);

    //--------- We need to give the fully qualified
    //--------- path name to retrieve the status
    lstat(TempDir,&status);


    if ( S_ISDIR( status.st_mode ) )
    {
      if ( direntry->d_name[0] == '.')
        continue;
      fprintf(stdout,"%*s%s/\n",level ,
      "", direntry->d_name );
      //--------- TempDir , contains fully qualified file name
      TraverseDirectory(TempDir,level + 4 );
    } 

    else {
      fprintf(stdout,"%*s%s/\n",level , 
        "",direntry->d_name ); 

    } 
  } 
  closedir(dir);
  return; 
}
/////////////////////////////////
//
// This Program demonstrates Recursive Directory
// Traversal
//
// g++ -o Directory2.exe Directory2.cpp
// ./Directory2.exe 
//
//
//

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

//////////////////////
//
// This Routine does not change directories to traverse the
// directory for it's entries.
//

void TraverseDirectory( char *DirName , int level )
{
  DIR *dir = 0;
  struct stat status;
  struct dirent *direntry;
  char TempDir[8192]; 

  strcpy(TempDir,DirName);
  if (( dir = opendir(TempDir) ) == 0 ) {
    fprintf(stdout,"Failed to Get into %s\n",DirName);
    return;
  }

  while ( ( direntry = readdir(dir) ) != 0 )
  {
    //------------- Copy the Directory name to Temp Dir
    //------------- Add the entry (can be directory or file )
    strcpy(TempDir,DirName);
    strcat(TempDir,direntry->d_name);

    //--------- We need to give the fully qualified
    //--------- path name to retrieve the status
    lstat(TempDir,&status);


    if ( S_ISDIR( status.st_mode ) )
    {
      if ( direntry->d_name[0] == '.')
        continue;
      fprintf(stdout,"%*s%s/\n",level ,
      "", direntry->d_name );
      //--------- TempDir , contains fully qualified file name
      TraverseDirectory(TempDir,level + 4 );
    } 

    else {
      fprintf(stdout,"%*s%s/\n",level , 
        "",direntry->d_name ); 

    } 
  } 
  closedir(dir);
  return; 
}



int main( int argc , char **argv )
{
  char directory_buffer[8192];
  strcpy(directory_buffer,"/usr/lib/"); 
  TraverseDirectory(directory_buffer,0);

} 

