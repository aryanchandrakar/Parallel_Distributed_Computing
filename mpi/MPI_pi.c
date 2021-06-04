#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define N 1000
 
int main(int argc, char* argv[])
{
    int myid,I=N*N,nodenum,i, count=0;                       
    double x,y,z,pi;                                                      
 
    MPI_Init(&argc, &argv);          
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);           
    MPI_Comm_size(MPI_COMM_WORLD, &nodenum);
    
    int circle[nodenum];
    long square[nodenum];
    
    
    srand(N+myid); 
 
    if(myid != 0)
    {
        for (i=0; i<I; ++i)                  
        {
            x= (double)(rand()%N)/N;           //gets a random x coordinate
            y =(double)(rand()%N)/N;           //gets a random y coordinate
            z = (x*x+y*y);                  
            if (z<=1)
            {
                count++;  // circle_point ++
            }
        }
        for(i=0; i<nodenum; ++i)
        {
            MPI_Send(&count,1,MPI_INT,0,1,MPI_COMM_WORLD);
            MPI_Send(&I,1,MPI_LONG,0,2,MPI_COMM_WORLD);
        }
    }
    else if (myid == 0)
    {
        for(i=0; i<nodenum; ++i)
        {
            MPI_Recv(&circle[i],nodenum,MPI_INT,MPI_ANY_SOURCE,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            
            MPI_Recv(&square[i],nodenum,MPI_LONG,MPI_ANY_SOURCE,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        }
    }

 
    if (myid == 0)                      
    {
        int finalcircle = 0;
        long finalsquare = 0;
        for(i = 0; i<nodenum; ++i)
        {
            finalcircle += circle[i];
            finalsquare += square[i];
        }
 
        pi = ((double)finalcircle/(double)finalsquare)*4.0;             
        printf("--------------- 18BCI0174 ARYAN ---------------\n~ pi=4*(random points in circle or radius 1 unit/random points in square or side 1 unit)\n");
        printf("\n[+] Pi found: %f\n", pi);            
 
    }
 
    MPI_Finalize();                     
    return 0;
}
