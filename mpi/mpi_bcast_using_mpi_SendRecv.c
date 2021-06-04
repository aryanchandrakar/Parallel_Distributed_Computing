  
#include "stdio.h"
#include "stdlib.h"
#include "mpi.h"
#include "math.h"

int main(int argc, char **argv)
{
    //("*********** 18BCI0174 ARYAN ***********");
    int myid, numprocs;
    int tag, source, destination, count;
    int buffer;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    tag = 1;
    source = 0; // using mpi send only one sender
    destination = 1; // using mpi recieve only one reciever
    count = 1; // msg packet size count
    if (myid == source)
    {
        buffer = 100;
        MPI_Send(&buffer, count, MPI_INT, destination, tag, MPI_COMM_WORLD);
        printf("[~]source - processor %d,  sent msg- %d, to destination - processor %d\n", myid, buffer,destination);
    }
    if (myid == destination)
    {
        MPI_Recv(&buffer, count, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
        printf("\n[+]destination - processor %d,  got msg - %d, from source - processor %d\n", myid, buffer,source);
    }
    MPI_Finalize();
    return 0;
}
