#include "GEMM_blocking.hpp"

static inline int min_val(int a, int b) {
    return (a < b) ? a : b;
}

void gemm_blocking(int M, int K, int N, const int* A, const int* B, int* C, int block_size) {

    //Reset C matrix to 0s
    for (int i = 0; i < M * N; ++i) {
        C[i] = 0;
    }

    //Tiled multiplication
    for (int ii = 0; ii < M; ii += block_size) {
        for (int jj = 0; jj < N; jj += block_size) {
            for (int kk = 0; kk < K; kk += block_size) {

                int i_max = min_val(ii + block_size, M);
                int j_max = min_val(jj + block_size, N);
                int k_max = min_val(kk + block_size, K);

                for (int i = ii; i < i_max; ++i) {
                    for (int j = jj; j < j_max; ++j) {
                        for (int k = kk; k < k_max; ++k) {
                            C[i * N + j] += A[i * K + k] * B[k * N + j];
                        }
                    }
                }

            }
        }
    }
}