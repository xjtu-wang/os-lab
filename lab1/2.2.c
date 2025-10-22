#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
sem_t mutex;

int variable = 100;
void* func1();
void* func2();

int main(){
    pthread_t tid1,tid2;
    int res1,res2;
    sem_init(&mutex,0,1);
    while((pthread_create(&tid1,NULL,func1,NULL))!=0);
    while((pthread_create(&tid2,NULL,func2,NULL))!=0);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    printf("variable = %d\n",variable);
    return 0;
    
}

void* func1(){
    printf("thread 1 created successfully!\n");
    sem_wait(&mutex);
    for(int i=0;i<100000;i++){
        variable++;
    }
    sem_post(&mutex);
    pthread_exit(NULL); 
}

void* func2(){
    printf("thread 2 created successfully!\n");
    sem_wait(&mutex);
    for(int i=0;i<100000;i++){
        variable--;
    }
    sem_post(&mutex);
    pthread_exit(NULL); 
}