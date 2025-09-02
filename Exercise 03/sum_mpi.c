#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    long long local_sum = 0;
    long long global_sum = 0;
    long long n = 10000000;  // Sum from 1 to 10,000,000

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Determine the range of numbers for this process
    long long chunk_size = n / size;
    long long start = rank * chunk_size + 1;
    long long end = (rank == size - 1) ? n : (rank + 1) * chunk_size;

    // Compute local sum
    for (long long i = start; i <= end; i++) {
        local_sum += i;
    }

    // Reduce all local sums into global sum on rank 0
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Sum of numbers from 1 to %lld = %lld\n", n, global_sum);
    }

    MPI_Finalize();
    return 0;
}
