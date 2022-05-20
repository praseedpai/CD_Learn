//nineteenth.cpp
// This Program demonstrates simple DirectoryTraversal
// g++ -o SimpleDir.exe nineteenth.cpp
// ./SimpleDir.exe
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
/////////////////////////////////////
//
// Emits the content of Directory ...
//
void DumpDirectory( char *DirName ){
  DIR *dir = 0;
  struct stat status;
  struct dirent *direntry;
  char TempDir[8192];
  if (( dir = opendir(DirName) ) == 0 ) {
    fprintf(stdout,"Failed to Get into %s\n",DirName);
    return;
  }
  //----------------- Read one entry at a Time
  //----------------- Check the status ,
  //------------ if Directory give appropriate message
  while ( ( direntry = readdir(dir) ) != 0 )
  {
    strcpy(TempDir,DirName);
    strcat(TempDir,direntry->d_name);
    lstat(TempDir,&status);
    //----------- Check the Directory Bit
    if ( S_ISDIR( status.st_mode ) ){
      //---------- ignore . , ..
      if ( direntry->d_name[0] == '.')
        continue;
      fprintf(stdout,"Directory @ %s\n",direntry->d_name );
    }
    else {
      fprintf(stdout,"File @ %s\n",direntry->d_name ); 
    }
  }
  //------------- Finished Read the Directory...
  closedir(dir);
  return; 
}
// Driver Program
int main( int argc , char **argv ){
  const char *dirname = "/usr/lib/";
  DumpDirectory((char *)dirname);
}

// Eof nineteenth.cpp 