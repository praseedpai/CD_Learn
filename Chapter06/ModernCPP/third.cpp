#include <stdio.h>
#include <iostream>
using namespace std;

template <class T>
class IComparitorStrategy{  
     public: 
         virtual int Execute(T a, T b) = 0;
};


template <class T>
class GenericComparitor : public IComparitorStrategy<T> {
        public:
	int Execute(T a, T b) { 
		T  pa  = a ;   double  pb  = b ; 
		return pa > pb ? 1 : (pb > pa ) ? -1 : 0; 
        	}

};
template <class T>
void BSort(unique_ptr<T []> &arr, int len , IComparitorStrategy<T>& test) {
            int n = len;
              for(int i = 0; i<n; ++i)
                for (int j = 0; j < n-i-1; j++)
                   if (test.Execute(arr[j],arr[j + 1]) > 0) {  
                              T  temp = arr[j]; arr[j] = arr[j + 1];  arr[j + 1] = temp; 
                  }
}

int main(int argc, char ** args){
         //---- Check whether there is any Command Line argument
        if ( argc  == 1 ) {  printf("No Command Line ARguments");    return 1; }
       //------ Allocate Array
        unique_ptr<double[]> arr (new double[argc-1]);
        for( int i=0; i< argc-1 ; ++i )
                 arr[i] = atof(args[i+1]);
              //---------- A Bubble Sort Routine
              GenericComparitor<double> a;
              BSort(arr, argc-1 , a) ;
            
            //-------------------- Spit the Output
            for( int i=0; i<argc-1; ++i   )  { printf("%e\n",arr[i]); }
           
            return 0;
    } // Main
