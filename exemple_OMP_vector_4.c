#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define N 1200
 
int  i, tid, offset;

__attribute__ ((aligned (64))) float a[N];
__attribute__ ((aligned (64))) float b[N];

void foo(float *a, float *b, int off)
{
 int i;
 for( i = 0; i < N; i++)
     a[i] = a[i + off] * b[i];
}

void foo_2(int *a, int *b)
{
 int i;
 for( i = 0; i < N; i++)
   a[i] = (a[i] > 1.0) ?
     a[i] / b[i] :
     a[i];
}

void vec0(int *a, int *b, int off, int len)
{
   __assume(off % 32 == 0);
   __assume_aligned(a, 64);
   __assume_aligned(b, 64);
   
   int i;
   for(i = 0; i < len; i++)
   {
      a[i] = (a[i] > 1.0) ?
         a[i] * b[i] :
         a[i + off] * b[i];
   }
}

int main (int argc, char **argv)  {
 
int k;
 
/* Explicitly turn off dynamic threads */
/*  omp_set_dynamic(0); */
 
if (argc >= 2)
   offset = atoi(argv[1]); 
 
 printf ("Parameter = %d \n", offset); 
 /*some initializations */

 for (i=0; i<N; i++)
   a[i] = b[i] = (i * 1.0);
  
  
 printf("Original Matrix:\n");

 for (i=0; i<N; i++)
 		printf (" %f4.1  ", a[i]);

 
  printf("\n ************************************\n");
 
  foo (a, b, offset);

  printf("Modified Matrix:\n");

  for (i=0; i<N; i++)
 		printf (" %f4.1  ", a[i]);

   printf("\n ************************************\n");
   
#pragma omp simd safelen(4)
 
  for (k=5; k<N; k++) {
    a[k] = a[k-4] + b[k];
  }
  printf("Last Matrix:\n");

  for (i=0; i<N; i++)
 		printf (" %f4.1  ", a[i]);

   printf("\n ************************************\n");

return(0);
}
