#include <iostream>
#include <fstream>
#include <chrono>
#include "../src/GEMM_simple.hpp"
#include "../src/GEMM_blocking.hpp"

int main(int argc, char* argv[]) {
    //Resolve input file path
    std::string filepath = "../tests/input.txt"; 
    if (argc > 1) {
        filepath = argv[1];
    }

    std::ifstream infile(filepath);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open input file at " << filepath << std::endl;
        return 1;
    }

    int M, K, N;
    infile >> M >> K >> N;

    //Allocate raw dynamic arrays on heap
    int* A = new int[M * K];
    int* B = new int[K * N];
    int* C = new int[M * N];

    //Read values into raw arrays
    for (int i = 0; i < M * K; ++i) infile >> A[i];
    for (int i = 0; i < K * N; ++i) infile >> B[i];
    infile.close();

    //Set fixed decimal precision (4 decimal places) using std::cout
    std::cout.setf(std::ios::fixed);
    std::cout.precision(4);

    //Simple GEMM Execution & Timing (Isolated)
    auto start_simple = std::chrono::high_resolution_clock::now();
    
    gemm_simple(M, K, N, A, B, C);
    
    auto stop_simple = std::chrono::high_resolution_clock::now();
    double duration_simple = std::chrono::duration<double, std::milli>(stop_simple - start_simple).count();

    //Print Simple Output
    std::cout << "Algorithm: GEMM Simple" << std::endl;
    std::cout << "Result matrix:" << std::endl;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << C[i * N + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Execution time: " << duration_simple << " ms\n\n";

    //Reset C matrix to zero before running Blocking GEMM
    for (int i = 0; i < M * N; ++i) {
        C[i] = 0;
    }

    //Blocking GEMM Execution & Timing (Isolated)
    auto start_block = std::chrono::high_resolution_clock::now();
    
    gemm_blocking(M, K, N, A, B, C, 32);
    
    auto stop_block = std::chrono::high_resolution_clock::now();
    double duration_block = std::chrono::duration<double, std::milli>(stop_block - start_block).count();

    //Print Blocking Output
    std::cout << "Algorithm: GEMM Blocking" << std::endl;
    std::cout << "Result matrix:" << std::endl;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << C[i * N + j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Execution time: " << duration_block << " ms" << std::endl;

    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}