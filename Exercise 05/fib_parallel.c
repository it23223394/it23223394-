#include <stdio.h>
#include <omp.h>

int fib(int n) {
    if (n < 2) return n;

    int i, j;

    #pragma omp task shared(i)
    i = fib(n - 1);

    #pragma omp task shared(j)
    j = fib(n - 2);

    #pragma omp taskwait
    return i + j;
}

int main() {
    int n = 10; // Fibonacci number to compute
    int result;

    double start = omp_get_wtime();  // <-- START TIMER

    #pragma omp parallel
    {
        #pragma omp single
        result = fib(n);
    }

    double end = omp_get_wtime();    // <-- END TIMER

    printf("Fibonacci(%d) = %d\n", n, result);
    printf("Elapsed time: %f seconds\n", end - start);  // <-- PRINT TIME
    return 0;
}
