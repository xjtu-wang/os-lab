#include <sys/types.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("system_call process pid = %d\n",pid);
    printf("system_call thread tid = %lu\n",tid);
    return 0;
}