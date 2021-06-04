#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/* Define length of dot product vectors */
#define VECLEN 10

//("************** 18BCI0174 ARYAN ************");

int main(int argc, char *argv[])
{
    
    int i, myid, numprocs, len = VECLEN;
    int *a, *b;
    int mysum, allsum;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    /* Each MPI task performs the addition, obtains its partial sum, and then calls    MPI_Reduce to obtain the global sum. */
    if (myid == 0)
        printf("[~] Using %d tasks...\n", numprocs);

    /* Assign storage for vectors */
    a = (int *)malloc(len * sizeof(int));
    b = (int *)malloc(len * sizeof(int));
    /* Initialize vectors */
    for (i = 0; i < len; i++)
    {
        a[i] = 1; // vector of length 10 with all 1s
        b[i] = a[i];
    }
    /* Perform the dot product */
    mysum = 0;
    for (i = 0; i < len; i++)
    {
        mysum += a[i] * b[i];
    }
    
    

    printf("~ Task %d found partial sum = %d\n", myid, mysum);
    
    /* After the dot product, perform a summation of results on each node */
    MPI_Reduce(&mysum, &allsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (myid == 0)
        printf("Global sum of vector addition  =  %d \n", allsum);
    free(a);
    free(b);
    MPI_Finalize();
}
