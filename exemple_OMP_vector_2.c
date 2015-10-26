#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define N 24
 
int  i, k, tid;

__attribute__ ((aligned (64))) int a[N], b[N];


int main ()  {
 
/* Explicitly turn off dynamic threads */
  omp_set_dynamic(0);
 
 /*some initializations */

 for (i=0; i<N; i++)
   a[i] = b[i] = (i * 1.0);
  
  
 printf("Original Matrix:\n");

 for (i=0; i<N; i++)
 		printf (" %d  ", a[i]);

 
  printf("\n ************************************\n");
 
#pragma omp simd safelen(4)
 
  for (k=5; k<N; k++) {
    a[k] = a[k-4] + b[k];
  }
  printf("Modified Matrix:\n");

  for (i=0; i<N; i++)
 		printf (" %d  ", a[i]);

   printf("\n ************************************\n");

return(0);
}
