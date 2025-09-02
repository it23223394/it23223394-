#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

int main(int argc, char** argv) {
    int rank, size;
    long long int N = 10000000; // total number of points
    long long int local_N;
    long long int local_count = 0, total_count = 0;
    double x, y, pi;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Split work among processes
    local_N = N / size;

    // Seed random number generator uniquely for each process
    srand(time(NULL) + rank);

    // Monte Carlo simulation
    for(long long int i = 0; i < local_N; i++){
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if(x*x + y*y <= 1.0){
            local_count++;
        }
    }

    // Reduce results to rank 0
    MPI_Reduce(&local_count, &total_count, 1, MPI_LONG_LONG_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        pi = 4.0 * total_count / N;
        printf("Estimated Pi = %.10f using %lld samples\n", pi, N);
    }

    MPI_Finalize();
    return 0;
}
