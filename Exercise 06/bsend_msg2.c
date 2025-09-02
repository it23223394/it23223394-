#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(void) {
    int rank;
    MPI_Status status;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int x = 500, y;
    int buf_size;

    // Calculate buffer size and attach
    MPI_Pack_size(1, MPI_INT, MPI_COMM_WORLD, &buf_size);
    buf_size += MPI_BSEND_OVERHEAD;
    char* buffer = (char*)malloc(buf_size);
    MPI_Buffer_attach(buffer, buf_size);

    if (rank == 0) {
        MPI_Bsend(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data (Bsend) %d to process 1\n", x);
    } 
    else if (rank == 1) {
        MPI_Recv(&y, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process 1 received data (Bsend) %d from process 0\n", y);
    } 
    else {
        printf("Just a normal process with rank %d\n", rank);
    }

    MPI_Buffer_detach(&buffer, &buf_size);
    free(buffer);
    MPI_Finalize();
    return 0;
}
