#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int x[10], y[10];
    int bufsize;

    // calculate buffer size for Bsend
    MPI_Pack_size(10, MPI_INT, MPI_COMM_WORLD, &bufsize);
    bufsize += MPI_BSEND_OVERHEAD;

    char *buffer = (char*) malloc(bufsize);
    MPI_Buffer_attach(buffer, bufsize);

    if(rank == 1) {
        for(int i = 0; i < 10; i++) x[i] = i * 10;
        printf("Process %d sending data using Bsend\n", rank);
        MPI_Bsend(x, 10, MPI_INT, 3, 0, MPI_COMM_WORLD);
    }
    else if(rank == 3) {
        MPI_Recv(y, 10, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received data using Bsend:\n", rank);
        for(int i = 0; i < 10; i++) printf("%d ", y[i]);
        printf("\n");
    } else {
        printf("Just a normal process: rank %d\n", rank);
    }

    MPI_Buffer_detach(&buffer, &bufsize);
    free(buffer);
    MPI_Finalize();
    return 0;
}

