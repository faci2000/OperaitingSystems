#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>


void signinfo_handler(int sig,siginfo_t *info,void *ucontext) {
    printf("Signal %d recieved from process PID:%d .\n", sig,info->si_pid);
} 

void sigchld_handler(int sig_no){
    printf("Signal %d recieved.\n", sig_no);
}


void test_signal(){
    raise(SIGUSR1);
    pid_t child_pid;
    child_pid = fork();
    if(child_pid==0){
        raise(SIGUSR1);
    }
}


int main(int argc,char** argv) {

    struct sigaction action;
    action.sa_sigaction=signinfo_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags=SA_SIGINFO;
    sigaction(SIGUSR1,&action,NULL);

    raise(SIGUSR1);    
    
    action.sa_handler=sigchld_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags=SA_RESETHAND;
    sigaction(SIGCHLD,&action,NULL);

    
    pid_t first_child = fork();
    if(first_child==0){
       raise(SIGSTOP);
    }
    sleep(2);

    pid_t second_child = fork();
    if(second_child==0){
       raise(SIGSTOP);
    }
    sleep(2);
    
    struct sigaction action2;
    action2.sa_handler=sigchld_handler;
    sigemptyset(&action2.sa_mask);
    action2.sa_flags=SA_NOCLDSTOP;
    sigaction(SIGCHLD,&action2,NULL);

    pid_t third_child = fork();
    if(third_child==0){
       raise(SIGSTOP);
    }
    sleep(2);
    
    kill(first_child,SIGKILL);
    kill(second_child,SIGKILL);
    kill(third_child,SIGKILL);
}