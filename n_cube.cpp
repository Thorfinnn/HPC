#include <iostream>
#include <omp.h>

int main() {
    int start = 99; // Start of the range
    int end = 120; // End of the range

    // Set the number of threads
    int num_threads = 4;
    omp_set_num_threads(num_threads);

    // Parallel region
    #pragma omp parallel for
    for (int i = start; i <= end; ++i) {
        // Compute the cube of the number
        int cube = i * i * i;
        // Print the cube
        #pragma omp critical
        std::cout << "Cube of " << i << " is " << cube << std::endl;
    }

    return 0;
}

