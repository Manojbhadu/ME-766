#include <stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include <omp.h>
int main()    
{

int i, N ;     // N is number of sample points
N = 2000000 ;
float s = 0 ;
float random_number ;
#pragma omp parallel for reduction(+: s)
for (i=0;i<N;i++)
	{	
		random_number = ((double)rand()/RAND_MAX)*M_PI - M_PI/2 ;
		s+=cos(random_number) ;
	}

printf("%.8f", s*M_PI/N);
  return 0;
}
