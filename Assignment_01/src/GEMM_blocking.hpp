#ifndef GEMM_BLOCKING_HPP
#define GEMM_BLOCKING_HPP

void gemm_blocking(int M, int K, int N, 
                   const int* A, 
                   const int* B, 
                   int* C,
                   int block_size = 32);

#endif