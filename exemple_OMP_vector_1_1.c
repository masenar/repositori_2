#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 


#define N 128
 
int  i, tid;
float __attribute__ ((aligned (32))) a[N];
float __attribute__ ((aligned (32))) b[N]; 


void init(float a[])
{ int i;
  
  for (i = 0; i < N; i++) 
     a[i] = (float)i*1.5;
}

float checksum(float b[])
{ int i;
  float res = 0.0;

  for (i = 0; i < N; i++) 
     res += b[i]; 
  return res;
}

void vec0 (float *__restrict__ a, float *b, int n, int n1)
{

#ifdef ICC
__assume (n1%16==0); /* for icc compiler*/
#endif

 int i; 
 #pragma omp simd aligned (b:32)
 for (i=n1; i < n-n1; i++)
   a[i] = a[i] + b[i] + b[i+n1] + b[i-n1];
  
}
 
void vec1 (float *a, float *b, int n, int n1)
{

 int i; 

 for (i=n1; i < n-n1; i++)
   a[i] = a[i] + b[i] + b[i+n1] + b[i-n1];
  
}

int main ()  {
 
int i; 

float res = 0.0f;
 
 /*some initializations */

  init(a);
  init(b);
    
  printf("Original Matrix:\n");

 for (i=0; i<N; i++)
 		printf (" %f3.2  ", a[i]);

 
  printf("\n ************************************\n");
 

 vec0 (a, b, N, 16); 


 printf("Modified Matrix:\n");

 for (i=0; i<N; i++)
 		printf (" %f3.2  ", a[i]);

 
  printf("\n ************************************\n");
  
  res = checksum(a); 
  printf("res = %.2f\n", res);

  return (0);
}
