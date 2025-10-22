#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    pthread_t tid = pthread_self();
    printf("thread tid = %lu\n",tid);
    return 0;
}