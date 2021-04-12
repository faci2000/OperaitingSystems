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
sigset_t MASK;


void sigusr1_handler(int sig_no,siginfo_t *info,void *ucontext){    
    if(!GET_SIGUSR2)
        sigsuspend(&MASK);
    GOT_SIGUSR1_SIGNALS++;

    SIGNALS_GOT_BY_CATCHER=info->si_value.sival_int;
}

void sigusr2_handler(int sig_no,siginfo_t *info,void *ucontext){
    GET_SIGUSR2=true;
}

void sigmin_handler(int sig_no,siginfo_t *info,void *ucontext){    
    if(!GET_SIGUSR2)
        sigsuspend(&MASK);

    GOT_SIGUSR1_SIGNALS++;
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
    //printf("%d\n",getpid());
    if(argc!=4){
        printf("Invalid number of arguments. Expected 3, given %d.",argc-1);
        return 1;
    }
    int signal_no=atoi(argv[2]);
    pid_t catcher=(pid_t)atoi(argv[1]);
    int type=-1;
    if(strcmp("KILL",argv[3])==0)
        type=0;
    else if(strcmp("SIGQUEUE",argv[3])==0){
        type=1;
    }else if(strcmp("SIGRT",argv[3])==0){
        type=2;
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
        if(type==0)
            kill(catcher,SIGUSR1);
        else if(type==1){
            union sigval sv;
            sv.sival_int=1;
            sigqueue(catcher,SIGUSR1,sv);
        }else if(type==2){
            kill(catcher,SIGRTMIN);
        }
        i++;
    }
    if(type==0)
        kill(catcher,SIGUSR2);
    else if(type==1){
        union sigval sv;
        sv.sival_int=-1;
        sigqueue(catcher,SIGUSR2,sv);
    }else if(type==2){
        kill(catcher,SIGRTMIN+1);
    }
    
    sigsuspend(&MASK);

    printf("Sent: %d\nRecieved: %d\n",signal_no,GOT_SIGUSR1_SIGNALS);
    if(SIGNALS_GOT_BY_CATCHER!=0)
        printf("Catcher got: %d\n",SIGNALS_GOT_BY_CATCHER);

}