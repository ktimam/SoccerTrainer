/*********************************************************************/
/* Copyright 2009, 2010 The University of Texas at Austin.           */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/*   1. Redistributions of source code must retain the above         */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer.                                                  */
/*                                                                   */
/*   2. Redistributions in binary form must reproduce the above      */
/*      copyright notice, this list of conditions and the following  */
/*      disclaimer in the documentation and/or other materials       */
/*      provided with the distribution.                              */
/*                                                                   */
/*    THIS  SOFTWARE IS PROVIDED  BY THE  UNIVERSITY OF  TEXAS AT    */
/*    AUSTIN  ``AS IS''  AND ANY  EXPRESS OR  IMPLIED WARRANTIES,    */
/*    INCLUDING, BUT  NOT LIMITED  TO, THE IMPLIED  WARRANTIES OF    */
/*    MERCHANTABILITY  AND FITNESS FOR  A PARTICULAR  PURPOSE ARE    */
/*    DISCLAIMED.  IN  NO EVENT SHALL THE UNIVERSITY  OF TEXAS AT    */
/*    AUSTIN OR CONTRIBUTORS BE  LIABLE FOR ANY DIRECT, INDIRECT,    */
/*    INCIDENTAL,  SPECIAL, EXEMPLARY,  OR  CONSEQUENTIAL DAMAGES    */
/*    (INCLUDING, BUT  NOT LIMITED TO,  PROCUREMENT OF SUBSTITUTE    */
/*    GOODS  OR  SERVICES; LOSS  OF  USE,  DATA,  OR PROFITS;  OR    */
/*    BUSINESS INTERRUPTION) HOWEVER CAUSED  AND ON ANY THEORY OF    */
/*    LIABILITY, WHETHER  IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*    (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY WAY OUT    */
/*    OF  THE  USE OF  THIS  SOFTWARE,  EVEN  IF ADVISED  OF  THE    */
/*    POSSIBILITY OF SUCH DAMAGE.                                    */
/*                                                                   */
/* The views and conclusions contained in the software and           */
/* documentation are those of the authors and should not be          */
/* interpreted as representing official policies, either expressed   */
/* or implied, of The University of Texas at Austin.                 */
/*********************************************************************/

#ifndef ASSEMBLER

/* Level 2 Blas routines */

#ifdef __CUDACC__
extern "C" {
#endif

int sbgemv_n(BLASLONG, BLASLONG, float, bfloat16 *, BLASLONG, bfloat16 *, BLASLONG, float, float *, BLASLONG);
int sbgemv_t(BLASLONG, BLASLONG, float, bfloat16 *, BLASLONG, bfloat16 *, BLASLONG, float, float *, BLASLONG);
int sbgemv_thread_n(BLASLONG, BLASLONG, float, bfloat16 *, BLASLONG, bfloat16 *, BLASLONG, float, float *, BLASLONG, int);
int sbgemv_thread_t(BLASLONG, BLASLONG, float, bfloat16 *, BLASLONG, bfloat16 *, BLASLONG, float, float *, BLASLONG, int);
int sger_k (BLASLONG, BLASLONG, BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int dger_k (BLASLONG, BLASLONG, BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int qger_k (BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int cgeru_k(BLASLONG, BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int cgerc_k(BLASLONG, BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int cgerv_k(BLASLONG, BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int cgerd_k(BLASLONG, BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int zgeru_k(BLASLONG, BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int zgerc_k(BLASLONG, BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int zgerv_k(BLASLONG, BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int zgerd_k(BLASLONG, BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int xgeru_k(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xgerc_k(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xgerv_k(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xgerd_k(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);

int sger_thread  (BLASLONG, BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int dger_thread  (BLASLONG, BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int qger_thread  (BLASLONG, BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int cger_thread_U(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int cger_thread_C(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int cger_thread_V(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int cger_thread_D(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int zger_thread_U(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zger_thread_C(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zger_thread_V(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zger_thread_D(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int xger_thread_U(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xger_thread_C(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xger_thread_V(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xger_thread_D(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int sgemv_n(BLASLONG, BLASLONG, BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int sgemv_t(BLASLONG, BLASLONG, BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int dgemv_n(BLASLONG, BLASLONG, BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dgemv_t(BLASLONG, BLASLONG, BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int qgemv_n(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer);
int qgemv_t(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer);

int cgemv_n(BLASLONG, BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int cgemv_t(BLASLONG, BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int cgemv_r(BLASLONG, BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int cgemv_c(BLASLONG, BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int cgemv_o(BLASLONG, BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int cgemv_u(BLASLONG, BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int cgemv_s(BLASLONG, BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int cgemv_d(BLASLONG, BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);

int zgemv_n(BLASLONG, BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zgemv_t(BLASLONG, BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zgemv_r(BLASLONG, BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zgemv_c(BLASLONG, BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zgemv_o(BLASLONG, BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zgemv_u(BLASLONG, BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zgemv_s(BLASLONG, BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zgemv_d(BLASLONG, BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);

int xgemv_n(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer);
int xgemv_t(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer);
int xgemv_r(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer);
int xgemv_c(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer);
int xgemv_o(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer);
int xgemv_u(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer);
int xgemv_s(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer);
int xgemv_d(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer);

int sgemv_thread_n(BLASLONG, BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int sgemv_thread_t(BLASLONG, BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int dgemv_thread_n(BLASLONG, BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int dgemv_thread_t(BLASLONG, BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int qgemv_thread_n(BLASLONG, BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int qgemv_thread_t(BLASLONG, BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);

int cgemv_thread_n(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgemv_thread_t(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgemv_thread_r(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgemv_thread_c(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgemv_thread_o(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgemv_thread_u(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgemv_thread_s(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgemv_thread_d(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);

int zgemv_thread_n(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgemv_thread_t(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgemv_thread_r(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgemv_thread_c(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgemv_thread_o(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgemv_thread_u(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgemv_thread_s(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgemv_thread_d(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);

int xgemv_thread_n(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgemv_thread_t(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgemv_thread_r(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgemv_thread_c(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgemv_thread_o(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgemv_thread_u(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgemv_thread_s(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgemv_thread_d(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);

int strsv_NUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int strsv_NUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int strsv_NLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int strsv_NLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int strsv_TUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int strsv_TUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int strsv_TLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int strsv_TLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);

int dtrsv_NUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtrsv_NUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtrsv_NLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtrsv_NLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtrsv_TUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtrsv_TUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtrsv_TLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtrsv_TLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);

int qtrsv_NUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtrsv_NUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtrsv_NLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtrsv_NLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtrsv_TUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtrsv_TUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtrsv_TLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtrsv_TLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);

int ctrsv_NUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_NUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_NLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_NLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_TUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_TUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_TLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_TLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_RUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_RUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_RLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_RLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_CUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_CUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_CLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctrsv_CLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);

int ztrsv_NUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_NUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_NLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_NLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_TUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_TUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_TLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_TLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_RUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_RUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_RLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_RLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_CUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_CUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_CLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztrsv_CLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);

int xtrsv_NUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_NUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_NLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_NLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_TUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_TUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_TLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_TLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_RUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_RUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_RLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_RLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_CUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_CUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_CLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtrsv_CLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);

int strmv_NUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int strmv_NUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int strmv_NLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int strmv_NLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int strmv_TUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int strmv_TUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int strmv_TLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int strmv_TLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);

int dtrmv_NUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int dtrmv_NUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int dtrmv_NLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int dtrmv_NLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int dtrmv_TUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int dtrmv_TUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int dtrmv_TLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int dtrmv_TLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);

int qtrmv_NUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int qtrmv_NUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int qtrmv_NLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int qtrmv_NLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int qtrmv_TUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int qtrmv_TUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int qtrmv_TLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int qtrmv_TLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);

int ctrmv_NUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_NUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_NLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_NLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_TUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_TUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_TLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_TLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_RUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_RUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_RLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_RLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_CUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_CUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_CLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ctrmv_CLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);

int ztrmv_NUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_NUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_NLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_NLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_TUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_TUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_TLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_TLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_RUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_RUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_RLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_RLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_CUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_CUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_CLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int ztrmv_CLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);

int xtrmv_NUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_NUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_NLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_NLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_TUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_TUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_TLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_TLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_RUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_RUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_RLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_RLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_CUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_CUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_CLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xtrmv_CLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);

int strmv_thread_NUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int strmv_thread_NUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int strmv_thread_NLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int strmv_thread_NLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int strmv_thread_TUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int strmv_thread_TUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int strmv_thread_TLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int strmv_thread_TLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);

int dtrmv_thread_NUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtrmv_thread_NUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtrmv_thread_NLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtrmv_thread_NLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtrmv_thread_TUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtrmv_thread_TUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtrmv_thread_TLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtrmv_thread_TLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);

int qtrmv_thread_NUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtrmv_thread_NUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtrmv_thread_NLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtrmv_thread_NLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtrmv_thread_TUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtrmv_thread_TUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtrmv_thread_TLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtrmv_thread_TLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int ctrmv_thread_NUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_NUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_NLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_NLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_TUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_TUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_TLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_TLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_RUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_RUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_RLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_RLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_CUU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_CUN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_CLU(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctrmv_thread_CLN(BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);

int ztrmv_thread_NUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_NUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_NLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_NLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_TUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_TUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_TLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_TLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_RUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_RUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_RLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_RLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_CUU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_CUN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_CLU(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztrmv_thread_CLN(BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);

int xtrmv_thread_NUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_NUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_NLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_NLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_TUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_TUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_TLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_TLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_RUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_RUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_RLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_RLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_CUU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_CUN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_CLU(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtrmv_thread_CLN(BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int stpsv_NUU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpsv_NUN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpsv_NLU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpsv_NLN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpsv_TUU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpsv_TUN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpsv_TLU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpsv_TLN(BLASLONG, float *, float *, BLASLONG, float *buffer);

int dtpsv_NUU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpsv_NUN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpsv_NLU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpsv_NLN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpsv_TUU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpsv_TUN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpsv_TLU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpsv_TLN(BLASLONG, double *, double *, BLASLONG, float *buffer);

int qtpsv_NUU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpsv_NUN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpsv_NLU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpsv_NLN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpsv_TUU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpsv_TUN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpsv_TLU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpsv_TLN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);

int ctpsv_NUU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_NUN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_NLU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_NLN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_TUU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_TUN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_TLU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_TLN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_RUU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_RUN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_RLU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_RLN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_CUU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_CUN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_CLU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpsv_CLN(BLASLONG, float *, float *, BLASLONG, float *buffer);

int ztpsv_NUU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_NUN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_NLU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_NLN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_TUU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_TUN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_TLU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_TLN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_RUU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_RUN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_RLU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_RLN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_CUU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_CUN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_CLU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpsv_CLN(BLASLONG, double *, double *, BLASLONG, float *buffer);

int xtpsv_NUU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_NUN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_NLU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_NLN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_TUU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_TUN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_TLU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_TLN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_RUU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_RUN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_RLU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_RLN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_CUU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_CUN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_CLU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpsv_CLN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);

int stpmv_NUU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpmv_NUN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpmv_NLU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpmv_NLN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpmv_TUU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpmv_TUN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpmv_TLU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int stpmv_TLN(BLASLONG, float *, float *, BLASLONG, float *buffer);

int dtpmv_NUU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpmv_NUN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpmv_NLU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpmv_NLN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpmv_TUU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpmv_TUN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpmv_TLU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int dtpmv_TLN(BLASLONG, double *, double *, BLASLONG, float *buffer);

int qtpmv_NUU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpmv_NUN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpmv_NLU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpmv_NLN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpmv_TUU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpmv_TUN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpmv_TLU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int qtpmv_TLN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);

int ctpmv_NUU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_NUN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_NLU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_NLN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_TUU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_TUN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_TLU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_TLN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_RUU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_RUN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_RLU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_RLN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_CUU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_CUN(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_CLU(BLASLONG, float *, float *, BLASLONG, float *buffer);
int ctpmv_CLN(BLASLONG, float *, float *, BLASLONG, float *buffer);

int ztpmv_NUU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_NUN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_NLU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_NLN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_TUU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_TUN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_TLU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_TLN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_RUU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_RUN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_RLU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_RLN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_CUU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_CUN(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_CLU(BLASLONG, double *, double *, BLASLONG, float *buffer);
int ztpmv_CLN(BLASLONG, double *, double *, BLASLONG, float *buffer);

int xtpmv_NUU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_NUN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_NLU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_NLN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_TUU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_TUN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_TLU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_TLN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_RUU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_RUN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_RLU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_RLN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_CUU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_CUN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_CLU(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);
int xtpmv_CLN(BLASLONG, xdouble *, xdouble *, BLASLONG, float *buffer);

int stpmv_thread_NUU(BLASLONG, float *, float *, BLASLONG, float *, int);
int stpmv_thread_NUN(BLASLONG, float *, float *, BLASLONG, float *, int);
int stpmv_thread_NLU(BLASLONG, float *, float *, BLASLONG, float *, int);
int stpmv_thread_NLN(BLASLONG, float *, float *, BLASLONG, float *, int);
int stpmv_thread_TUU(BLASLONG, float *, float *, BLASLONG, float *, int);
int stpmv_thread_TUN(BLASLONG, float *, float *, BLASLONG, float *, int);
int stpmv_thread_TLU(BLASLONG, float *, float *, BLASLONG, float *, int);
int stpmv_thread_TLN(BLASLONG, float *, float *, BLASLONG, float *, int);

int dtpmv_thread_NUU(BLASLONG, double *, double *, BLASLONG, double *, int);
int dtpmv_thread_NUN(BLASLONG, double *, double *, BLASLONG, double *, int);
int dtpmv_thread_NLU(BLASLONG, double *, double *, BLASLONG, double *, int);
int dtpmv_thread_NLN(BLASLONG, double *, double *, BLASLONG, double *, int);
int dtpmv_thread_TUU(BLASLONG, double *, double *, BLASLONG, double *, int);
int dtpmv_thread_TUN(BLASLONG, double *, double *, BLASLONG, double *, int);
int dtpmv_thread_TLU(BLASLONG, double *, double *, BLASLONG, double *, int);
int dtpmv_thread_TLN(BLASLONG, double *, double *, BLASLONG, double *, int);

int qtpmv_thread_NUU(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int qtpmv_thread_NUN(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int qtpmv_thread_NLU(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int qtpmv_thread_NLN(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int qtpmv_thread_TUU(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int qtpmv_thread_TUN(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int qtpmv_thread_TLU(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int qtpmv_thread_TLN(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);

int ctpmv_thread_NUU(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_NUN(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_NLU(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_NLN(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_TUU(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_TUN(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_TLU(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_TLN(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_RUU(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_RUN(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_RLU(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_RLN(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_CUU(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_CUN(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_CLU(BLASLONG, float *, float *, BLASLONG, float *, int);
int ctpmv_thread_CLN(BLASLONG, float *, float *, BLASLONG, float *, int);

int ztpmv_thread_NUU(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_NUN(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_NLU(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_NLN(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_TUU(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_TUN(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_TLU(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_TLN(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_RUU(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_RUN(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_RLU(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_RLN(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_CUU(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_CUN(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_CLU(BLASLONG, double *, double *, BLASLONG, double *, int);
int ztpmv_thread_CLN(BLASLONG, double *, double *, BLASLONG, double *, int);

int xtpmv_thread_NUU(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_NUN(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_NLU(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_NLN(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_TUU(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_TUN(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_TLU(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_TLN(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_RUU(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_RUN(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_RLU(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_RLN(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_CUU(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_CUN(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_CLU(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);
int xtpmv_thread_CLN(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, int);

int ssymv_L(BLASLONG, BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ssymv_U(BLASLONG, BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int dsymv_L(BLASLONG, BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int dsymv_U(BLASLONG, BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int qsymv_L(BLASLONG, BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int qsymv_U(BLASLONG, BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int csymv_L(BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int csymv_U(BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int zsymv_L(BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int zsymv_U(BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int xsymv_L(BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xsymv_U(BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);

int ssymv_thread_L(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ssymv_thread_U(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int dsymv_thread_L(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dsymv_thread_U(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int qsymv_thread_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qsymv_thread_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int csymv_thread_L(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int csymv_thread_U(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int zsymv_thread_L(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zsymv_thread_U(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int xsymv_thread_L(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xsymv_thread_U(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int chemv_thread_L(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int chemv_thread_U(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int chemv_thread_M(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int chemv_thread_V(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int zhemv_thread_L(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zhemv_thread_U(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zhemv_thread_M(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zhemv_thread_V(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int xhemv_thread_L(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xhemv_thread_U(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xhemv_thread_M(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xhemv_thread_V(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int sspmv_L(BLASLONG, float, float *, float *, BLASLONG, float *, BLASLONG, float *buffer);
int sspmv_U(BLASLONG, float, float *, float *, BLASLONG, float *, BLASLONG, float *buffer);
int dspmv_L(BLASLONG, double, double *, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dspmv_U(BLASLONG, double, double *, double *, BLASLONG, double *, BLASLONG, float *buffer);
int qspmv_L(BLASLONG, xdouble, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qspmv_U(BLASLONG, xdouble, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int cspmv_L(BLASLONG, float, float, float *, float *, BLASLONG, float *, BLASLONG, float *buffer);
int cspmv_U(BLASLONG, float, float, float *, float *, BLASLONG, float *, BLASLONG, float *buffer);
int zspmv_L(BLASLONG, double, double, double *, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zspmv_U(BLASLONG, double, double, double *, double *, BLASLONG, double *, BLASLONG, float *buffer);
int xspmv_L(BLASLONG, xdouble, xdouble, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xspmv_U(BLASLONG, xdouble, xdouble, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);

int sspmv_thread_L(BLASLONG, float, float *, float *, BLASLONG, float *, BLASLONG, float *, int);
int sspmv_thread_U(BLASLONG, float, float *, float *, BLASLONG, float *, BLASLONG, float *, int);
int dspmv_thread_L(BLASLONG, double, double *, double *, BLASLONG, double *, BLASLONG, double *, int);
int dspmv_thread_U(BLASLONG, double, double *, double *, BLASLONG, double *, BLASLONG, double *, int);
int qspmv_thread_L(BLASLONG, xdouble, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qspmv_thread_U(BLASLONG, xdouble, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int cspmv_thread_L(BLASLONG, float *, float *, float *, BLASLONG, float *, BLASLONG, float *, int);
int cspmv_thread_U(BLASLONG, float *, float *, float *, BLASLONG, float *, BLASLONG, float *, int);
int zspmv_thread_L(BLASLONG, double *, double *, double *, BLASLONG, double *, BLASLONG, double *, int);
int zspmv_thread_U(BLASLONG, double *, double *, double *, BLASLONG, double *, BLASLONG, double *, int);
int xspmv_thread_L(BLASLONG, xdouble *, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xspmv_thread_U(BLASLONG, xdouble *, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int ssyr_L(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *);
int ssyr_U(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *);
int dsyr_L(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *);
int dsyr_U(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *);
int qsyr_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int qsyr_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int csyr_L(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *);
int csyr_U(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *);
int zsyr_L(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *);
int zsyr_U(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *);
int xsyr_L(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xsyr_U(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);

int ssyr_thread_L(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, int);
int ssyr_thread_U(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, int);
int dsyr_thread_L(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, int);
int dsyr_thread_U(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, int);
int qsyr_thread_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qsyr_thread_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int csyr_thread_L(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, int);
int csyr_thread_U(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, int);
int zsyr_thread_L(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, int);
int zsyr_thread_U(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, int);
int xsyr_thread_L(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xsyr_thread_U(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int ssyr2_L(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int ssyr2_U(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int dsyr2_L(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int dsyr2_U(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int qsyr2_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int qsyr2_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int csyr2_L(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int csyr2_U(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int zsyr2_L(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int zsyr2_U(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int xsyr2_L(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xsyr2_U(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);

int ssyr2_thread_L(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ssyr2_thread_U(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int dsyr2_thread_L(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dsyr2_thread_U(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int qsyr2_thread_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qsyr2_thread_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int csyr2_thread_L(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int csyr2_thread_U(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int zsyr2_thread_L(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zsyr2_thread_U(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int xsyr2_thread_L(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xsyr2_thread_U(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int sspr_L(BLASLONG, float, float *, BLASLONG, float *, float *);
int sspr_U(BLASLONG, float, float *, BLASLONG, float *, float *);
int dspr_L(BLASLONG, double, double *, BLASLONG, double *, double *);
int dspr_U(BLASLONG, double, double *, BLASLONG, double *, double *);
int qspr_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *);
int qspr_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *);
int cspr_L(BLASLONG, float, float, float *, BLASLONG, float *, float *);
int cspr_U(BLASLONG, float, float, float *, BLASLONG, float *, float *);
int zspr_L(BLASLONG, double, double, double *, BLASLONG, double *, double *);
int zspr_U(BLASLONG, double, double, double *, BLASLONG, double *, double *);
int xspr_L(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *);
int xspr_U(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *);

int sspr_thread_L(BLASLONG, float, float *, BLASLONG, float *, float *, int);
int sspr_thread_U(BLASLONG, float, float *, BLASLONG, float *, float *, int);
int dspr_thread_L(BLASLONG, double, double *, BLASLONG, double *, double *, int);
int dspr_thread_U(BLASLONG, double, double *, BLASLONG, double *, double *, int);
int qspr_thread_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *, int);
int qspr_thread_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *, int);
int cspr_thread_L(BLASLONG, float *, float *, BLASLONG, float *, float *, int);
int cspr_thread_U(BLASLONG, float *, float *, BLASLONG, float *, float *, int);
int zspr_thread_L(BLASLONG, double *, double *, BLASLONG, double *, double *, int);
int zspr_thread_U(BLASLONG, double *, double *, BLASLONG, double *, double *, int);
int xspr_thread_L(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, xdouble *, int);
int xspr_thread_U(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, xdouble *, int);

int sspr2_L(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, float *);
int sspr2_U(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, float *);
int dspr2_L(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, double *);
int dspr2_U(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, double *);
int qspr2_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *);
int qspr2_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *);
int cspr2_L(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, float *);
int cspr2_U(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, float *);
int zspr2_L(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, double *);
int zspr2_U(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, double *);
int xspr2_L(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *);
int xspr2_U(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *);

int sspr2_thread_L(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, float *, int);
int sspr2_thread_U(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, float *, int);
int dspr2_thread_L(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, double *, int);
int dspr2_thread_U(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, double *, int);
int qspr2_thread_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *, int);
int qspr2_thread_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *, int);
int cspr2_thread_L(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, float *, int);
int cspr2_thread_U(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, float *, int);
int zspr2_thread_L(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, double *, int);
int zspr2_thread_U(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, double *, int);
int xspr2_thread_L(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *, int);
int xspr2_thread_U(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *, int);

int cher_L(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *);
int cher_U(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *);
int cher_V(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *);
int cher_M(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *);
int zher_L(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *);
int zher_U(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *);
int zher_V(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *);
int zher_M(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *);
int xher_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xher_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xher_V(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xher_M(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);

int cher_thread_L(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, int);
int cher_thread_U(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, int);
int cher_thread_V(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, int);
int cher_thread_M(BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, int);
int zher_thread_L(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, int);
int zher_thread_U(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, int);
int zher_thread_V(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, int);
int zher_thread_M(BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, int);
int xher_thread_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xher_thread_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xher_thread_V(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xher_thread_M(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int cher2_L(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int cher2_U(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int cher2_M(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int cher2_V(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int zher2_L(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int zher2_U(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int zher2_M(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int zher2_V(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int xher2_L(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xher2_U(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xher2_M(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xher2_V(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);

int cher2_thread_L(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int cher2_thread_U(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int cher2_thread_M(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int cher2_thread_V(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int zher2_thread_L(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zher2_thread_U(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zher2_thread_M(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zher2_thread_V(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int xher2_thread_L(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xher2_thread_U(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xher2_thread_M(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xher2_thread_V(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int chpr_L(BLASLONG, float, float *, BLASLONG, float *, float *);
int chpr_U(BLASLONG, float, float *, BLASLONG, float *, float *);
int chpr_M(BLASLONG, float, float *, BLASLONG, float *, float *);
int chpr_V(BLASLONG, float, float *, BLASLONG, float *, float *);
int zhpr_L(BLASLONG, double, double *, BLASLONG, double *, double *);
int zhpr_U(BLASLONG, double, double *, BLASLONG, double *, double *);
int zhpr_M(BLASLONG, double, double *, BLASLONG, double *, double *);
int zhpr_V(BLASLONG, double, double *, BLASLONG, double *, double *);
int xhpr_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *);
int xhpr_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *);
int xhpr_M(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *);
int xhpr_V(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *);

int chpr_thread_L(BLASLONG, float, float *, BLASLONG, float *, float *, int);
int chpr_thread_U(BLASLONG, float, float *, BLASLONG, float *, float *, int);
int chpr_thread_M(BLASLONG, float, float *, BLASLONG, float *, float *, int);
int chpr_thread_V(BLASLONG, float, float *, BLASLONG, float *, float *, int);
int zhpr_thread_L(BLASLONG, double, double *, BLASLONG, double *, double *, int);
int zhpr_thread_U(BLASLONG, double, double *, BLASLONG, double *, double *, int);
int zhpr_thread_M(BLASLONG, double, double *, BLASLONG, double *, double *, int);
int zhpr_thread_V(BLASLONG, double, double *, BLASLONG, double *, double *, int);
int xhpr_thread_L(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *, int);
int xhpr_thread_U(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *, int);
int xhpr_thread_M(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *, int);
int xhpr_thread_V(BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, xdouble *, int);

int chpr2_L(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, float *);
int chpr2_U(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, float *);
int chpr2_M(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, float *);
int chpr2_V(BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, float *);
int zhpr2_L(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, double *);
int zhpr2_U(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, double *);
int zhpr2_M(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, double *);
int zhpr2_V(BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, double *);
int xhpr2_L(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *);
int xhpr2_U(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *);
int xhpr2_M(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *);
int xhpr2_V(BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *);

int chpr2_thread_L(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, float *, int);
int chpr2_thread_U(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, float *, int);
int chpr2_thread_M(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, float *, int);
int chpr2_thread_V(BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, float *, int);
int zhpr2_thread_L(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, double *, int);
int zhpr2_thread_U(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, double *, int);
int zhpr2_thread_M(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, double *, int);
int zhpr2_thread_V(BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, double *, int);
int xhpr2_thread_L(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *, int);
int xhpr2_thread_U(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *, int);
int xhpr2_thread_M(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *, int);
int xhpr2_thread_V(BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, xdouble *, int);

int chemv_L(BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int chemv_U(BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int chemv_M(BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int chemv_V(BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *);
int zhemv_L(BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int zhemv_U(BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int zhemv_M(BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int zhemv_V(BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *);
int xhemv_L(BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xhemv_U(BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xhemv_M(BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);
int xhemv_V(BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *);

int chpmv_L(BLASLONG, float, float, float *, float *, BLASLONG, float *, BLASLONG, float *buffer);
int chpmv_U(BLASLONG, float, float, float *, float *, BLASLONG, float *, BLASLONG, float *buffer);
int chpmv_M(BLASLONG, float, float, float *, float *, BLASLONG, float *, BLASLONG, float *buffer);
int chpmv_V(BLASLONG, float, float, float *, float *, BLASLONG, float *, BLASLONG, float *buffer);
int zhpmv_L(BLASLONG, double, double, double *, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zhpmv_U(BLASLONG, double, double, double *, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zhpmv_M(BLASLONG, double, double, double *, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zhpmv_V(BLASLONG, double, double, double *, double *, BLASLONG, double *, BLASLONG, float *buffer);
int xhpmv_L(BLASLONG, xdouble, xdouble, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xhpmv_U(BLASLONG, xdouble, xdouble, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xhpmv_M(BLASLONG, xdouble, xdouble, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xhpmv_V(BLASLONG, xdouble, xdouble, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);

int chpmv_thread_L(BLASLONG, float *, float *, float *, BLASLONG, float *, BLASLONG, float *, int);
int chpmv_thread_U(BLASLONG, float *, float *, float *, BLASLONG, float *, BLASLONG, float *, int);
int chpmv_thread_M(BLASLONG, float *, float *, float *, BLASLONG, float *, BLASLONG, float *, int);
int chpmv_thread_V(BLASLONG, float *, float *, float *, BLASLONG, float *, BLASLONG, float *, int);
int zhpmv_thread_L(BLASLONG, double *, double *, double *, BLASLONG, double *, BLASLONG, double *, int);
int zhpmv_thread_U(BLASLONG, double *, double *, double *, BLASLONG, double *, BLASLONG, double *, int);
int zhpmv_thread_M(BLASLONG, double *, double *, double *, BLASLONG, double *, BLASLONG, double *, int);
int zhpmv_thread_V(BLASLONG, double *, double *, double *, BLASLONG, double *, BLASLONG, double *, int);
int xhpmv_thread_L(BLASLONG, xdouble *, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xhpmv_thread_U(BLASLONG, xdouble *, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xhpmv_thread_M(BLASLONG, xdouble *, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xhpmv_thread_V(BLASLONG, xdouble *, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int ssbmv_L(BLASLONG, BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ssbmv_U(BLASLONG, BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int dsbmv_L(BLASLONG, BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dsbmv_U(BLASLONG, BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int qsbmv_L(BLASLONG, BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qsbmv_U(BLASLONG, BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int csbmv_L(BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int csbmv_U(BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int zsbmv_L(BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zsbmv_U(BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int xsbmv_L(BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xsbmv_U(BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);

int chbmv_L(BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int chbmv_U(BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int chbmv_M(BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int chbmv_V(BLASLONG, BLASLONG, float, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int zhbmv_L(BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zhbmv_U(BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zhbmv_M(BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int zhbmv_V(BLASLONG, BLASLONG, double, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int xhbmv_L(BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xhbmv_U(BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xhbmv_M(BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xhbmv_V(BLASLONG, BLASLONG, xdouble, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);


int ssbmv_thread_L(BLASLONG, BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ssbmv_thread_U(BLASLONG, BLASLONG, float, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int dsbmv_thread_L(BLASLONG, BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dsbmv_thread_U(BLASLONG, BLASLONG, double, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int qsbmv_thread_L(BLASLONG, BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qsbmv_thread_U(BLASLONG, BLASLONG, xdouble, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int csbmv_thread_L(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int csbmv_thread_U(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int zsbmv_thread_L(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zsbmv_thread_U(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int xsbmv_thread_L(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xsbmv_thread_U(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int chbmv_thread_L(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int chbmv_thread_U(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int chbmv_thread_M(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int chbmv_thread_V(BLASLONG, BLASLONG, float *, float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int zhbmv_thread_L(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zhbmv_thread_U(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zhbmv_thread_M(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int zhbmv_thread_V(BLASLONG, BLASLONG, double *, double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int xhbmv_thread_L(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xhbmv_thread_U(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xhbmv_thread_M(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xhbmv_thread_V(BLASLONG, BLASLONG, xdouble *, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int snorm_n(BLASLONG, BLASLONG, float *a, BLASLONG);
int snorm_t(BLASLONG, BLASLONG, float *a, BLASLONG);
int dnorm_n(BLASLONG, BLASLONG, double *a, BLASLONG);
int dnorm_t(BLASLONG, BLASLONG, double *a, BLASLONG);
int cnorm_n(BLASLONG, BLASLONG, float *a, BLASLONG);
int cnorm_t(BLASLONG, BLASLONG, float *a, BLASLONG);
int znorm_n(BLASLONG, BLASLONG, double *a, BLASLONG);
int znorm_t(BLASLONG, BLASLONG, double *a, BLASLONG);

void sgbmv_n(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
void sgbmv_t(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);

void dgbmv_n(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
void dgbmv_t(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);

void qgbmv_n(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
void qgbmv_t(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);

void cgbmv_n(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float, float,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
void cgbmv_t(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float, float,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
void cgbmv_r(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float, float,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
void cgbmv_c(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float, float,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
void cgbmv_o(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float, float,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
void cgbmv_u(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float, float,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
void cgbmv_s(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float, float,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
void cgbmv_d(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float, float,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);

void zgbmv_n(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double, double,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
void zgbmv_t(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double, double,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
void zgbmv_r(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double, double,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
void zgbmv_c(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double, double,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
void zgbmv_o(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double, double,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
void zgbmv_u(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double, double,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
void zgbmv_s(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double, double,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
void zgbmv_d(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double, double,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);

void xgbmv_n(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
void xgbmv_t(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
void xgbmv_r(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
void xgbmv_c(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
void xgbmv_o(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
void xgbmv_u(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
void xgbmv_s(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
void xgbmv_d(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);

int sgbmv_thread_n(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int sgbmv_thread_t(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);

int dgbmv_thread_n(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int dgbmv_thread_t(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);

int qgbmv_thread_n(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int qgbmv_thread_t(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);

int cgbmv_thread_n(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float *,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgbmv_thread_t(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float *,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgbmv_thread_r(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float *,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgbmv_thread_c(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float *,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgbmv_thread_o(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float *,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgbmv_thread_u(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float *,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgbmv_thread_s(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float *,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);
int cgbmv_thread_d(BLASLONG, BLASLONG, BLASLONG, BLASLONG, float *,
		 float *, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer, int);

int zgbmv_thread_n(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double *,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgbmv_thread_t(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double *,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgbmv_thread_r(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double *,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgbmv_thread_c(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double *,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgbmv_thread_o(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double *,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgbmv_thread_u(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double *,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgbmv_thread_s(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double *,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);
int zgbmv_thread_d(BLASLONG, BLASLONG, BLASLONG, BLASLONG, double *,
		 double *, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *buffer, int);

int xgbmv_thread_n(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble *,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgbmv_thread_t(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble *,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgbmv_thread_r(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble *,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgbmv_thread_c(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble *,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgbmv_thread_o(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble *,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgbmv_thread_u(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble *,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgbmv_thread_s(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble *,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);
int xgbmv_thread_d(BLASLONG, BLASLONG, BLASLONG, BLASLONG, xdouble *,
		 xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *buffer, int);

int stbmv_NUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbmv_NUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbmv_NLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbmv_NLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbmv_TUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbmv_TUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbmv_TLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbmv_TLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);

int dtbmv_NUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbmv_NUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbmv_NLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbmv_NLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbmv_TUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbmv_TUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbmv_TLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbmv_TLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);

int qtbmv_NUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbmv_NUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbmv_NLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbmv_NLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbmv_TUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbmv_TUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbmv_TLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbmv_TLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);

int ctbmv_NUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_NUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_NLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_NLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_TUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_TUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_TLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_TLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_RUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_RUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_RLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_RLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_CUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_CUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_CLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbmv_CLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);

int ztbmv_NUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_NUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_NLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_NLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_TUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_TUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_TLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_TLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_RUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_RUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_RLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_RLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_CUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_CUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_CLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbmv_CLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);

int xtbmv_NUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_NUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_NLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_NLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_TUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_TUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_TLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_TLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_RUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_RUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_RLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_RLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_CUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_CUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_CLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbmv_CLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);

int stbmv_thread_NUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int stbmv_thread_NUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int stbmv_thread_NLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int stbmv_thread_NLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int stbmv_thread_TUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int stbmv_thread_TUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int stbmv_thread_TLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int stbmv_thread_TLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);

int dtbmv_thread_NUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtbmv_thread_NUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtbmv_thread_NLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtbmv_thread_NLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtbmv_thread_TUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtbmv_thread_TUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtbmv_thread_TLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int dtbmv_thread_TLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);

int qtbmv_thread_NUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtbmv_thread_NUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtbmv_thread_NLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtbmv_thread_NLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtbmv_thread_TUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtbmv_thread_TUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtbmv_thread_TLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int qtbmv_thread_TLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int ctbmv_thread_NUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_NUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_NLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_NLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_TUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_TUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_TLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_TLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_RUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_RUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_RLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_RLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_CUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_CUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_CLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);
int ctbmv_thread_CLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *, int);

int ztbmv_thread_NUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_NUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_NLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_NLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_TUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_TUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_TLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_TLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_RUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_RUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_RLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_RLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_CUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_CUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_CLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);
int ztbmv_thread_CLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, double *, int);

int xtbmv_thread_NUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_NUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_NLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_NLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_TUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_TUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_TLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_TLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_RUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_RUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_RLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_RLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_CUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_CUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_CLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);
int xtbmv_thread_CLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, xdouble *, int);

int stbsv_NUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbsv_NUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbsv_NLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbsv_NLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbsv_TUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbsv_TUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbsv_TLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int stbsv_TLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);

int dtbsv_NUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbsv_NUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbsv_NLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbsv_NLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbsv_TUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbsv_TUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbsv_TLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int dtbsv_TLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);

int qtbsv_NUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbsv_NUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbsv_NLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbsv_NLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbsv_TUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbsv_TUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbsv_TLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int qtbsv_TLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);

int ctbsv_NUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_NUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_NLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_NLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_TUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_TUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_TLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_TLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_RUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_RUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_RLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_RLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_CUU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_CUN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_CLU(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);
int ctbsv_CLN(BLASLONG, BLASLONG, float *, BLASLONG, float *, BLASLONG, float *buffer);

int ztbsv_NUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_NUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_NLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_NLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_TUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_TUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_TLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_TLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_RUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_RUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_RLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_RLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_CUU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_CUN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_CLU(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);
int ztbsv_CLN(BLASLONG, BLASLONG, double *, BLASLONG, double *, BLASLONG, float *buffer);

int xtbsv_NUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_NUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_NLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_NLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_TUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_TUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_TLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_TLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_RUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_RUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_RLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_RLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_CUU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_CUN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_CLU(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);
int xtbsv_CLN(BLASLONG, BLASLONG, xdouble *, BLASLONG, xdouble *, BLASLONG, float *buffer);

#ifdef __CUDACC__
}
#endif

#endif
