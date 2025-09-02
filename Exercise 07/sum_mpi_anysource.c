#include <stdio.h>
#include <mpi.h>

int main() {
    int rank, size;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long int N = 10000000;
    long long int local_sum = 0;
    long long int sum = 0;

    long long int chunk = N / size;
    long long int start = rank * chunk + 1;
    long long int end = (rank == size - 1) ? N : start + chunk - 1;

    for(long long int i = start; i <= end; i++)
        local_sum += i;

    if(rank != 0)
        MPI_Send(&local_sum, 1, MPI_LONG_LONG_INT, 0, 0, MPI_COMM_WORLD);
    else {
        sum = local_sum;
        long long int tmp;
        MPI_Status status;
        for(int i = 1; i < size; i++) {
            // Use MPI_ANY_SOURCE for receiving from any process
            MPI_Recv(&tmp, 1, MPI_LONG_LONG_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            sum += tmp;
        }
        printf("Sum of numbers from 1 to %lld = %lld\n", N, sum);
    }

    MPI_Finalize();
    return 0;
}

