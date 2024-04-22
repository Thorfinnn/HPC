#include <iostream>
#include <omp.h>

int main() {
    int num_threads;
    #pragma omp parallel
    {
        num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        std::cout << "Hello World from thread " << thread_id << std::endl;
    }
    std::cout << "Number of threads created: " << num_threads << std::endl;
    return 0;
}
