#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int wait_flag;

void stop();

int main(){
    int pid1,pid2;
    signal(2,stop);
    while((pid1=fork())==-1);
    if(pid1>0){
        while((pid2=fork())==-1);
        if(pid2>0){
            wait_flag=1;
            alarm(6);
            sleep(3); //todo 父进程等待5秒
            //kill(pid1,16);
            kill(pid2,17);
            wait(0);
            wait(0);
            printf("\n Parent process is killed !!\n");
            exit(0);
        }
        else{
            wait_flag=1;
            signal(17,stop); //todo 等待进程2被杀死的中断号17
            while(wait_flag==1);
            printf("\n Child process 2 is killed by parent !!\n");
            exit(0);
        }
    }
    else{
        wait_flag=1;
        signal(14,stop);
        while(wait_flag==1);
        printf("\n Child process 1 is killed by parent !!\n");
        exit(0);
    }
}
void stop(){
    wait_flag = 0;
}