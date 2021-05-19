#!/bin/bash

threads=(2 4 6 8)

n_pes=(2 4 6 8)

N=(10 100 200 400 600 800 1000 2000)

echo "OPEN_MP" >> output.txt
for i in "${threads[@]}"; do
	echo >> output.txt
	echo 'threads' $i >> output.txt
	
	/usr/local/opt/llvm/bin/clang -fopenmp -L/usr/local/opt/llvm/lib open_mp.c
	for j in "${N[@]}"; do
		echo >> output.txt
		echo 'N' $j >> output.txt
		export OMP_NUM_THREADS=$i
		for k in {0..5}; do
			./a.out $j >> output.txt
		done

	done 
	echo >> output.txt
done

echo >> output.txt
echo "MPI" >> output.txt
for i in "${n_pes[@]}"; do
	echo 'n_pes' $i >> output.txt
	for j in "${N[@]}"; do
		echo >> output.txt
		echo 'N' $j >> output.txt
		$HOME/opt/usr/local/bin/mpicc  ./MPI.c
		for k in {0..5}; do
			$HOME/opt/usr/local/bin/mpirun -np $i ./a.out $j >> output.txt
			echo >> output.txt
		done

	done 
	echo >> output.txt
done


