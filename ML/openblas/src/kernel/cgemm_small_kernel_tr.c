#define TR
#define ASMNAME _cgemm_small_kernel_tr
#define ASMFNAME _cgemm_small_kernel_tr_
#define NAME cgemm_small_kernel_tr_
#define CNAME cgemm_small_kernel_tr
#define CHAR_NAME "cgemm_small_kernel_tr_"
#define CHAR_CNAME "cgemm_small_kernel_tr"
#define COMPLEX
#include "kernel/x86_64/../generic/zgemm_small_matrix_kernel_tn.c"