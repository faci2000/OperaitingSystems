#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>

int GOT_SIGUSR1_SIGNALS=0;
bool GET_SIGUSR2=false;
int TYPE=0;//0-KILL,1-SIGQUEUE,2-KILL(SIGRT)
pid_t SENDER_PID=0;
sigset_t MASK;
bool RECIVING=true;

void confirm(){
    if(TYPE==0)
        kill(SENDER_PID,SIGUSR1);
    else if(TYPE==1){
        union sigval sv;
        sv.sival_int=GOT_SIGUSR1_SIGNALS;
        sigqueue(SENDER_PID,SIGUSR1,sv);
    }else if(TYPE==2){
        kill(SENDER_PID,SIGRTMIN);
    }
}

void sigusr1_handler(int sig_no,siginfo_t *info,void *ucontext){  
    if(RECIVING){
        GOT_SIGUSR1_SIGNALS++;
        if(SENDER_PID==0)
            SENDER_PID=info->si_pid;
        //printf("%d\n",info->si_value.sival_int);
        TYPE=info->si_value.sival_int;
        confirm();
        if(!GET_SIGUSR2)
            sigsuspend(&MASK);
    }
    
}

void sigusr2_handler(int sig_no,siginfo_t *info,void *ucontext){
    GET_SIGUSR2=true;

}

void sigmin_handler(int sig_no,siginfo_t *info,void *ucontext){
    if(RECIVING){
        GOT_SIGUSR1_SIGNALS++;
        if(SENDER_PID==0)
            SENDER_PID=info->si_pid;

        TYPE=2;
        confirm();
        if(!GET_SIGUSR2)
            sigsuspend(&MASK);

    }
    
}

void sigmin1_handler(int sig_no,siginfo_t *info,void *ucontext){
    GET_SIGUSR2=true;
}


void set_sigusr_handlers(){
    struct sigaction action;
    action.sa_sigaction=sigusr1_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags=SA_SIGINFO;
    sigaction(SIGUSR1,&action,NULL);
    
    struct sigaction action2;
    action2.sa_sigaction=sigusr2_handler;
    sigemptyset(&action2.sa_mask);
    action2.sa_flags=SA_SIGINFO;
    sigaction(SIGUSR2,&action2,NULL);

    struct sigaction action3;
    action3.sa_sigaction=sigmin_handler;
    sigemptyset(&action3.sa_mask);
    action3.sa_flags=SA_SIGINFO;
    sigaction(SIGRTMIN,&action3,NULL);

    struct sigaction action4;
    action4.sa_sigaction=sigmin1_handler;
    sigemptyset(&action4.sa_mask);
    action4.sa_flags=SA_SIGINFO;
    sigaction(SIGRTMIN+1,&action4,NULL);
}

int main(int argc,char** argv) {
    printf("%d\n",getpid());

    // sigprocmask(SIG_SETMASK,&MASK,NULL);

    set_sigusr_handlers();
    sigfillset(&MASK);
    sigdelset(&MASK,SIGUSR1);
    sigdelset(&MASK,SIGUSR2);
    sigdelset(&MASK,SIGRTMIN);
    sigdelset(&MASK,SIGRTMIN+1);
    sigsuspend(&MASK);

    RECIVING=false;

    int i=0;
    while (GOT_SIGUSR1_SIGNALS>i)
    {
            
        if(TYPE==0)
            kill(SENDER_PID,SIGUSR1);
        else if(TYPE==1){
            union sigval sv;
            sv.sival_int=GOT_SIGUSR1_SIGNALS;
            sigqueue(SENDER_PID,SIGUSR1,sv);
        }else if(TYPE==2){
            kill(SENDER_PID,SIGRTMIN);
        }
        sigsuspend(&MASK);
        i++;
    }
    if(TYPE==0)
        kill(SENDER_PID,SIGUSR2);
    else if(TYPE==1){
        union sigval sv;
        sv.sival_int=GOT_SIGUSR1_SIGNALS;
        sigqueue(SENDER_PID,SIGUSR2,sv);
    }else if(TYPE==2){
        kill(SENDER_PID,SIGRTMIN+1);
    }

    printf("Recieved and sent: %d\n",GOT_SIGUSR1_SIGNALS);
}