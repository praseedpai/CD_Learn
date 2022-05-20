// sixth.cpp
//
// g++ -o test.exe sixth.cpp -ldl
#include <stdio.h>
#include <dlfcn.h>   // necessary for dynamic loading of shared libraries

//--- typedef for a function pointer which represent int Add(int , int )
typedef int (*BinaryFunction)( int x , int y );
//--------------- user entry point
int main(){

    void * lib  = dlopen("./libSixtha.so", RTLD_LAZY);

    if ( lib == 0 ) {
         printf("Failed to load the shared library \n");
         return -1;
    }

    BinaryFunction bf = (BinaryFunction)dlsym(lib,"Add");

    if ( bf == 0 ) {
           printf("Failed to retrieve function pointer \n");
           return -1;
    }

    int r = (*bf)(3,4);
    dlclose(lib);
  
    printf("%d\n",r);

    return 0;
}

// Eof main.cpp