#include <stdio.h>
#include<math.h>

int main()    
{
	int i , N ;
	N = 2000000 ;              // N is number of divisions
	float h = M_PI/N ;
	float s=0 ;
	float a = -M_PI/2 ;
	float b = M_PI/2 ;

	s += cos(a) ;
	s +=cos(b) ;
	for (int i=1;i<N;i++)
		s+=2*cos(a+i*h) ;



  printf("%.8f", s*h/2);
  return 0;
}
