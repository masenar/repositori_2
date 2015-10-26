#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 


#define N 128
 
int  i, tid;

__attribute__ ((aligned (64))) int a[N];
__attribute__ ((aligned (64))) int b[N]; 
__attribute__ ((aligned (64))) int c[N];


void vec0 (int *a, int *b, int off, int len)
{
 __builtin_expect (off % 32, 0);
 __builtin_assume_aligned (a, 64);
 __builtin_assume_aligned (b, 64);
 
 for (i=0; i< len; i++)
 {
  a[i] = (a[i] % 5 > 2.0) ?
       a[i] + b[i] :
       a[i+off] + b[i];
  }
}
 
void vec1(int *a, int *b, int off, int len)
{

 for (i=0; i < len; i++)
  {
  a[i] = (a[i] % 5 > 2.0) ?
       a[i] + b[i] :
       a[i + off] + b[i];
  }
} 
 

main ()  {
 
/* Explicitly turn off dynamic threads */
  omp_set_dynamic(0);
 
 /*some initializations */

for (i=0; i<N; i++)
   a[i] = b[i] = (i * 1.0);
  
  
  printf("Original Matrix:\n");

 for (i=0; i<N; i++)
 		printf (" %d  ", a[i]);

 
  printf("\n ************************************\n");
 

vec0 (a, b, N/2, N/2); 


 printf("Modified Matrix:\n");

 for (i=0; i<N; i++)
 		printf (" %d  ", a[i]);

 
  printf("\n ************************************\n");
}
