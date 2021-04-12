#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc,char** argv) {

    int processes=0;
    if(argc!=2){
        printf("Invalid number of arguments!\n");
        return -1;
    }else{
        processes=atoi(argv[1]);
        if(processes==0){
            printf("The given number of processes is invalid!");
            return -1;
        }
    }
    pid_t child_pid;
    printf("Main program PID: %d\n", (int)getpid());
    for(int i=0;i<processes;i++){
        child_pid = fork();
        if(child_pid==0)
            break;
    }
    
    if(child_pid==0) {
        printf("This printf was called from child process with PID:%d\n", (int)getpid());
    }

    return 0;   
}