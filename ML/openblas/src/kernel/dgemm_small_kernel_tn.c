#define ASMNAME _dgemm_small_kernel_tn
#define ASMFNAME _dgemm_small_kernel_tn_
#define NAME dgemm_small_kernel_tn_
#define CNAME dgemm_small_kernel_tn
#define CHAR_NAME "dgemm_small_kernel_tn_"
#define CHAR_CNAME "dgemm_small_kernel_tn"
#define DOUBLE
#include "kernel/x86_64/../generic/gemm_small_matrix_kernel_tn.c"