
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <assert.h>

__global__ void matrixMult(int *A, int *B, int *C, int N){
    // Calculate the global row and column for each thread
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if(row < N && col < N){
        // def temprary variable for storing sum 
        int tmp = 0;
        for(int i = 0; i < N; i++){
            tmp += A[row * N + i] * B[i * N + col];
        }

        // storing results back
        C[row * N + col] = tmp;
    }
}


// We will check whether our results are reight or not
/* void verify_result(int *A, int *B, int *C, int N){
    int tmp;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            tmp = 0;
            for(int k = 0; k < N; k++){
                tmp += A[i * N + k] * B[k * N + j];
            }
            // use the assert for checking the final answer
            assert(tmp == C[i * N + j]);
        }
    }
} */

int main(int argc, char **argv){
    
    int N = atoi(argv[1]);
    clock_t    start, end;              /* timing */
    double  elapsed;
    int size = sizeof(double)*N*N ;
 
    
    start = clock();
    // memory allocation in host RAM
    int *h_A, *h_B, *h_C;
    cudaMallocHost((void **) &h_A, size);
    cudaMallocHost((void **) &h_B, size);
    cudaMallocHost((void **) &h_C, size);
    
    for(int i = 0; i < N; ++i)
    {for( int j = 0;  j < N; ++j)
        { h_A[i*N+j] = (double)rand()/RAND_MAX*100;
          h_B[i*N+j] = (double)rand()/RAND_MAX*100;
          h_C[i*N+j] = 0;
        }
    }


    int *dev_A, *dev_B, *dev_C;
    cudaMalloc((void **) &dev_A, size);
    cudaMalloc((void **) &dev_B, size);
    cudaMalloc((void **) &dev_C, size);
    

    // copy A and B from host to device 
    cudaMemcpy(dev_A, h_A, sizeof(int)*N*N, cudaMemcpyHostToDevice);
    cudaMemcpy(dev_B, h_B, sizeof(int)*N*N, cudaMemcpyHostToDevice);



    // Set our CTA and Grid dimensions
    int threads = 16;
    int blocks = (N + threads - 1) / threads;

    // Setup our kernel launch parameters
    dim3 THREADS(threads, threads);
    dim3 BLOCKS(blocks, blocks);

    // Launch our kernel
    matrixMult<<<BLOCKS, THREADS>>>(dev_A, dev_B, dev_C, N);
    cudaMemcpy(h_C, dev_C, size, cudaMemcpyDeviceToHost);
    cudaDeviceSynchronize();

     end   = clock();
      elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;   
      printf(" \n Time taken for size %d is %f \n",N,elapsed);


    // Verify the result
    // verify_result(h_A, h_B, h_C, N);

    // printf("All Results are correct");
    
    // Free allocated memory
    cudaFree(h_A);
    cudaFree(h_B);
    cudaFree(h_C);
    cudaFree(dev_A);
    cudaFree(dev_B);
    cudaFree(dev_C);

    return 0;
}
