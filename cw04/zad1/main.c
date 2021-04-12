#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


void handler(int sig_no) {
 printf("Signal %d recieved.\n", sig_no);
} 

void set_mask(){
    sigset_t newmask;
    sigset_t oldmask;
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGUSR1);
    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
        printf("The new mask wasnt set.");
}

void test_signal(bool is_pending){
    raise(SIGUSR1);
    pid_t child_pid;
    child_pid = fork();
    if(child_pid==0&&!is_pending){
        raise(SIGUSR1);
    }
}

void check_pending(){
    sigset_t pending_signals;
    sigemptyset(&pending_signals);
    sigpending(&pending_signals);

    //printf("%d\n",getpid());

    if(sigismember(&pending_signals,SIGUSR1))
        printf("Signal %d is pending.\n",SIGUSR1);
    else
        printf("Signal %d is not pending.\n",SIGUSR1);

}

int main(int argc,char** argv) {
    if(argc!=2){
        printf("Wrong number of arguments!");
        return -1;
    }
    if(strcmp("handler",argv[1])==0){

        printf("Testing handler:\n");

        struct sigaction action;
        action.sa_handler=handler;
        sigemptyset(&action.sa_mask);
        action.sa_flags=0;
        sigaction(SIGUSR1,&action,NULL);

        test_signal(false);

    }else if(strcmp("ignore",argv[1])==0){
        printf("Testing ignore:\n");
        
        signal(SIGUSR1,SIG_IGN);

        test_signal(false);

    }else if(strcmp("mask",argv[1])==0){
        
        printf("Testing mask:\n");

        set_mask();

        test_signal(false);

    }else if("pending"){

        printf("Testing pending:\n");

        set_mask();

        test_signal(true);

        check_pending();

    }
    
    
}