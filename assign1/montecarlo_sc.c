#include <stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
int main()    
{

int i, N ;
N = 2000000 ;         //  N is number of sample points
float s = 0 ;
float random_number ;

for (i=0;i<N;i++)
	{	
		random_number = ((double)rand()/RAND_MAX)*M_PI - M_PI/2 ;
		s+=cos(random_number) ;
	}

printf("%.8f", s*M_PI/N);
  return 0;
}
