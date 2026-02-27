#include <iostream>
#include <cstdlib>   
#include <ctime>     
#include <cmath>     
#include <omp.h>   

#ifndef N
#define N 10000000
#endif

// this is the sequential version of the monte carlo estimation of pi,
// pretty much as the monteCarlo.cpp but without parallelism / OpenMP directives

int main() {
  
    long inside = 0;

    srand(time(nullptr));

    double start = omp_get_wtime();

    for (long i = 0; i < N; i++) {
        double x = rand() / (double)RAND_MAX;
        double y = rand() / (double)RAND_MAX;
        if (x*x + y*y <= 1.0)
            inside++;
    }

    double end = omp_get_wtime();

    double pi_estimate = 4.0 * inside / N;
    double error = std::abs(pi_estimate - M_PI);

    std::cout << "Sequential Monte Carlo pi estimation\n";
    std::cout << "Points: " << N << "\n";
    std::cout << "Estimated pi = " << pi_estimate << "\n";
    std::cout << "Error = " << error << "\n";
    std::cout << "Elapsed time = " << (end - start) << " s\n";

    return 0;
}
