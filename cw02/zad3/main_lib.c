#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include<time.h>
#include<sys/times.h>

#define BILLION  1000000000L;

struct measuredTime{
    double real;
    long long system;
    long long user;
};

bool check_if_square(int i){
    return ((int)sqrt(i)*sqrt(i)==i);
}

void read_find_and_write_numbers( FILE* file){
    char* line = (char*)malloc(1);
    int i=0;
    char readedChar='\0';
    int read=fread(&readedChar,1,1,file);
    bool fileAEnded=false;
    int evenCounter=0;
    FILE* tmpB = fopen("b.txt","w+");
    FILE* tmpC = fopen("c.txt","w+");
    while(read==1){
        
        while(read==1&&(readedChar!='\n'&&readedChar!=EOF)){
            line=realloc(line, i+2);
            line[i]=readedChar;
            i++;
            //strcat(line,&charA);
            read=fread(&readedChar,1,1,file);
        }
        if(readedChar!=EOF){
            line=realloc(line, i+2);
            line[i]='\n';
            if(check_if_square(atoi(line)))
                fwrite(line,1,i+1,tmpC);
            if(i>=2){
                if(line[i-2]=='7'||line[i-2]=='0')
                    fwrite(line,1,i+1,tmpB);
            }
            if(((int)line[i-1]-(int)'0')%2==0)
                evenCounter++;
            
            line=realloc(line,1); 
            read=fread(&readedChar,1,1,file);
        }
        if(!fileAEnded&&readedChar==EOF)
                fileAEnded=true;
           
        i=0;
    }

    fclose(tmpB);
    tmpB = fopen("a.txt","w+");
    fwrite("Liczb parzystych jest: ",1,23,tmpB);
    char* strEvenCounter = (char*)calloc(12,1);
    sprintf(strEvenCounter,"%d",evenCounter);
    //printf("%s\n",strEvenCounter);
    fwrite(strEvenCounter,1,strlen(strEvenCounter),tmpB);
    fclose(tmpC);
    fclose(tmpB);

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
    if(argc==2){
        FILE* file=fopen(argv[1],"r");
        if(!file){
            printf("Thee file %s does not exist or path is incorrect.",argv[2]);
            return -1;
        }
        read_find_and_write_numbers(file);
        fclose(file);
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