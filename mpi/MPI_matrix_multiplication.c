#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

// matrix multiplication (m*a)*(a*n) = (m*n) 

#define NRA 6        // number of rows in matrix A 
#define NCA 5        // number of columns in matrix A 
#define NCB 4         // number of columns in matrix B 
#define MASTER 0      // taskid of first task 
#define FROM_MASTER 1 // setting a message type 
#define FROM_WORKER 2 // setting a message type 

int main(int argc, char *argv[])
{
    int numtasks, taskid,  numworkers,  source,  dest,  mtype, rows, averow, extra, offset,  i, j, k, rc; 
    int a[NRA][NCA],        // matrix A 
        b[NCA][NCB],           // matrix B 
        c[NRA][NCB];           // result matrix C 
        
        
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid); // getting task id
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks); // getting total tasks
    if (numtasks < 2) // exit if task less than 2
    {
        printf("Need at least two MPI tasks. Quitting...\n");
        MPI_Abort(MPI_COMM_WORLD, rc);
        exit(1);
    }
    
    numworkers = numtasks - 1; //workers = task - 1(master)

    /**************************** master task ************************************/
    if (taskid == MASTER)
    {
        printf("[~] ---------- 18BCI0174 ARYAN ---------\n [~]Started with %d tasks => 1 master, %d workers\n\n", numtasks, numworkers);
        
        // initializing array's values
        printf("~ Initializing arrays of size %d * %d, %d * %d...\n", NRA,NCA,NCA,NCB);
        printf("~ would result in matrix of size %d * %d\n\n",NRA,NCB);
        for (i = 0; i < NRA; i++)
            for (j = 0; j < NCA; j++)
                a[i][j] = i + j;
        for (i = 0; i < NCA; i++)
            for (j = 0; j < NCB; j++)
                b[i][j] = i * j;



        // Send matrix data to the worker tasks 
        averow = NRA / numworkers;
        extra = NRA % numworkers;
        offset = 0; //=>position
        mtype = FROM_MASTER; //msg type
        for (dest = 1; dest <= numworkers; dest++)
        {
            rows = (dest <= extra) ? averow + 1 : averow;
            printf("[~]Sending %d rows to task %d\n", rows, dest);
            MPI_Send(&offset, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
            MPI_Send(&a[offset][0], rows * NCA, MPI_DOUBLE, dest, mtype,
                     MPI_COMM_WORLD);
            MPI_Send(&b, NCA * NCB, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
            offset = offset + rows;
        }


        // Receive results from worker tasks
        mtype = FROM_WORKER; //msg type
        for (i = 1; i <= numworkers; i++)
        {
            source = i;
            MPI_Recv(&offset, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
            MPI_Recv(&c[offset][0], rows * NCB, MPI_DOUBLE, source, mtype,
                     MPI_COMM_WORLD, &status);
            printf("[~]Received results from task %d\n", source);
        }

        // results 
        printf("\n[+] ------ Result Matrix -----:->\n");
        for (i = 0; i < NRA; i++)
        {
            printf("\n");
            for (j = 0; j < NCB; j++)
                printf("%d   ", c[i][j]);
        }
    }

    //**************************** worker task ************************************
    if (taskid > MASTER)
    {
        mtype = FROM_MASTER;
        MPI_Recv(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
        MPI_Recv(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
        MPI_Recv(&a, rows * NCA, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);
        MPI_Recv(&b, NCA * NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);

        for (k = 0; k < NCB; k++)
            for (i = 0; i < rows; i++)
            {
                c[i][k] = 0;
                for (j = 0; j < NCA; j++)
                    c[i][k] = c[i][k] + a[i][j] * b[j][k];
            }
        mtype = FROM_WORKER;
        MPI_Send(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
        MPI_Send(&c, rows * NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
