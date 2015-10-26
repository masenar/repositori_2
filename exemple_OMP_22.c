#include <omp.h> 
#include <stdio.h>
 
int  a, b, i, tid, j, k, n=8, m=8;
float x;
 
 
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
  omp_set_num_threads (3); 
#pragma omp parallel private(tid,i)  shared (n)
  {
     for  (i=0; i<n; i++)
     {
        printf("THREAD %d:    i =  %d \n",omp_get_thread_num(),i);
       #pragma omp for lastprivate(k)
       for (k = 0; k<m; k++)
       {
           tid = omp_get_thread_num();
           printf("Thread %d:   i, k = %d %d \n",tid,i, k);
       }
        printf("****  End of k loop: %d i= %d  Thread: %d ************ \n ", k, i, omp_get_thread_num());
     }
  }  /* end of parallel section */
  printf("************************************\n");
  printf("Master thread doing serial work here\n");
  printf("************************************\n");
  
omp_set_num_threads (4); 
  
#pragma omp parallel for private(i,a)
for (i=0; i<n; i++)
{
   a = i+1;
   printf("Thread %d has a value of a = %d for i = %d\n",
   omp_get_thread_num(),a,i);
  } /*-- End of parallel for --*/

a=0;

printf ("++++++++++++++++++++++++++++++++++++++++++++++++ \n");
#pragma omp parallel for private(i) shared(a)
for (i=0; i<n; i++)
{
 #pragma omp critical
   a = i+1;
   printf("Thread %d has a value of a = %d for i = %d\n",
   omp_get_thread_num(),a,i);
  } /*-- End of parallel for --*/

printf(" ******************************** \n");
printf (" Nested parallelism is %s \n", omp_get_nested() ? "supported" : "not supported");
omp_set_nested(1);
printf(" ******************************** \n");
printf (" Nested parallelism is %s \n", omp_get_nested() ? "supported" : "not supported");
#pragma omp parallel private(tid)
{
   tid = omp_get_thread_num();
   printf("Thread %d executes the outer parallel region\n",tid);
   #pragma omp barrier
   #pragma omp parallel num_threads(2) firstprivate(tid)
   {
      if (tid != 1)
        printf("TID %d: Thread %d executes inner parallel region\n",tid,omp_get_thread_num());
    } /*-- End of inner parallel region --*/
} /*-- End of outer parallel region --*/


}

