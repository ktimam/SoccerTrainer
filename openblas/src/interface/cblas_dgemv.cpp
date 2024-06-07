#define CBLAS
#define ASMNAME _cblas_dgemv
#define ASMFNAME _cblas_dgemv_
#define NAME cblas_dgemv_
#define CNAME cblas_dgemv
#define CHAR_NAME "cblas_dgemv_"
#define CHAR_CNAME "cblas_dgemv"
#define DOUBLE
#include "openblas/interface/gemv.c"