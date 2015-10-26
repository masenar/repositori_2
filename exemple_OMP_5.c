#include <stdio.h>
#include <omp.h>
int main (void)
{
   int A=0;
   omp_set_nested(1);
   omp_set_max_active_levels(8);
   omp_set_dynamic(0);
   omp_set_num_threads(2);
   #pragma omp parallel
   {
      printf ("Hello world from thread %d\n", omp_get_thread_num());
      omp_set_num_threads(3);
      #pragma omp parallel
      {
          #pragma omp critical
          A++;
          omp_set_num_threads(4);
/*          #pragma omp single */
          {
          /*
           * The following should print:
           * Inner: max_act_lev=8, num_thds=3, max_thds=4
           * Inner: max_act_lev=8, num_thds=3, max_thds=4
           */
               printf ("Inner: max_act_lev=%d, num_thds=%d, max_thds=%d, thread_id= %d, parent =%d\n",
                        omp_get_max_active_levels(), omp_get_num_threads(),
                        omp_get_max_threads(),omp_get_thread_num(), omp_get_ancestor_thread_num(1));
          }
      }
      #pragma omp barrier
      printf (" After inner section A = %d \n", A);
/*      #pragma omp single*/
      {
      #pragma omp critical
       A++;
      /*
       * The following should print:
       * Outer: max_act_lev=8, num_thds=2, max_thds=3
       */
          printf ("Outer: max_act_lev=%d, num_thds=%d, max_thds=%d, thread_id= %d, parent =%d\n",
                        omp_get_max_active_levels(), omp_get_num_threads(),
                        omp_get_max_threads(),omp_get_thread_num(), omp_get_ancestor_thread_num(1));
       }
   }
   printf (" Final A = %d \n", A);
   return 0;
}
