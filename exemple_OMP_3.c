#include <omp.h> 
#include <stdio.h> 
#include <stdlib.h> 

#define N 50
#define CHUNCKSIZE 5
 
 
int main ()  {

int i, chunck, tid;
float a[N], b[N], c[N];
char first_time;

/*some initializations */

for (i=0; i<N; i++)
   a[i] = b[i] = i * 1.0;
chunck = CHUNCKSIZE;
first_time = 'y';
 
/* Explicitly turn off dynamic threads */
  omp_set_dynamic(0);
 
  printf("1st Parallel Region:\n");
#pragma omp parallel for shared (a, b, c, chunck) private(i,tid) schedule (static, chunck) firstprivate (first_time)

  for (i=0; i<N; i++)
 	{
	if (first_time == 'y')
		{
		tid = omp_get_thread_num();
		first_time = 'n';
	}
	c[i] = a[i] + b[i];
	printf ("tid= %d  i= %d  c[i]= %f\n", tid, i, c[i]);
	}
}
