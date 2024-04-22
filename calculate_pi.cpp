#include <iostream>
#include <random>
#include <cmath>
#include <omp.h>

int main() {
    int num_threads = 12; // Number of threads
    int num_points = 1000000; // Number of points to generate
    int total_points_in_circle = 0;

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    // Set the number of threads
    omp_set_num_threads(num_threads);

    // Parallel region
    #pragma omp parallel reduction(+:total_points_in_circle)
    {
        // Each thread generates a subset of points
        int local_count = 0;
        #pragma omp for
        for (int i = 0; i < num_points; ++i) {
            // Generate random (x, y) coordinate pair
            double x = dis(gen);
            double y = dis(gen);

            // Calculate distance from origin
            double distance = std::sqrt(x * x + y * y);

            // Check if point falls within the circle
            if (distance <= 1.0) {
                local_count++;
            }
        }
        // Accumulate local count to total count
        total_points_in_circle += local_count;
    }

    // Calculate PI
    double pi_estimate = (4.0 * total_points_in_circle) / static_cast<double>(num_points);

    // Output the estimated value of PI
    std::cout << "Estimated value of PI: " << pi_estimate << std::endl;

    return 0;
}

