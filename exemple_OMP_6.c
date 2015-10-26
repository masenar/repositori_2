#include <omp.h> 
#include <stdio.h>


void function_1 (){
int j, tmp1 =0;
#pragma omp parallel for firstprivate (tmp1)
for (j= 0; j<100; ++j){
		tmp1 =j;
   if (omp_get_thread_num() ==0)
      printf (" loop %d,   tmp1 %d \n",j, tmp1);
}
printf (" no lastprivate tmp1 = %d\n", tmp1);

}

void function_2 (){
int j, tmp1 =0;
#pragma omp parallel for firstprivate (tmp1) lastprivate(tmp1)
for (j= 0; j<100; ++j){
		tmp1 +=j;
   if (omp_get_thread_num() ==0)
      printf (" loop %d,   tmp1 %d \n",j, tmp1);
}
printf ("lastprivate tmp1 = %d\n", tmp1);
}

main ()  
{int a, i, j, tmp1, n=10, aa[10], bb[10];

 
/* Explicitly turn off dynamic threads */
  omp_set_dynamic(0);
  omp_set_num_threads(4);
tmp1=0;
#pragma omp parallel shared (tmp1)
{  
#pragma omp for firstprivate (tmp1) lastprivate (tmp1)
for (j= 0; j<100; ++j){
		tmp1 =j;
   if (omp_get_thread_num() ==0)
      printf ("  loop %d,   tmp1 %d \n",j, tmp1);
 }
}

printf (" lastprivate tmp1 = %d\n", tmp1);

function_1();
function_2();

#pragma omp parallel for private(i) lastprivate(a)
for (i=0; i<n; i++)
{
a = i+1;
printf("Thread %d has a value of a = %d for i = %d\n",
omp_get_thread_num(),a,i);
} /*-- End of parallel for --*/
printf("Value of a after parallel for: a = %d\n",a);


#pragma omp parallel for 
   for (i=1; i<n; i++) /* i is private by default */
   {
      bb[i] = (aa[i] + aa[i-1]) / 2.0;
      printf ("Work on b[%d] done by thread %d \n", i, omp_get_thread_num());
   }
  return(0);
}
