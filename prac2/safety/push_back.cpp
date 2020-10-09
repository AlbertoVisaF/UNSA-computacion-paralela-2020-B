#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <vector>
using namespace std;
int thread_count;
struct ARG{
vector<int>* t_v;
};
void* Proof(void* args){
ARG* g = (ARG*)args;
g->t_v->push_back(4);
return NULL;
}
int main(int argc, char* argv[]){
long thread;
pthread_t* thread_handles;
thread_count = strtol(argv[1],NULL,10);
thread_handles = (pthread_t*)malloc(thread_count*sizeof(pthread_t));
vector<int> v{1,2,3};
ARG p;
p.t_v = &v;
for(thread=0; thread<thread_count; thread++){
pthread_create(&thread_handles[thread], NULL, Proof, (void*)&p);
}
for(thread=0; thread<thread_count; thread++){
pthread_join(thread_handles[thread], NULL);
}
free(thread_handles);
return 0;
}
