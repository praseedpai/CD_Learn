#include <stdio.h>
#include <iostream>
using namespace std;

class IComparitorStrategy {  public: virtual int Execute(void *a, void *b) = 0;};
class IntComparitor : public IComparitorStrategy {
        public:
	int Execute(void *a, void *b) { 
		int  pa  = * (int *)a ;   int pb  =* (int *) b ; 
		return pa > pb ? 1 : (pb > pa ) ? -1 : 0; 
        	}

};

class DoubleComparitor : public IComparitorStrategy {
        public:
	int Execute(void *a, void *b) { 
		double  pa  = * (double *)a ;   double  pb  =* (double *) b ; 
		return pa > pb ? 1 : (pb > pa ) ? -1 : 0; 
        	}

};

void BSort(int *arr, int len , IComparitorStrategy& test) {
            int n = len;
              for(int i = 0; i<n; ++i)
                for (int j = 0; j < n-i-1; j++)
                   if (test.Execute((void *)&arr[j],(void *)&arr[j + 1]) > 0) {  
                              int  temp = arr[j]; arr[j] = arr[j + 1];  arr[j + 1] = temp; 
                  }
}

void BSort(double *arr, int len , IComparitorStrategy& test) {
            int n = len;
              for(int i = 0; i<n; ++i)
                for (int j = 0; j < n-i-1; j++)
                   if (test.Execute((void *)&arr[j],(void *)&arr[j + 1]) > 0) {  
                              double temp = arr[j]; arr[j] = arr[j + 1];  arr[j + 1] = temp; 
                  }
}
int main(int argc, char ** args){
         //---- Check whether there is any Command Line argument
        if ( argc  == 1 ) {  printf("No Command Line ARguments");    return 1; }
       //------ Allocate Array
        double *arr = new double[argc-1];
        for( int i=0; i< argc-1 ; ++i )
                 arr[i] = atof(args[i+1]);
              //---------- A Bubble Sort Routine
              DoubleComparitor a;
              BSort(arr, argc-1 , a) ;
            
            //-------------------- Spit the Output
            for( int i=0; i<argc-1; ++i   )  { printf("%e\n",arr[i]); }
            delete [] arr;
            return 0;
    } // Main
