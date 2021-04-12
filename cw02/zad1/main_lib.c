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

void read_and_write_files(FILE* fileA, FILE* fileB){
    char* line = (char*)malloc(1);
    int i=0;
    char charA;
    char charB;
    int readA=fread(&charA,1,1,fileA);
    int readB=fread(&charB,1,1,fileB);
    bool fileAEnded=false;
    bool fileBEnded=false;

    while(readA==1||readB==1){
        
        while(readA==1&&(charA!='\n'&&charA!=EOF)){
            line=realloc(line, i+2);
            line[i]=charA;
            i++;
            //strcat(line,&charA);
            readA=fread(&charA,1,1,fileA);
        }
        if(readA==1&&charA!=EOF){
            line=realloc(line, i+2);
            line[i]='\0';
            printf("%s\n",line);
            line=realloc(line,1); 
            readA=fread(&charA,1,1,fileA);
        }else if(readA==1){
            printf("\n");
        }

        if(!fileAEnded&&charA==EOF)
                fileAEnded=true;
           

        i=0;

        while(readB==1&&(charB!='\n'&&charB!=EOF)){
            line=realloc(line, i+2);
            line[i]=charB;
            i++;
            //strcat(line,&charA);
            readB=fread(&charB,1,1,fileB);
        }
        if(readB==1&&charB!=EOF){
            line=realloc(line, i+2);
            line[i]='\0';
            printf("%s\n",line);
            line=realloc(line,1); 
            readA=fread(&charB,1,1,fileB);
        }else if(readB==1){
            printf("\n");
        }

        if(!fileBEnded&&charB==EOF)
                fileBEnded=true;
        i=0;
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
        FILE* fileA=fopen(argv[1],"r");
        if(!fileA){
            printf("Thee file %s does not exist or path is incorrect.",argv[1]);
            return -1;
        }
        FILE* fileB=fopen(argv[2],"r");
        if(!fileB){
            printf("Thee file %s does not exist or path is incorrect.",argv[2]);
            return -1;
        }
        read_and_write_files(fileA,fileB);
        fclose(fileA);
        fclose(fileB);
    }else if(argc==2){
        printf("Podano tylko scieżkę do jednego pliku, podaj drugą:\n");
        char* fileBPath = (char *)calloc(256,sizeof(char));
        fgets(fileBPath,sizeof(fileBPath),stdin);

        FILE* fileA=fopen(argv[1],"r");
        if(fileA==-1){
            printf("Thee file %s does not exist or path is incorrect.",argv[1]);
            return -1;
        }
        FILE* fileB=fopen(fileBPath,"r");
        if(!fileB){
            printf("Thee file %s does not exist or path is incorrect.",argv[2]);
            return -1;
        }
        read_and_write_files(fileA,fileB);
        fclose(fileA);
        fclose(fileB);
        free(fileBPath);
    }else{
        printf("Nie podano scieżek plików do wypisania, podaj pierwszą:\n");
        char* fileAPath = (char *)calloc(256,sizeof(char));
        fgets(fileAPath,sizeof(fileAPath),stdin);

        printf("Podaj druga scieżkę pierwszą:\n");
        char* fileBPath = (char *)calloc(256,sizeof(char));
        fgets(fileBPath,sizeof(fileBPath),stdin);

        FILE* fileA=fopen(fileAPath,"r");
        if(!fileA){
            printf("Thee file %s does not exist or path is incorrect.",argv[1]);
            return -1;
        }
        FILE* fileB=fopen(fileBPath,"r");
        if(!fileB){
            printf("Thee file %s does not exist or path is incorrect.",argv[2]);
            return -1;
        }
        
        read_and_write_files(fileA,fileB);
        
        fclose(fileA);
        fclose(fileB);
        
        free(fileAPath);
        free(fileBPath);
    }
    clock_gettime(CLOCK_REALTIME,&stop_real); 
    times(&end_tms);

    measured.real+=(stop_real.tv_sec-start_real.tv_sec)+(double)(stop_real.tv_nsec-start_real.tv_nsec)/(double)BILLION;
    measured.user += (end_tms.tms_utime - start_tms.tms_utime);
    measured.system += (end_tms.tms_stime - start_tms.tms_stime);

    printf( "Total time:\n real: %lf system: %lf user: %lf\n", measured.real,(double)measured.system/ticks,(double)measured.user/ticks);
}