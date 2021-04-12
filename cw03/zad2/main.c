#include<stdio.h>
#include"textmergelib.h"
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<sys/times.h>
#include <inttypes.h>
#include  <unistd.h>
#include<sys/wait.h>

#define BILLION  1000000000L;

struct measuredTime{
    double real;
    long long system;
    long long user;
};

int check_if_pair_of_files(char* pairOfFiles){
    int i=0;
    while(pairOfFiles[i]!='\0'){
        if(pairOfFiles[i]==':'){
            return i;
        }
        i++;
    }
    return -1;
}

int main(int argc, char **argv){
    const long ticks =sysconf(2);
    struct timespec start_real, stop_real;
    struct tms start_tms,end_tms;

    struct measuredTime merges;
    merges.real=0;
    merges.system=0;
    merges.user=0;        
    
    struct BlocksArray mainBlock;

    for(int i=1;i<argc;i++){    
        if(strcmp("merge_files",argv[i])==0){
            
            int pairs=0;
            bool first=true;
            int div_position=check_if_pair_of_files(argv[i+1]);
            char* fileNames=(char*)calloc(1,sizeof(char));
            while(div_position!=-1&&i<argc-1){
                
                //argv[i][div_position]=' ';
                if(!first){
                    fileNames = realloc(fileNames,strlen(fileNames)+2);
                    strcat(fileNames," ");
                } 
                int fileNamesLen = strlen(fileNames); 
                fileNames = realloc(fileNames,strlen(fileNames)+strlen(argv[i+1])+1);
                
                strcat(fileNames,argv[i+1]);
                fileNames[fileNamesLen+div_position]=' ';
                pairs++;
                i++;
                first=false;
                if(i<argc-1)
                    div_position=check_if_pair_of_files(argv[i+1]);
            }

            mainBlock = create_new_main_blocks_array(pairs);

            int new_files=mainBlock.end;

            set_file_names(&mainBlock,define_files_sequence(fileNames),pairs);

            free(fileNames);
            
            pid_t child_pid,wpid;
            int status=0;

            times(&start_tms);
            clock_gettime(CLOCK_REALTIME,&start_real);
            for(int i=new_files;i<mainBlock.end;i++){

                child_pid=fork();
                if(child_pid==0){
                    merge_files(&mainBlock,i);
                    break;    
                }                
                
            }

            while((wpid=wait(&status))>0)

            clock_gettime(CLOCK_REALTIME,&stop_real); 
            times(&end_tms);

            merges.real+=(stop_real.tv_sec-start_real.tv_sec)+(double)(stop_real.tv_nsec-start_real.tv_nsec)/(double)BILLION;
            merges.user += (end_tms.tms_cutime - start_tms.tms_cutime);
            merges.system += (end_tms.tms_cstime - start_tms.tms_cstime);

                
        }
    }
    delete_main_block(&mainBlock);
    printf( "Total time of merges:\n real: %lf system: %lf user: %lf\n", merges.real,(double)merges.system/ticks,(double)merges.user/ticks);
    return 0;
}