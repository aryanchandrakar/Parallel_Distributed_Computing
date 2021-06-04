#include "stdio.h"
#include "mpi.h"
#include "stdlib.h"

int main(int argc, char *argv[])
{
    const int tag = 42; // Message tag 
    int id, ntasks, source_id, dest_id, err, i;
    MPI_Status status;
    int msg[2];  // Message array 
    err = MPI_Init(&argc, &argv); // Initialize MPI 
    if (err != MPI_SUCCESS)
    {
        printf("MPI initialization failed!\n");
        exit(1);
    }
    err = MPI_Comm_size(MPI_COMM_WORLD, &ntasks); //get tasks
    err = MPI_Comm_rank(MPI_COMM_WORLD, &id);  // process id
    if (ntasks < 2) // atleast 2 processor needed if not exits
    {
        printf("You have to use at least 2 processors to run this program\n");
        MPI_Finalize(); 
        exit(0);
    }

    if (id == 0) // processor 0 recieves from all sources
    {
        // reciever
        for (i = 1; i < ntasks; i++)
        {
            err = MPI_Recv(msg, 2, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
            // message recieve
            source_id = status.MPI_SOURCE;
            // sender's id
            printf("Received message %d %d from process %d\n", msg[0], msg[1], source_id);
        }
    }
    else // all other remaning processors send to processor 0
    {
        // senders
        msg[0] = id;     // id added to msg
        msg[1] = ntasks; // total number of process
        dest_id = 0;     // destination process
        err = MPI_Send(msg, 2, MPI_INT, dest_id, tag, MPI_COMM_WORLD);
    }
    if (id == 0)
        printf("Ready\n");
    err = MPI_Finalize(); //end
    exit(0);
    return 0;
}
