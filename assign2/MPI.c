#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int npes;
  int my_PE_num;     
  int N = atoi(argv[1]);      
  int i,j,k;                                 
  MPI_Status stat;            
  int tag1 = 1, tag2 = 100;       
  int n_rws;
  double     start,end; 

  MPI_Init(&argc, &argv);     
  MPI_Comm_size(MPI_COMM_WORLD, &npes );
  int n = N/(npes-1);
  /*printf("%d\n", npes);*/
  MPI_Comm_rank(MPI_COMM_WORLD, &my_PE_num );

  double (*A)[N], (*B)[N], (*C)[N];
  A = malloc(sizeof *A * N);
  B = malloc(sizeof *B * N);
  C = malloc(sizeof *C * N);

  if(my_PE_num==0) {
    for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
        B[i][j] = ((double)rand()/RAND_MAX)*100;
  }
    

start=MPI_Wtime(); 

/*  Broadcast B to every PE as it is needed by every PE  */
  MPI_Bcast(&(B[0][0]), N*N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  if(my_PE_num==0) {
    for(int i=0;i<N;i++)
      for(int j=0;j<N;j++)
        A[i][j] = ((double)rand()/RAND_MAX)*100;

    n_rws = N-n*(npes-2);       // number of rows to be sent to mype 1
    MPI_Send(&(A[0][0]), n_rws*N, MPI_DOUBLE, 1, tag1, MPI_COMM_WORLD);
    for(i=2;i<npes;i++)        // Remaining send equally to each mype
      MPI_Send(&(A[(i-2)*n+n_rws][0]), n*N, MPI_DOUBLE, i, tag1, MPI_COMM_WORLD);

    // Recieve by mype 1
    MPI_Recv(&(C[0][0]), n_rws*N, MPI_DOUBLE, 1, tag2, MPI_COMM_WORLD, &stat);
    for(i=2;i<npes;i++)
    // Recieve by other mypes
      MPI_Recv(&(C[(i-2)*n+n_rws][0]), n*N, MPI_DOUBLE, i, tag2, MPI_COMM_WORLD, &stat);

  }

  else {
    if(my_PE_num == 1)
      n_rws = N-n*(npes-2);
    else
      n_rws = n;

     
    MPI_Recv(&(A[0][0]), n_rws*N, MPI_DOUBLE, 0, tag1, MPI_COMM_WORLD, &stat);

    for(i=0;i<n_rws;i++)
      for(j=0;j<N;j++) {
        C[i][j] = 0.0;
        for(k=0;k<N;k++)
          C[i][j] = C[i][j] + A[i][k]*B[k][j];
      }

    MPI_Send(&(C[0][0]), n_rws*N, MPI_DOUBLE, 0, tag2, MPI_COMM_WORLD);  
  }

  MPI_Barrier( MPI_COMM_WORLD );

  for(k=0; k<N-1; k++) {
    n = (N-k-1)/(npes-1);
    if(my_PE_num == 0) {
      for(i=1;i<npes;i++) {
        MPI_Send(&C[k][0], N, MPI_DOUBLE, i, tag1+i, MPI_COMM_WORLD);
        n_rws = (N-k-1)-n*(npes-2);
        if(i == 1)
        MPI_Send(&C[k+1][0], n_rws*N, MPI_DOUBLE, i, tag1+i, MPI_COMM_WORLD);
        else
          MPI_Send(&C[k+1+(i-2)*n+n_rws][0], n*N, MPI_DOUBLE, i, tag1+i, MPI_COMM_WORLD);

      }
      

      for(i=1;i<npes;i++) {
        n_rws = (N-k-1)-n*(npes-2);
        if(i == 1)
          MPI_Recv(&C[k+1][0], n_rws*N, MPI_DOUBLE, i, tag2+i, MPI_COMM_WORLD, &stat);
        else
          MPI_Recv(&C[k+1+(i-2)*n+n_rws][0], n*N, MPI_DOUBLE, i, tag2+i, MPI_COMM_WORLD, &stat);
      }

    }
    else {
      MPI_Recv(&C[0][0], N, MPI_DOUBLE, 0, tag1+my_PE_num, MPI_COMM_WORLD, &stat);
            
      if(my_PE_num == 1)
        n_rws = (N-k-1)-n*(npes-2);
      else
        n_rws = n;
      
      
      MPI_Recv(&C[1][0], n_rws*N, MPI_DOUBLE, 0, tag1+my_PE_num, MPI_COMM_WORLD, &stat);

      double pivot_factor;
      for(i=1; i<n_rws+1; i++) {
        pivot_factor = C[i][k]/C[0][k];
        for(j=k; j<N; j++) {
          C[i][j] = C[i][j] - C[0][j]*pivot_factor;
        }
      }

      MPI_Send(&C[1][0], n_rws*N, MPI_DOUBLE, 0, tag2+my_PE_num, MPI_COMM_WORLD);
    }
    
    MPI_Barrier( MPI_COMM_WORLD );
  }



/*Uncomment below commented lines for print the upper triangular matirx */
   /*if(my_PE_num==0)
   {
      printf("\n");
      for(i=0;i<10;i++)
      {
         for(j=0;j<10;j++)
         printf("%f\t",C[i][j]);
         printf("\n");
      }
   }*/                 

end=MPI_Wtime();
double time_taken = end - start;
printf("%.4f ", time_taken);

  MPI_Finalize();
  return EXIT_SUCCESS;
}




