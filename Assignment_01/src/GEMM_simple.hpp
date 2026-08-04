#ifndef GEMM_SIMPLE_HPP
#define GEMM_SIMPLE_HPP

void gemm_simple(int M, int K, int N, 
                 const int* A, 
                 const int* B, 
                 int* C);

#endif