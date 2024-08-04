
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

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#if !defined(unlikely)
#ifdef __GNUC__
#define unlikely(x) __builtin_expect(!!(x), 0)
#else
#define unlikely(x) (x)
#endif
#endif

#ifdef SMP_DEBUG
#   define MT_TRACE(...) fprintf(stderr, __VA_ARGS__)
#else
#   define MT_TRACE(...)
#endif

/* This is a thread implementation for Win32 lazy implementation */

/* Thread server common information */

static blas_queue_t *work_queue = NULL;
static HANDLE kickoff_event = NULL;
static CRITICAL_SECTION queue_lock;

/* We need this global for checking if initialization is finished.   */
int blas_server_avail = 0;

int blas_omp_threads_local = 1;

static void * blas_thread_buffer[MAX_CPU_NUMBER];

/* Local Variables */
static BLASULONG server_lock       = 0;

static HANDLE	    blas_threads   [MAX_CPU_NUMBER];
static DWORD	    blas_threads_id[MAX_CPU_NUMBER];
static volatile int thread_target;	// target num of live threads, volatile for cross-thread reads

//Prototypes
static void exec_threads(int , blas_queue_t *, int);
static void adjust_thread_buffers();

//
// Legacy code path
//
static void legacy_exec(void *func, int mode, blas_arg_t *args, void *sb) {

      if (!(mode & BLAS_COMPLEX)) {
#ifdef EXPRECISION
	if ((mode & BLAS_PREC) == BLAS_XDOUBLE){
	  /* REAL / Extended Double */
	  void (*afunc)(BLASLONG, BLASLONG, BLASLONG, xdouble,
			xdouble *, BLASLONG, xdouble *, BLASLONG,
			xdouble *, BLASLONG, void *) = func;

	  afunc(args -> m, args -> n, args -> k,
		((xdouble *)args -> alpha)[0],
		args -> a, args -> lda,
		args -> b, args -> ldb,
		args -> c, args -> ldc, sb);
	} else
#endif
	  if ((mode & BLAS_PREC) == BLAS_DOUBLE) {
	    /* REAL / Double */
	    void (*afunc)(BLASLONG, BLASLONG, BLASLONG, double,
			  double *, BLASLONG, double *, BLASLONG,
			  double *, BLASLONG, void *) = func;

	    afunc(args -> m, args -> n, args -> k,
		  ((double *)args -> alpha)[0],
		  args -> a, args -> lda,
		  args -> b, args -> ldb,
		  args -> c, args -> ldc, sb);
	  } else if ((mode & BLAS_PREC) == BLAS_SINGLE) {
	    /* REAL / Single */
	    void (*afunc)(BLASLONG, BLASLONG, BLASLONG, float,
			  float *, BLASLONG, float *, BLASLONG,
			  float *, BLASLONG, void *) = func;

	    afunc(args -> m, args -> n, args -> k,
		  ((float *)args -> alpha)[0],
		  args -> a, args -> lda,
		  args -> b, args -> ldb,
		  args -> c, args -> ldc, sb);
#ifdef BUILD_BFLOAT16
          } else if ((mode & BLAS_PREC) == BLAS_BFLOAT16) {
            /* REAL / BFLOAT16 */
            void (*afunc)(BLASLONG, BLASLONG, BLASLONG, bfloat16,
                          bfloat16 *, BLASLONG, bfloat16 *, BLASLONG,
                          bfloat16 *, BLASLONG, void *) = func;

            afunc(args -> m, args -> n, args -> k,
                  ((bfloat16 *)args -> alpha)[0],
                  args -> a, args -> lda,
                  args -> b, args -> ldb,
                  args -> c, args -> ldc, sb);
          } else if ((mode & BLAS_PREC) == BLAS_STOBF16) {
            /* REAL / BLAS_STOBF16 */
            void (*afunc)(BLASLONG, BLASLONG, BLASLONG, float,
                          float *, BLASLONG, bfloat16 *, BLASLONG,
                          float *, BLASLONG, void *) = func;

            afunc(args -> m, args -> n, args -> k,
                  ((float *)args -> alpha)[0],
                  args -> a, args -> lda,
                  args -> b, args -> ldb,
                  args -> c, args -> ldc, sb);
          } else if ((mode & BLAS_PREC) == BLAS_DTOBF16) {
            /* REAL / BLAS_DTOBF16 */
            void (*afunc)(BLASLONG, BLASLONG, BLASLONG, double,
                          double *, BLASLONG, bfloat16 *, BLASLONG,
                          double *, BLASLONG, void *) = func;

            afunc(args -> m, args -> n, args -> k,
                  ((double *)args -> alpha)[0],
                  args -> a, args -> lda,
                  args -> b, args -> ldb,
                  args -> c, args -> ldc, sb);
#endif
          } else {
            /* REAL / Other types in future */
	  }
      } else {
#ifdef EXPRECISION
	if ((mode & BLAS_PREC) == BLAS_XDOUBLE) {
	  /* COMPLEX / Extended Double */
	  void (*afunc)(BLASLONG, BLASLONG, BLASLONG, xdouble, xdouble,
			xdouble *, BLASLONG, xdouble *, BLASLONG,
			xdouble *, BLASLONG, void *) = func;

	  afunc(args -> m, args -> n, args -> k,
		((xdouble *)args -> alpha)[0],
		((xdouble *)args -> alpha)[1],
		args -> a, args -> lda,
		args -> b, args -> ldb,
		args -> c, args -> ldc, sb);
	} else
#endif
	  if ((mode & BLAS_PREC) == BLAS_DOUBLE) {
	    /* COMPLEX / Double */
	  void (*afunc)(BLASLONG, BLASLONG, BLASLONG, double, double,
			double *, BLASLONG, double *, BLASLONG,
			double *, BLASLONG, void *) = func;

	  afunc(args -> m, args -> n, args -> k,
		((double *)args -> alpha)[0],
		((double *)args -> alpha)[1],
		args -> a, args -> lda,
		args -> b, args -> ldb,
		args -> c, args -> ldc, sb);
	  } else if ((mode & BLAS_PREC) == BLAS_SINGLE) {
	    /* COMPLEX / Single */
	  void (*afunc)(BLASLONG, BLASLONG, BLASLONG, float, float,
			float *, BLASLONG, float *, BLASLONG,
			float *, BLASLONG, void *) = func;

	  afunc(args -> m, args -> n, args -> k,
		((float *)args -> alpha)[0],
		((float *)args -> alpha)[1],
		args -> a, args -> lda,
		args -> b, args -> ldb,
		args -> c, args -> ldc, sb);
        } else {
          /* COMPLEX / Other types in future */
        }
      }
}

//
// This is a main routine of threads. Each thread waits until job is queued.
//
static DWORD WINAPI blas_thread_server(void *arg) {

  /* Thread identifier */
  BLASLONG  cpu = (BLASLONG)arg;
  
  blas_queue_t	*queue;

  MT_TRACE("Server[%2ld] Thread is started!\n", cpu);

  while (1) {

    /* Waiting for Queue */

    MT_TRACE("Server[%2ld] Waiting for Queue.\n", cpu);

    // event raised when work is added to the queue
    WaitForSingleObject(kickoff_event, INFINITE);

    if (cpu > thread_target - 2) {
      //MT_TRACE("thread [%d] exiting.\n", cpu);
      break;	// excess thread, so worker thread exits
    }

    MT_TRACE("Server[%2ld] Got it.\n", cpu);

    EnterCriticalSection(&queue_lock);

    queue = work_queue;
    if (queue)
        work_queue = work_queue->next;

    LeaveCriticalSection(&queue_lock);

    if(queue) {

    exec_threads(cpu, queue, 0);
    } else {

        continue; //if queue == NULL
    }
    
    MT_TRACE("Server[%2ld] Finished!\n", cpu);
	
	  queue->finished = 1;
  }

  /* Shutdown procedure */

  MT_TRACE("Server[%2ld] Shutdown!\n",  cpu);

  return 0;
}

//
// Initializing routine
//
int blas_thread_init(void) {
  BLASLONG i;

  if (blas_server_avail || (blas_cpu_number <= 1)) return 0;

  LOCK_COMMAND(&server_lock);

  adjust_thread_buffers();

  MT_TRACE("Initializing Thread(Num. threads = %d)\n", blas_cpu_number);

  if (!blas_server_avail) {
    // create the kickoff Event
    kickoff_event = CreateEvent(NULL, TRUE, FALSE, NULL);

    thread_target = blas_cpu_number;

    InitializeCriticalSection(&queue_lock);

    for(i = 0; i < blas_cpu_number - 1; i++) {
	    //MT_TRACE("thread_init: creating thread [%d]\n", i);

      blas_threads[i] = CreateThread(NULL, 0,
				     blas_thread_server, (void *)i,
				     0, &blas_threads_id[i]);
    }

    blas_server_avail = 1;
  }

  UNLOCK_COMMAND(&server_lock);

  return 0;
}

//
//   User can call one of two routines.
//     exec_blas_async ... immediately returns after jobs are queued.
//     exec_blas       ... returns after jobs are finished.
//
int exec_blas_async(BLASLONG pos, blas_queue_t *queue) {

#if defined(SMP_SERVER)
  // Handle lazy re-init of the thread-pool after a POSIX fork
  // on Cygwin or as delayed init when a static library	is used
  if (unlikely(blas_server_avail == 0)) blas_thread_init();
#endif

  blas_queue_t *current;

  current = queue;

  while (current) {
    current -> position = pos;

#ifdef CONSISTENT_FPCSR
    __asm__ __volatile__ ("fnstcw %0"  : "=m" (current -> x87_mode));
    __asm__ __volatile__ ("stmxcsr %0" : "=m" (current -> sse_mode));
#endif

  	current->finished = 0;
    current = current -> next;
    pos ++;
  }

  EnterCriticalSection(&queue_lock);

  if (!work_queue)
  {
    work_queue = queue;
  }
  else
  {
	  blas_queue_t *queue_item = work_queue;

    // find the end of the work queue
    while (queue_item->next)
        queue_item = queue_item->next;

    // add new work to the end
    queue_item->next = queue;
  }

  LeaveCriticalSection(&queue_lock);

  SetEvent(kickoff_event);

  return 0;
}

//
// Join. Wait for all queued tasks to complete
//
int exec_blas_async_wait(BLASLONG num, blas_queue_t *queue) {

  MT_TRACE("Synchronization Waiting.\n");

  while (num) {
    MT_TRACE("Waiting Queue ..\n");

    while (!queue->finished)
      YIELDING;

    queue = queue->next;
    num--;
  }

  MT_TRACE("Completely Done.\n\n");

	// if work was added to the queue after this batch we can't sleep the worker threads
	// by resetting the event
	EnterCriticalSection(&queue_lock);

	if (work_queue == NULL)
		ResetEvent(kickoff_event);

	LeaveCriticalSection(&queue_lock);

	return 0;
}

//
// Execute Threads
//
int exec_blas(BLASLONG num, blas_queue_t *queue) {

#if defined(SMP_SERVER) && defined(OS_CYGWIN_NT)
  // Handle lazy re-init of the thread-pool after a POSIX fork
  if (unlikely(blas_server_avail == 0)) blas_thread_init();
#endif

#ifndef ALL_THREADED
   int (*routine)(blas_arg_t *, void *, void *, double *, double *, BLASLONG);
#endif

  if ((num <= 0) || (queue == NULL)) return 0;

  //Redirect to caller's callback routine
  if (openblas_threads_callback_) {
  int buf_index = 0, i = 0;
#ifndef USE_SIMPLE_THREADED_LEVEL3
    for (i = 0; i < num; i ++)
      queue[i].position = i;
#endif
    openblas_threads_callback_(1, (openblas_dojob_callback) exec_threads, num, sizeof(blas_queue_t), (void*) queue, buf_index);
    return 0;
  }

  if ((num > 1) && queue -> next) 
    exec_blas_async(1, queue -> next);

  routine = queue -> routine;

  if (queue -> mode & BLAS_LEGACY) {
    legacy_exec(routine, queue -> mode, queue -> args, queue -> sb);
  } else {
    if (queue -> mode & BLAS_PTHREAD) {
      void (*pthreadcompat)(void *) = queue -> routine;
      (pthreadcompat)(queue -> args);
    } else
      (routine)(queue -> args, queue -> range_m, queue -> range_n,
    		queue -> sa, queue -> sb, 0);
  }

  if ((num > 1) && queue -> next) 
    exec_blas_async_wait(num - 1, queue -> next);

  return 0;
}

//
// Shutdown procedure, but user don't have to call this routine. The
// kernel automatically kill threads.
//
int BLASFUNC(blas_thread_shutdown)(void) {

  int i;

  if (!blas_server_avail) return 0;

  LOCK_COMMAND(&server_lock);

  //Free buffers allocated for threads
  for(i=0; i<MAX_CPU_NUMBER; i++){
    if(blas_thread_buffer[i]!=NULL){
      blas_memory_free(blas_thread_buffer[i]);
      blas_thread_buffer[i]=NULL;
    }
  }

  if (blas_server_avail) {

    for (i = 0; i < blas_num_threads - 1; i++) {
      // Could also just use WaitForMultipleObjects
      DWORD wait_thread_value = WaitForSingleObject(blas_threads[i], 50);

#ifndef OS_WINDOWSSTORE
      // TerminateThread is only available with WINAPI_DESKTOP and WINAPI_SYSTEM not WINAPI_APP in UWP
      if (WAIT_OBJECT_0 != wait_thread_value) {
        TerminateThread(blas_threads[i],0);
      }
#endif

      CloseHandle(blas_threads[i]);
    }

    blas_server_avail = 0;
  }

  UNLOCK_COMMAND(&server_lock);

  return 0;
}

//
// Legacy function to set numbef of threads
//
void goto_set_num_threads(int num_threads)
{
	long i;

#if defined(SMP_SERVER) && defined(OS_CYGWIN_NT)
	// Handle lazy re-init of the thread-pool after a POSIX fork
	if (unlikely(blas_server_avail == 0)) blas_thread_init();
#endif

	if (num_threads < 1) num_threads = blas_cpu_number;

	if (num_threads > MAX_CPU_NUMBER) num_threads = MAX_CPU_NUMBER;

	if (blas_server_avail && num_threads < blas_num_threads) {
		LOCK_COMMAND(&server_lock);

		thread_target = num_threads;
		
		SetEvent(kickoff_event);

		for (i = num_threads - 1; i < blas_num_threads - 1; i++) {
			//MT_TRACE("set_num_threads: waiting on thread [%d] to quit.\n", i);

			WaitForSingleObject(blas_threads[i], INFINITE);

			//MT_TRACE("set_num_threads: thread [%d] has quit.\n", i);

			CloseHandle(blas_threads[i]);
		}

		blas_num_threads = num_threads;
		
		ResetEvent(kickoff_event);

		UNLOCK_COMMAND(&server_lock);
	}

	if (num_threads > blas_num_threads) {

		LOCK_COMMAND(&server_lock);

		thread_target = num_threads;

		  //increased_threads = 1;
	    if (!blas_server_avail) {
			// create the kickoff Event
			kickoff_event = CreateEvent(NULL, TRUE, FALSE, NULL);

			InitializeCriticalSection(&queue_lock);

			blas_server_avail = 1;
		}

		for (i = (blas_num_threads > 0) ? blas_num_threads - 1 : 0; i < num_threads - 1; i++) {
			//MT_TRACE("set_num_threads: creating thread [%d]\n", i);

			blas_threads[i] = CreateThread(NULL, 0,
				     blas_thread_server, (void *)i,
				     0, &blas_threads_id[i]);
		}

		blas_num_threads = num_threads;

		UNLOCK_COMMAND(&server_lock);
	}

	blas_cpu_number  = num_threads;
}

//
// Openblas function to set thread count
//
void openblas_set_num_threads(int num)
{
	goto_set_num_threads(num);
}

static void adjust_thread_buffers() {

  int i=0;

  //adjust buffer for each thread
  for(i=0; i < blas_cpu_number; i++){
    if(blas_thread_buffer[i] == NULL){
      blas_thread_buffer[i] = blas_memory_alloc(2);
    }
  }
  for(; i < MAX_CPU_NUMBER; i++){
    if(blas_thread_buffer[i] != NULL){
      blas_memory_free(blas_thread_buffer[i]);
      blas_thread_buffer[i] = NULL;
    }
  }
}

//Indivitual threads work executor, Helps in setting by synchronization environment and calling inner_threads routine
static void exec_threads(int cpu, blas_queue_t *queue, int buf_index) {
  
  void *buffer, *sa, *sb;
  
  buffer = blas_thread_buffer[cpu];
  sa = queue -> sa;
  sb = queue -> sb;

  int (*routine)(blas_arg_t *, void *, void *, void *, void *, BLASLONG) = queue -> routine;

  #ifdef CONSISTENT_FPCSR
    __asm__ __volatile__ ("ldmxcsr %0" : : "m" (queue -> sse_mode));
    __asm__ __volatile__ ("fldcw %0"   : : "m" (queue -> x87_mode));
  #endif

  MT_TRACE("Server[%2ld] Started.  Mode = 0x%03x M = %3ld N=%3ld K=%3ld\n",
    cpu, queue->mode, queue-> args ->m, queue->args->n, queue->args->k);

  // fprintf(stderr, "queue start[%ld]!!!\n", cpu);

  #ifdef MONITOR
    main_status[cpu] = MAIN_RUNNING1;
  #endif

  if (sa == NULL) 
    sa = (void *)((BLASLONG)buffer + GEMM_OFFSET_A);

  if (sb == NULL) {
    if (!(queue -> mode & BLAS_COMPLEX)) {
#ifdef EXPRECISION
if ((queue -> mode & BLAS_PREC) == BLAS_XDOUBLE) {
  sb = (void *)(((BLASLONG)sa + ((XGEMM_P * XGEMM_Q * sizeof(xdouble)
      + GEMM_ALIGN) & ~GEMM_ALIGN)) + GEMM_OFFSET_B);
} else
#endif
  if ((queue -> mode & BLAS_PREC) == BLAS_DOUBLE) {
#ifdef BUILD_DOUBLE
    sb = (void *)(((BLASLONG)sa + ((DGEMM_P * DGEMM_Q * sizeof(double)
        + GEMM_ALIGN) & ~GEMM_ALIGN)) + GEMM_OFFSET_B);
#endif
  } else if ((queue -> mode & BLAS_PREC) == BLAS_SINGLE) {
#ifdef BUILD_SINGLE
    sb = (void *)(((BLASLONG)sa + ((SGEMM_P * SGEMM_Q * sizeof(float)
        + GEMM_ALIGN) & ~GEMM_ALIGN)) + GEMM_OFFSET_B);
#endif
  } else {
        /* Other types in future */
  }
} else {
#ifdef EXPRECISION
if ((queue -> mode & BLAS_PREC) == BLAS_XDOUBLE){
  sb = (void *)(((BLASLONG)sa + ((XGEMM_P * XGEMM_Q * 2 * sizeof(xdouble)
      + GEMM_ALIGN) & ~GEMM_ALIGN)) + GEMM_OFFSET_B);
} else
#endif
  if ((queue -> mode & BLAS_PREC) == BLAS_DOUBLE){
#ifdef BUILD_COMPLEX16
    sb = (void *)(((BLASLONG)sa + ((ZGEMM_P * ZGEMM_Q * 2 * sizeof(double)
        + GEMM_ALIGN) & ~GEMM_ALIGN)) + GEMM_OFFSET_B);
#endif
  } else if ((queue -> mode & BLAS_PREC) == BLAS_SINGLE) {
#ifdef BUILD_COMPLEX
    sb = (void *)(((BLASLONG)sa + ((CGEMM_P * CGEMM_Q * 2 * sizeof(float)
        + GEMM_ALIGN) & ~GEMM_ALIGN)) + GEMM_OFFSET_B);
#endif
  } else {
        /* Other types in future */
  }
}
    queue->sb=sb;
  }

  #ifdef MONITOR
    main_status[cpu] = MAIN_RUNNING2;
  #endif

  if (!(queue -> mode & BLAS_LEGACY)) {
    (routine)(queue -> args, queue -> range_m, queue -> range_n, sa, sb, queue -> position);
  } else {
    legacy_exec(routine, queue -> mode, queue -> args, sb);
  }

}