/* File:  
 *    pth_cond_bar.c
 *
 * Purpose:
 *    Use condition wait barriers to synchronize threads.
 *
 * Input:
 *    none
 * Output:
 *    Time for BARRIER_COUNT barriers
 *
 * Usage:
 *    pth_cond_bar <thread_count>
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "timer.h"

#define BARRIER_COUNT 1000

int thread_count;
int barrier_thread_count = 0;
pthread_mutex_t barrier_mutex;
pthread_cond_t ok_to_proceed;

void Usage(char* prog_name);
void *Thread_work(void* rank);

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   long       thread;
   pthread_t* thread_handles; 
   double start, finish;

   if (argc != 2) Usage(argv[0]);
   thread_count = strtol(argv[1], NULL, 10);

   thread_handles = malloc (thread_count*sizeof(pthread_t));
   pthread_mutex_init(&barrier_mutex, NULL);
   pthread_cond_init(&ok_to_proceed, NULL);

   GET_TIME(start);
   for (thread = 0; thread < thread_count; thread++)
      pthread_create(&thread_handles[thread], (pthread_attr_t*) NULL,
          Thread_work, (void*) thread);

   for (thread = 0; thread < thread_count; thread++) 
      pthread_join(thread_handles[thread], NULL);
   GET_TIME(finish);
   printf("Elapsed time = %e seconds\n", finish - start);

   pthread_mutex_destroy(&barrier_mutex);
   pthread_cond_destroy(&ok_to_proceed);
   free(thread_handles);
   return 0;
}  /* main */


/*--------------------------------------------------------------------
 * Function:    Usage
 * Purpose:     Print command line for function and terminate
 * In arg:      prog_name
 */
void Usage(char* prog_name) {

   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   exit(0);
}  /* Usage */


/*-------------------------------------------------------------------
 * Function:    Thread_work
 * Purpose:     Run BARRIER_COUNT barriers
 * In arg:      rank
 * Global var:  thread_count, barrier_thread_count, barrier_mutex,
 *              ok_to_proceed
 * Return val:  Ignored
 */
void *Thread_work(void* rank) {
// long my_rank = (long) rank; 
   int i;

   for (i = 0; i < BARRIER_COUNT; i++) {
      pthread_mutex_lock(&barrier_mutex);
      barrier_thread_count++;
      if (barrier_thread_count == thread_count) {
         barrier_thread_count = 0;
         pthread_cond_broadcast(&ok_to_proceed);
      } else {
         // Wait unlocks mutex and puts thread to sleep.
         //    Put wait in while loop in case some other
         // event awakens thread.
         while (pthread_cond_wait(&ok_to_proceed,
                   &barrier_mutex) != 0);
         // Mutex is relocked at this point.
      }
      pthread_mutex_unlock(&barrier_mutex);
   }

   return NULL;
}  /* Thread_work */
