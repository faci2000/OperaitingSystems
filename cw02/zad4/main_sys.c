#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include<time.h>
#include<sys/times.h>

#define BILLION  1000000000L;

struct measuredTime{
    double real;
    long long system;
    long long user;
};


void read_change_and_write(int fileFrom,int fileTo,char* toChange,char* changeWith){
    char* word = (char*)malloc(1);
    int i=0;
    char readedChar='\0';
    int readed=read(fileFrom,&readedChar,1);
    while(readed==1){
        
        while(readed==1&&readedChar!='\n'&&readedChar!=EOF&&readedChar!=' '&&readedChar!='.'&&readedChar!=','&&readedChar!=';'){
            word=realloc(word, i+1);
            word[i]=readedChar;
            i++;
            readed=read(fileFrom,&readedChar,1);
        }
        word[i]='\0';
        if(strcmp(word,toChange)==0){
            write(fileTo,changeWith,strlen(changeWith));
        }else{
            write(fileTo,word,i);
        }
        if(readed==1&&readedChar!=EOF){
            write(fileTo,&readedChar,1);
            readed=read(fileFrom,&readedChar,1);
        }
           
        i=0;
    }
    free(word);
}


int main(int argc,char** argv){
    const long ticks =sysconf(2);
    struct timespec start_real, stop_real;
    struct tms start_tms,end_tms;

    struct measuredTime measured;
    measured.real=0;
    measured.system=0;
    measured.user=0;

    times(&start_tms);
    clock_gettime(CLOCK_REALTIME,&start_real); 
    if(argc==5){
        int fileFrom=open(argv[1],O_RDONLY);
        if(fileFrom==-1){
            printf("Thee file %s does not exist or path is incorrect.",argv[1]);
            return -1;
        }
        int fileTo=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC, 0666);
        if(fileTo==-1){
            printf("Thee file %s does not exist or path is incorrect.",argv[2]);
            return -1;
        }
        read_change_and_write(fileFrom,fileTo,argv[3],argv[4]);
        close(fileFrom);
        close(fileTo);
    }else{
        printf("Wrong number of arguments!\n");
        return -1;
    }
    clock_gettime(CLOCK_REALTIME,&stop_real); 
    times(&end_tms);

    measured.real+=(stop_real.tv_sec-start_real.tv_sec)+(double)(stop_real.tv_nsec-start_real.tv_nsec)/(double)BILLION;
    measured.user += (end_tms.tms_utime - start_tms.tms_utime);
    measured.system += (end_tms.tms_stime - start_tms.tms_stime);

    printf( "Total time:\n real: %lf system: %lf user: %lf\n", measured.real,(double)measured.system/ticks,(double)measured.user/ticks);
}