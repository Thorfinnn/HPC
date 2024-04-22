#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int SIZE = 1000; // Size of matrices A, B, and C

// Function to initialize matrices with random values
void initializeMatrices(vector<vector<int>>& A, vector<vector<int>>& B) {
    srand(time(0)); // Seed the random number generator with current time

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            A[i][j] = rand() % 100; // Assign a random value between 0 and 99
            B[i][j] = rand() % 100; // Assign a random value between 0 and 99
        }
    }
}

// Function to multiply matrices C = A * B
void multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    #pragma omp parallel for collapse(2) // Parallelize the nested loops
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < SIZE; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    vector<vector<int>> A(SIZE, vector<int>(SIZE, 0)); // Matrix A
    vector<vector<int>> B(SIZE, vector<int>(SIZE, 0)); // Matrix B
    vector<vector<int>> C(SIZE, vector<int>(SIZE, 0)); // Matrix C

    // Initialize matrices A and B with random values
    initializeMatrices(A, B);

    // Serial version
    auto start_serial = high_resolution_clock::now();
    multiplyMatrices(A, B, C);
    auto stop_serial = high_resolution_clock::now();
    auto duration_serial = duration_cast<milliseconds>(stop_serial - start_serial);
    cout << "Serial execution time: " << duration_serial.count() << " milliseconds" << endl;

    // Parallel version
    for (int num_threads = 12; num_threads <= omp_get_max_threads(); num_threads *= 2) {
        omp_set_num_threads(num_threads); // Set the number of threads

        auto start_parallel = high_resolution_clock::now();
        multiplyMatrices(A, B, C);
        auto stop_parallel = high_resolution_clock::now();
        auto duration_parallel = duration_cast<milliseconds>(stop_parallel - start_parallel);
        cout << "Parallel execution time with " << num_threads << " threads: " << duration_parallel.count() << " milliseconds" << endl;
    }

    return 0;
}

