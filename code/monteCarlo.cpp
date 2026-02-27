#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <omp.h>

// added standard configurations if the N and num threads are not wrote in the makefile
#ifndef N
#define N 10000000
#endif

#ifndef NUM_THREADS
#define NUM_THREADS 4
#endif

int main() {
    // this is used to count how many points fall inside the circle
    long inside = 0;

    double start = omp_get_wtime();

    // this starts the parallel execution, the reduction defines that each thread should get a private copy of
    // the variable inside so no data race occurs, and num_threads is used to define how many threads this parallel
    // section should put to work
    #pragma omp parallel reduction(+:inside) num_threads(NUM_THREADS)
    {
        // this seed is mandatory so that each thread won't start computing starting with the same random number,
        // and also using time(nullptr) so that for each run the output will be non-deterministic / different
        unsigned int seed = omp_get_thread_num() + time(nullptr); // one seed per thread

        // this directive is used so that the loop splits parts of the loop to each thread equally, without it
        // threads would have to compute the for loop entirely one by one
        #pragma omp for
        for (long i = 0; i < N; i++) {
            // here both the x and y basically get a random number starting from the seed
            double x = rand_r(&seed) / (double)RAND_MAX;
            double y = rand_r(&seed) / (double)RAND_MAX;

            // here it checks if (x^2 + y^2) <= 1, i.e. if the point is inside the circle
            if (x*x + y*y <= 1.0)
                inside++;
        }
    }

    double end = omp_get_wtime();
    // the estimation of pi is given by the formula (4 * number of points inside the circle) / number of total points (both 
    // the square and the circle)
    double pi_estimate = 4.0 * inside / N;
    // computing error between estimated and real value of pi
    double error = std::abs(pi_estimate - M_PI);

    std::cout << "Parallel Monte Carlo pi estimation\n";
    std::cout << "Points: " << N << "\n";
    std::cout << "Estimated pi = " << pi_estimate << "\n";
    std::cout << "Error = " << error << "\n";
    std::cout << "Elapsed time = " << (end - start) << " s\n";

    return 0;
}
