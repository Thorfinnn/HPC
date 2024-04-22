#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 10000;

// Function to initialize a matrix with random values
void initializeMatrix(vector<vector<int>>& matrix) {
    srand(time(0)); // Seed the random number generator with current time

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrix[i][j] = rand() % 100; // Assign a random value between 0 and 99
        }
    }
}

// Function to multiply two matrices
vector<vector<int>> multiplyMatrices(const vector<vector<int>>& mat1, const vector<vector<int>>& mat2) {
    vector<vector<int>> result(SIZE, vector<int>(SIZE, 0));

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            for (int k = 0; k < SIZE; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    return result;
}

int main() {
    // Initialize matrices with random values
    vector<vector<int>> matrix1(SIZE, vector<int>(SIZE, 0));
    vector<vector<int>> matrix2(SIZE, vector<int>(SIZE, 0));

    initializeMatrix(matrix1);
    initializeMatrix(matrix2);

    // Multiply matrices
    vector<vector<int>> result = multiplyMatrices(matrix1, matrix2);

    // Output result
    cout << "Matrix multiplication completed." << endl;

    return 0;
}
