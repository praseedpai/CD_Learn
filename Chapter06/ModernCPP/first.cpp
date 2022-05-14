#include <stdio.h>
#include <iostream>
using namespace std;

int main(int argc, char ** args){
         //---- Check whether there is any Command Line argument
        if ( argc  == 1 ) {  printf("No Command Line ARguments");    return 1; }
       //------ Allocate Array
        unique_ptr<double[]> arr(new double[argc-1]);
        for( int i=0; i< argc-1 ; ++i )
                 arr[i] = atof(args[i+1]);
              //---------- A Bubble Sort Routine
              int n = argc - 1;
              for(int i = 0; i<n; ++i)
                for (int j = 0; j < n-i-1; j++)
                   if (arr[j]>arr[j + 1]){    double temp = arr[j];  arr[j] = arr[j + 1];  arr[j + 1] = temp;}
            //-------------------- Spit the Output
            for( int i=0; i<argc-1; ++i   )  { printf("%e\n",arr[i]); }
           
            return 0;
    } // Main
