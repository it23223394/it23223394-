#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long long n = 10000000; // sum from 1 to n
    long long local_sum = 0;
    long long total_sum = 0;

    // divide the work among processes
    long long chunk_size = n / size;
    long long start = rank * chunk_size + 1;
    long long end = (rank == size - 1) ? n : start + chunk_size - 1;

    double start_time = MPI_Wtime(); // start timer

    for (long long i = start; i <= end; i++) {
        local_sum += i;
    }

    MPI_Reduce(&local_sum, &total_sum, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime(); // end timer

    if (rank == 0) {
        printf("Sum of numbers from 1 to %lld = %lld\n", n, total_sum);
        printf("Elapsed time: %f seconds\n", end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
