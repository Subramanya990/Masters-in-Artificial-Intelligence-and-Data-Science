#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[]){

int A [] = {84, 30, 95, 94, 36, 73, 52, 23, 2, 13};
int S [10] = {0};
#pragma omp parallel
 {
    int S_private[10] = {0};
    #pragma omp for
    for (int n=0 ; n<10 ; ++n ) {
        for (int m=0; m<=n; ++m){
            S_private[n] += A[m];
        }
    }
    #pragma omp critical
    {
        for(int n=0; n<10; ++n) {
            S[n] += S_private[n];
        }
    }
  }
  
  for(int n=0; n<10; ++n) printf("S[%i]=%i\n",n,S[n]);
  printf("Expected_output = {84, 114, 209, 303, 339, 412, 464, 487, 489, 502}\n");
}
