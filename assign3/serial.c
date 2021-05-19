#include <stdio.h>
#include<math.h>
#include <omp.h>
#include<float.h>
#include<stdlib.h>
#include<time.h>
#include <omp.h>


int main()
{
int N;
N=10;

/* Initialize and fill the matix x and y */
double (*A)[N] = malloc(N * sizeof(*A));
double (*B)[N] = malloc(N * sizeof(*B));
double (*C)[N] = malloc(N * sizeof(*C));


srand(time(0));
double pivot_factor;
int i,j,k;

for(int i = 0; i < N; ++i)
  	{for( int j = 0;  j < N; ++j)
     	{ A[i][j] = (double)rand()/RAND_MAX*100;
     	  B[i][j] = (double)rand()/RAND_MAX*100;
 		  C[i][j] = 0;
 		}
 	}




for (int i = 0; i < N; ++i)
{
	for (int j = 0; j < N; ++j) 
	{
        for (int k = 0; k < N; ++k) 
        {
        	C[i][j] += A[i][k] * B[k][j];
        }
     }
}






for( int i = 0; i < N; ++i)
  	{
	  	for(int j = 0;  j < N; ++j)
			{
				printf("%f ", C[i][j]);
			}
		printf("\n");
	}


  return 0;



}