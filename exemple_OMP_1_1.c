#include <omp.h> 
 
int  a, b, i, tid;
float x;
 
#pragma omp threadprivate(a, x)
 /*A small change to tesk git */
main ()  {
 
/* Explicitly turn off dynamic threads */
  omp_set_dynamic(0);
 
  printf("1st Parallel Region:\n");

#pragma omp parallel private(i, b, tid)

  for (i=0; i<2; i++){
    tid = omp_get_thread_num();
    a = tid;
    b = tid;
    x = 1.1 * tid +1.0;
    printf("Thread %d:   a,b,i,x= %d %d %d %f\n",tid,a,b,i,x);
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

}
