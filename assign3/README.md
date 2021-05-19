
If you are running the code on colab than:
1. open script.ipynb with google colab
2. Upload cuda_c.cu file under file section
3. Run all the cells sequentially, the desired results will be produced.

If you are running code on command line:

1. nvcc cuda_c.cu -o cuda
2. ./cuda N        (here N is the size)
3. If you want to verify that matrix multiplication is correct not
		1. Do uncommnet the verify_result function
		2. Do uncomment the : verify_result(h_A, h_B, h_C, N);
		if no asseration error means results are correct.
		(I have commeneted baecause for 10000 it will take too much time)

