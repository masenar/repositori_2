#include <omp.h> 
#include <stdio.h>
 
int  a, b, i, tid;
float x;
 
#pragma omp threadprivate(a, x)

void diffusion (int nz, int ny, int count) {
#pragma omp parallel firstprivate(ny,nz, count)
{  
  int ii, z, y, tidd, parent_tidd, counter;
	printf("Thread %d:   of  %d \n", omp_get_thread_num(), omp_get_num_threads());
#pragma omp private(ii, z, y, tidd, counter)
  counter=0;	
  for (ii = 0; ii < count; ++ii)  {
   printf("Thread %d:   of  %d  loop ii %d \n", omp_get_thread_num(), omp_get_num_threads(), ii);
#pragma omp parallel for
    for (z = 0; z < nz; z++)    {
      for (y = 0; y < ny; y++)   {
         counter++;
	       tidd = omp_get_thread_num();
	       parent_tidd = omp_get_ancestor_thread_num(1);
	       printf("Thread %d:  of %d  parent %d ii, z, y = %d %d %d \n",tidd, omp_get_num_threads(), parent_tidd, ii, z, y );      
      } 
    } 
  }
  printf ("Thread: %d    Counter: %d \n", tidd, counter); 
 }
}   

 
main ()  {
 
/* Explicitly turn off dynamic threads */
  omp_set_dynamic(0);
 
  printf("1st Parallel Region:\n");
#pragma omp parallel private(b,tid)
  {
  tid = omp_get_thread_num();
  a = tid;
  b = tid;
  x = 1.1 * tid +1.0;
  printf("Thread %d:   a,b,x= %d %d %f\n",tid,a,b,x);
  }  /* end of parallel section */
 
  printf("************************************\n");
  printf("Master thread doing serial work here\n");
  printf("************************************\n");
 
  printf("2nd Parallel Region:\n");
#pragma omp parallel private(tid)
  {
  tid = omp_get_thread_num();
  printf("Thread %d:   a,b,x= %d %d %f\n",tid,a,b,x);
  }  /* end of parallel section */
  printf("************************************\n");
  printf("Master thread doing serial work here\n");
  printf("************************************\n");
  printf("3rd Parallel Region:\n");
 /* omp_set_nested_(1); */
  diffusion (3, 2, 4);
}

