#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;
sem_t full;
sem_t empty;

int variable = 100;
void* func1();
void* func2();

int main(){
    pthread_t tid1,tid2;
    int res1,res2;
    sem_init(&mutex,0,1);
    sem_init(&full,0,0);
    sem_init(&empty,0,1);
    while((pthread_create(&tid1,NULL,func1,NULL))!=0);
    while((pthread_create(&tid2,NULL,func2,NULL))!=0);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    printf("variable = %d\n",variable);
    return 0;
    
}
//todo:修改system和execl调用
void* func1(){
    printf("thread 1 created successfully!\n");
    sem_wait(&mutex);
    for(int i=0;i<100000;i++){
        variable++;
    }
    sem_post(&mutex);

    pid_t pid1 = getpid();
    pthread_t tid1 = pthread_self();
    sem_wait(&empty);
    printf("thread 1:pid = %d, tid = %lu\n",pid1,tid1);
    execl("out/system_call",NULL);
    sem_post(&full);
    pthread_exit(NULL); 
}

void* func2(){
    printf("thread 2 created successfully!\n");
    sem_wait(&mutex);
    for(int i=0;i<100000;i++){
        variable--;
    }
    sem_post(&mutex);

    pid_t pid2 = getpid();
    pthread_t tid2 = pthread_self();
    sem_wait(&full);
    printf("thread 2:pid = %d, tid = %lu\n",pid2,tid2);
    execl("out/system_call",NULL);
    sem_post(&empty);
    pthread_exit(NULL); 
}