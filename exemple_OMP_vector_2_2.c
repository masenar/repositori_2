#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define N 36
 
int  i, k, tid;

__attribute__ ((aligned (64))) int a[N], b[N];


int main ()  {
 
/* Explicitly turn off dynamic threads */
/*  omp_set_dynamic(0); */
 
 /*some initializations */

 # pragma omp simd
 
 for (i=0; i<N; i++)
   a[i] = b[i] = (i * 1.0);
  
  
 printf("Original Matrix:\n");

 for (i=0; i<N; i++)
 		printf (" %d  ", a[i]);

 
  printf("\n ************************************\n");
  
 
  #pragma simd
 
  for (k=5; k<N; k++) {
    a[k] = a[k-2] + b[k];
  }
  printf("Firstly Modified Matrix:\n");

  for (i=0; i<N; i++)
 		printf (" %d  ", a[i]);

   printf("\n ************************************\n");
 
#pragma simd safelen(4)
 
  for (k=5; k<N; k++) {
    a[k] = a[k-4] + b[k];
  }
  printf("Secondly Modified Matrix:\n");

  for (i=0; i<N; i++)
 		printf (" %d  ", a[i]);

   printf("\n ************************************\n");

return(0);
}
