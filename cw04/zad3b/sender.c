#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>

int GOT_SIGUSR1_SIGNALS=0;
int SIGNALS_GOT_BY_CATCHER=0;
bool GET_SIGUSR2=false;
pid_t CATCHER;
int TYPE=0;
sigset_t MASK;
bool RECIVING=false;

void confirm(){
    if(TYPE==0)
        kill(CATCHER,SIGUSR1);
    else if(TYPE==1){
        union sigval sv;
        sv.sival_int=1;
        sigqueue(CATCHER,SIGUSR1,sv);
    }else if(TYPE==2){
        kill(CATCHER,SIGRTMIN);
    }
}


void sigusr1_handler(int sig_no,siginfo_t *info,void *ucontext){    
    if(RECIVING){
        confirm();
        if(!GET_SIGUSR2)
            sigsuspend(&MASK);
        
        GOT_SIGUSR1_SIGNALS++;
        SIGNALS_GOT_BY_CATCHER=info->si_value.sival_int;
    }
    
}

void sigusr2_handler(int sig_no,siginfo_t *info,void *ucontext){
    GET_SIGUSR2=true;
}

void sigmin_handler(int sig_no,siginfo_t *info,void *ucontext){    
    if(RECIVING){
        confirm();
        if(!GET_SIGUSR2)
            sigsuspend(&MASK);
        
        GOT_SIGUSR1_SIGNALS++;
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
    // printf("%d\n",getpid());
    if(argc!=4){
        printf("Invalid number of arguments. Expected 3, given %d.",argc-1);
        return 1;
    }
    int signal_no=atoi(argv[2]);
    CATCHER=(pid_t)atoi(argv[1]);
    if(strcmp("KILL",argv[3])==0)
        TYPE=0;
    else if(strcmp("SIGQUEUE",argv[3])==0){
        TYPE=1;
    }else if(strcmp("SIGRT",argv[3])==0){
        TYPE=2;
    }

    set_sigusr_handlers();

    sigfillset(&MASK);
    sigprocmask(SIG_SETMASK,&MASK,NULL);
    sigdelset(&MASK,SIGUSR1);
    sigdelset(&MASK,SIGUSR2);
    sigdelset(&MASK,SIGRTMIN);
    sigdelset(&MASK,SIGRTMIN+1);

    
    int i=0;
    while (signal_no>i)
    {
        if(TYPE==0)
            kill(CATCHER,SIGUSR1);
        else if(TYPE==1){
            union sigval sv;
            sv.sival_int=1;
            sigqueue(CATCHER,SIGUSR1,sv);
        }else if(TYPE==2){
            kill(CATCHER,SIGRTMIN);
        }
        sigsuspend(&MASK);
        i++;
    }
    if(TYPE==0)
        kill(CATCHER,SIGUSR2);
    else if(TYPE==1){
        union sigval sv;
        sv.sival_int=-1;
        sigqueue(CATCHER,SIGUSR2,sv);
    }else if(TYPE==2){
        kill(CATCHER,SIGRTMIN+1);
    }

    RECIVING=true;
    sigsuspend(&MASK);

    printf("Sent: %d\nRecieved: %d\n",signal_no,GOT_SIGUSR1_SIGNALS);
    if(SIGNALS_GOT_BY_CATCHER!=0)
        printf("Catcher got: %d\n",SIGNALS_GOT_BY_CATCHER);

}