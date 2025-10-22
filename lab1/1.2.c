#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int a = 1;

int main(){
    pid_t pid,pid1;
    pid = fork();

    if(pid<0){
        fprintf(stderr,"Fork Failed");
        return 1;
    }
    else if(pid == 0){
        pid1 = getpid();
        a++;
        printf("child: pid = %d\n",pid);
        printf("child: pid1 = %d\n",pid1);
        printf("a = %d\n",a);
    }
    else{
        pid1 = getpid();
        a--;
        printf("parent: pid = %d\n",pid);
        printf("parent: pid1 = %d\n",pid1);
        printf("a = %d\n",a);
        //wait(NULL);
    }
    return 0;
}