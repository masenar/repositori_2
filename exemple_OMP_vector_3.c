#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define N 24
 
int  i, k, x, tid;

__attribute__ ((aligned (64))) int a[N], b[N];

int foo (int y){

  return (y+y);
}

int main ()  {
 
/* Explicitly turn off dynamic threads */
  omp_set_dynamic(0);
 
 /*some initializations */

 for (i=0; i<N; i++){
   a[i] = (i * 1.0);
   b[i] = 0;
 }
  
 printf("Original Matrix:\n");

 for (i=0; i<N; i++)
 		printf (" %d  ", a[i]);

 
  printf("\n ************************************\n");
 
 

  for (k = 0; k<N; k++) {
     x = a[k];
     b[k] = foo(x+a[k+1]);
  }
 
  
  printf("Modified Matrix:\n");

  for (i=0; i<N; i++)
 		printf (" %d  ", b[i]);

   printf("\n ************************************\n");

return(0);
}
