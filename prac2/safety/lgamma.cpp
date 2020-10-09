#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <math.h>
using namespace std;
int thread_count;
struct ARGS{
long rank;
double value;
};
void* Proof(void* args){
ARGS* message = (ARGS*)args;
lgamma(message->value);
sleep(1);
printf("El signo de gamma del thread %ld es: %i\n", message->rank, signgam);
return NULL;
}
int main(int argc, char* argv[]){
long thread;
pthread_t* thread_handles;
thread_count = strtol(argv[1],NULL,10);
thread_handles = (pthread_t*)malloc(thread_count*sizeof(pthread_t));
double values[] = {-0.5, 6.0, 7.0, 8.0};
for(thread=0; thread<thread_count; thread++){
lgamma(values[thread]);
printf("El signo de gamma correcto del thread
%ld deberia ser: %i\n", thread, signgam);
}
for(thread=0; thread<thread_count; thread++){
ARGS* a = (ARGS*)malloc(sizeof(ARGS));
a->rank = thread;
a->value = values[thread];
pthread_create(&thread_handles[thread], NULL, Proof, (void*)a);
}
for(thread=0; thread<thread_count; thread++){
pthread_join(thread_handles[thread], NULL);
}
free(thread_handles);
}
