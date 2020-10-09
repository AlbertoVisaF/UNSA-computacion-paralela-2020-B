#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
using namespace std;
int thread_count;
void* Proof(void* message){
cout<<(char*) message<<endl;
return NULL;
}
int main(int argc, char* argv[]){
long thread;
pthread_t* thread_handles;
thread_count = strtol(argv[1],NULL,10);
thread_handles = (pthread_t*)malloc(thread_count*sizeof(pthread_t));
char const* messages[thread_count] = {"Thread 1","Thread 2",
"Thread 3","Thread 4"};
for(thread=0; thread<thread_count; thread++){
pthread_create(&thread_handles[thread], NULL, Proof,
(void*) messages[thread]);
}
for(thread=0; thread<thread_count; thread++){
pthread_join(thread_handles[thread], NULL);
}
free(thread_handles);
}
