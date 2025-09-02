#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(void) {
    int rank;
    MPI_Status status;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int x = 42, y;

    if (rank == 0) {
        MPI_Send(&x, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent number %d to process 1\n", x);
    } 
    else if (rank == 2) { // rank mismatch example
        MPI_Recv(&y, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process 2 received number %d from process 0\n", y);
    } 
    else {
        char name[MPI_MAX_PROCESSOR_NAME];
        int len;
        MPI_Get_processor_name(name, &len);
        printf("Just a normal process from rank %d machine %s\n", rank, name);
    }

    MPI_Finalize();
    return 0;
}
