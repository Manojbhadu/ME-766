
There are three c files:
1. open_mp.c
2. MPI.c
3. serial.c

To obtain the output.txt:
simply Run: bash run.sh
(It will run and give time 6 times for every thread and every PEs(which are 2,4,6,8) for each N value(10,100,200,400,600,800,1000,200) )
for MPI it will give time taken by every process so each line contain as many values as the number of PES and this repest 6 times for each N anfd PE. While in Open-mp eeach line contain time taken by that N value and Threads 6 times.

To run Indivisually run:
1. For Open MP:
export OMP_NUM_THREADS=threads  (where threads can take value of 2, 4, 6, 8 )
Now:
Compile:
/usr/local/opt/llvm/bin/clang -fopenmp -L/usr/local/opt/llvm/lib open_mp.c
Run:
./a.out N   (where N: size of matrix)
Output: Time taken by process

2. For MPI:
Compile:
$HOME/opt/usr/local/bin/mpicc  ./MPI.c
Run:
$HOME/opt/usr/local/bin/mpirun -np n ./a.out N (where n: PEs and N size of matrix)
Output: Time taken by each PEs 


