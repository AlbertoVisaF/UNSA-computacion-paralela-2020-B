#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
using namespace std;
int thread_count;
void* Proof(void* args){
long rank = (long) args;
srand(rank);
int r1 = rand()%10+1;
sleep(1);
int r2 = rand()%10+1;
printf("Los numeros aleatorios finales del thread %ld son: %i %i\n",
rank, r1, r2);
return NULL;
}
int main(int argc, char* argv[]){
long thread;
pthread_t* thread_handles;
thread_count = strtol(argv[1],NULL,10);
thread_handles = (pthread_t*)malloc(thread_count*sizeof(pthread_t));
for(thread=0; thread<thread_count; thread++){
srand(thread);
int r1 = rand()%10+1;
int r2 = rand()%10+1;
printf("Los numeros aleatorios correctos del thread %ld son: %i %i\n",
thread, r1,r2);
}
for(thread=0; thread<thread_count; thread++){
pthread_create(&thread_handles[thread], NULL, Proof, (void*)thread);
}
for(thread=0; thread<thread_count; thread++){
pthread_join(thread_handles[thread], NULL);
}
free(thread_handles);
}
