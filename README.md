# Parallel_Distributed_Computing

contains:

in Open_mp

1. Using OpenMP, Design, develop and run a multi-threaded program to perform and print vector addition. --> VectorAddition.c

2. Using OpenMP, Design, develop and run a multi-threaded program to perform sum of N elements (N=2021) using Loop work Sharing with schedule clause. -->addition_n_number.c, multithreaded_Sum_N.c

3. Using open MP, design, develop and run a multi-threaded program to generate and print Fibonacci series. One thread has to generate the numbers up to the specified limit and another thread has to print them. --> fibonacci_series_multithreaded.c

4. Using Open MP, Design, develop and run a multi-threaded program to perform matrix multiplication --> matrix_multiplication_multithreaded.c

5. Using OpenMP, Design, develop and run a multi-threaded program to perform Combined parallel loop reduction. --> loop_redutction.c, prallel_loop_reduction.c

6. Using OpenMP, Design, develop and run a multi-threaded program to perform and Orphaned parallel loop reduction --> loop_reduction.c, prallel_loop_reduction.c

7. Write a parallel loop that computes the maximum and minimum values in an array --> max_min_array.c

________________________________________________________________________________________________________________________________________________________________________________

in MPI

1. Using MPI, Design, develop and run Broadcast communication (MPI_Bcast) using MPI_Send and MPI_Recv. --> mpi_bcast_using_mpi_SendRecv.c

2. Using MPI, Design, develop and run message passing using MPI_Send and MPI_Recv --> MPI_message_passing.c 

3. Using MPI, Design, develop and run Reduce communication for vector addition --> MPI_Vector_addition.c, MPI_VectorAddition_Reduce.c

4. Using MPI, Design, develop and run matrix multiplication using MPI_Send and MPI_Recv. In this code, the master task distributes a matrix multiply operation to numtasks-1 worker tasks --> MPI_matrix_multiplication.c

5. Using MPI, Design, develop and compute pi value using MPI_Send and MPI_Recv --> MPI_pi.c
