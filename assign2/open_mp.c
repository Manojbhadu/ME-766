#include <stdio.h>
#include<math.h>
#include <omp.h>
#include<float.h>
#include<stdlib.h>
#include<time.h>
#include <omp.h>
#include <time.h>

int main(int argc, char **argv)
{

clock_t start, end;
double cpu_time_used;

int N = atoi(argv[1]);


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

start = clock();

#pragma omp parallel for
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


for (int k=0; k<N-1;++k)          
{
	#pragma omp parallel for private(j, pivot_factor) shared(N)
	for (int i=k+1; i<N; ++i)
	{
		pivot_factor = C[i][k]/C[k][k];
		
		for(int j=k;j<N; ++j)
		{
			C[i][j] = C[i][j]-pivot_factor*C[k][j];
		}
	}
}

end = clock();
double time_used = ((double) (end - start)) / CLOCKS_PER_SEC;


/*Uncomment below commented lines for print the upper triangular matirx */
/*
for( int i = 0; i < N; ++i)
  	{
	  	for(int j = 0;  j < N; ++j)
			{
				printf("%f ", C[i][j]);
			}
		printf("\n");
	} 
*/
printf("%.4f ", time_used);

  return 0;



}