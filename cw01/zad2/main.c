#include<stdio.h>
#include"textmergelib.h"
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<sys/times.h>
#include <inttypes.h>
#include  <unistd.h>

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
    struct measuredTime saves;
    saves.real=0;
    saves.system=0;
    saves.user=0; 
    struct measuredTime deletions;
    deletions.real=0;
    deletions.system=0;
    deletions.user=0; 

    bool created=false;
    struct BlocksArray mainBlock;


    for(int i=1;i<argc;i++){    
        if(strcmp("create_table",argv[i])==0){
            int size = atoi(argv[i+1]);
            i++;
            if(size<=0){
                printf("The given size of main block is invalid.");
                return -1;
            }else{
                mainBlock = create_new_main_blocks_array(size);
                created=true;
            }
        }else if(strcmp("merge_files",argv[i])==0){
            if(!created){
                printf("The main block wasn't created, create one first.");
                return -1;
            }
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
            if(pairs>mainBlock.size-mainBlock.end){
                printf("Main block has only: %d free, whereas %d pairs of files were given.",mainBlock.size-mainBlock.end,pairs);
                return -1;
            }
            int new_files=mainBlock.end;

            set_file_names(&mainBlock,define_files_sequence(fileNames),pairs);

            free(fileNames);
            
            for(int i=new_files;i<mainBlock.end;i++){

                times(&start_tms);
                clock_gettime(CLOCK_REALTIME,&start_real);
                merge_files(&mainBlock,i);
                clock_gettime(CLOCK_REALTIME,&stop_real); 
                times(&end_tms);

                merges.real+=(stop_real.tv_sec-start_real.tv_sec)+(double)(stop_real.tv_nsec-start_real.tv_nsec)/(double)BILLION;
                merges.user += (end_tms.tms_utime - start_tms.tms_utime);
                merges.system += (end_tms.tms_stime - start_tms.tms_stime);

                times(&start_tms);
                clock_gettime(CLOCK_REALTIME,&start_real);
                add_merged_lines_to_main_blocks_array(mainBlock.mainBlocksArray[i]);
                clock_gettime(CLOCK_REALTIME,&stop_real); 
                times(&end_tms);

                saves.real+=(stop_real.tv_sec-start_real.tv_sec)+(double)(stop_real.tv_nsec-start_real.tv_nsec)/(double)BILLION;
                saves.user += (end_tms.tms_utime - start_tms.tms_utime);
                saves.system += (end_tms.tms_stime - start_tms.tms_stime);
                
            }
                
        }else if(strcmp("remove_block",argv[i])==0){
            if(!created){
                printf("The main block wasn't created, create one first.");
                return -1;
            }
            i++;
            int index = atoi(argv[i]);

            if(index<0){
                printf("The given index of main block is invalid.");
                return -1;
            }

            
            times(&start_tms);
            clock_gettime(CLOCK_REALTIME,&start_real);
            delete_lines_block(&mainBlock,index);
            clock_gettime(CLOCK_REALTIME,&stop_real); 
            times(&end_tms);

            deletions.real+=(stop_real.tv_sec-start_real.tv_sec)+(double)(stop_real.tv_nsec-start_real.tv_nsec)/(double)BILLION;
            deletions.user += (end_tms.tms_utime - start_tms.tms_utime);
            deletions.system += (end_tms.tms_stime - start_tms.tms_stime);
        }else if(strcmp("remove_row",argv[i])==0){
            if(!created){
                printf("The main block wasn't created, create one first.");
                return -1;
            }
            i++;
            int blockIndex = atoi(argv[i]);

            if(blockIndex<0||mainBlock.end<=blockIndex){
                printf("The given index of main block is invalid or main block is empty.");
                return -1;
            }
            i++;
            int rowIndex = atoi(argv[i]);

            if(rowIndex<0){
                printf("The given index of main block is invalid.");
                return -1;
            }

            if(mainBlock.mainBlocksArray[blockIndex]->linesCount<=rowIndex){
                printf("The given index of row does not exist.");
                return -1;
            }

            times(&start_tms);
            clock_gettime(CLOCK_REALTIME,&start_real);
            delete_line_from_lines_block(&mainBlock,blockIndex,rowIndex);
            clock_gettime(CLOCK_REALTIME,&stop_real); 
            times(&end_tms);

            deletions.real+=(stop_real.tv_sec-start_real.tv_sec)+(double)(stop_real.tv_nsec-start_real.tv_nsec)/(double)BILLION;
            deletions.user += (end_tms.tms_utime - start_tms.tms_utime);
            deletions.system += (end_tms.tms_stime - start_tms.tms_stime);

            
        }
    }
    delete_main_block(&mainBlock);
    printf( "Total time of merges:\n real: %lf system: %lf user: %lf\n", merges.real,(double)merges.system/ticks,(double)merges.user/ticks);
    printf( "Total time of block saves:\n real: %lf system: %lf user: %lf\n", saves.real,(double)saves.system/ticks,(double)saves.user/ticks);
    printf( "Total time of blocks deletions:\n real: %lf system: %lf user: %lf\n", deletions.real,(double)deletions.system/ticks,(double)deletions.user/ticks);
    printf( "Total time :\n real: %lf system: %lf user: %lf\n", deletions.real+merges.real+saves.real,(deletions.system+merges.system+saves.system)/(double)ticks,(deletions.user+merges.user+saves.user)/(double)ticks);
    return 0;
}