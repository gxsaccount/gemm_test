#include <stdio.h>
// #include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "common/utils.h"
// CUDA runtime
#include <cublas_v2.h>
#include <cuda_runtime.h>

void MY_MMult(cublasHandle_t handle, int m, int n, int k, float *d_A, int lda,
              float *d_B, int ldb, float *d_C, int ldc);
int main(){
    gtod_ref_time_sec++;
    return 0;
}