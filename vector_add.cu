#include <stdio.h>

// Kernel function to perform vector addition
__global__ void vectorAdd(int *a, int *b, int *c, int n) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if (index < n) {
        c[index] = a[index] + b[index];
    }
}

int main() {
    int n = 100000; // Size of vectors
    int *a, *b, *c; // Host vectors
    int *d_a, *d_b, *d_c; // Device vectors
    int size = n * sizeof(int);

    // Allocate memory for host vectors
    a = (int*)malloc(size);
    b = (int*)malloc(size);
    c = (int*)malloc(size);

    // Initialize host vectors
    for (int i = 0; i < n; ++i) {
        a[i] = i;
        b[i] = i;
    }

    // Allocate memory for device vectors
    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_c, size);

    // Copy host vectors to device
    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    // Define grid and block dimensions
    int blockSize = 256;
    int gridSize = (n + blockSize - 1) / blockSize;

    // Launch kernel
    vectorAdd<<<gridSize, blockSize>>>(d_a, d_b, d_c, n);

    // Copy result back to host
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    // Verify the result
    for (int i = 100000-20; i < 100000; ++i) {
        printf("%d + %d = %d\n", a[i], b[i], c[i]);
    }

    // Free device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    // Free host memory
    free(a);
    free(b);
    free(c);

    return 0;
}
