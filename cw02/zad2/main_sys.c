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

void read_find_and_write_lines(char demandedChar, int file){
    char* line = (char*)malloc(1);
    int i=0;
    char readedChar='\0';
    int readed=read(file,&readedChar,1);
    bool fileAEnded=false;
    bool contains=false;

    while(readed==1){
        
        while(readed==1&&(readedChar!='\n'&&readedChar!=EOF)){
            line=realloc(line, i+2);
            line[i]=readedChar;
            if(readedChar==demandedChar)
                contains=true;
            i++;
            //strcat(line,&charA);
            readed=read(file,&readedChar,1);
        }
        if(readedChar!=EOF){
            line=realloc(line, i+2);
            line[i]='\0';
            if(contains)
                printf("%s\n",line);
            line=realloc(line,1); 
            readed=read(file,&readedChar,1);
        }else if(!fileAEnded&&contains){
            printf("\n");
        }

        if(!fileAEnded&&readedChar==EOF)
                fileAEnded=true;
           
        i=0;
        contains=false;
    }

    free(line);
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
    if(argc==3){
        int file=open(argv[2],O_RDONLY);
        if(!file){
            printf("Thee file %s does not exist or path is incorrect.",argv[2]);
            return -1;
        }
        char demandedChar = argv[2][0];
        read_find_and_write_lines(demandedChar,file);
        close(file);
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