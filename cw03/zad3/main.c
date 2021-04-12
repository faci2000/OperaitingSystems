#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <stdlib.h>
#include<sys/wait.h>


bool check_if_contains(char* filename,char* searched_word){
    FILE* file=fopen(filename,"r");
    char* word = (char*)malloc(2);
    int i=0;
    char readedChar='\0';
    int read=fread(&readedChar,1,1,file);
    while(read==1){
        
        while(read==1&&readedChar!='\n'&&readedChar!=EOF&&readedChar!=' '&&readedChar!='.'&&readedChar!=','&&readedChar!=';'){
            word=realloc(word, i+2);
            word[i]=readedChar;
            i++;
            read=fread(&readedChar,1,1,file);
        }
        word[i]='\0';
        if(strcmp(word,searched_word)==0){
            free(word);
            fclose(file);
            return true;
        }

        if(read==1&&readedChar!=EOF){
            read=fread(&readedChar,1,1,file);
        }
           
        i=0;
    }
    free(word);
    fclose(file);
    return false;
}

bool check_if_txt(char* filename){
    return (filename[strlen(filename)-1]=='t')&&(filename[strlen(filename)-2]=='x')&&(filename[strlen(filename)-3]=='t')&&(filename[strlen(filename)-4]=='.');
}


void search_dirs(char* dir_path,int depth,int max_depth,char* searched_word,char* init,char* main_dir){

    if(depth>max_depth)
        return;

    DIR *dir = opendir(dir_path);
    if(dir==NULL){
        printf("Error opening directory.\n");
        return;
    }
    
    struct dirent *readed_item=readdir(dir);
    struct stat item_stat;
    

    while (readed_item!=NULL){

        char* new_path=(char*)calloc(strlen(dir_path)+strlen(readed_item->d_name)+5,1);
        strcpy(new_path,dir_path);
        strcat(new_path,"/");
        strcat(new_path,readed_item->d_name);
        
        lstat(new_path,&item_stat);

        if (strcmp(readed_item->d_name, ".") == 0 || strcmp(readed_item->d_name, "..") == 0) {
            readed_item = readdir(dir);
            continue;
        }
        if(S_ISDIR(item_stat.st_mode)){
            pid_t child;
            child=fork();
            if(child==0){
                search_dirs(new_path,depth+1,max_depth,searched_word,init,main_dir);
                free(new_path);
                free(init);
                exit(0);
            }
        }else if(S_ISREG(item_stat.st_mode)&&check_if_txt(readed_item->d_name)){
            //printf("%s\n",readed_item->d_name);
            if(check_if_contains(new_path,searched_word)){
                printf("%s %d\n",strstr(new_path,main_dir),(int)getpid());
            }

        }
        readed_item=readdir(dir);
        free(new_path);
    }
    return;
    
}

int main(int argc,char** argv){

    char* init_path;
    int depth;
    if(argc!=4){
        printf("Invalid number of arguments!\n");
        return -1;
    }else{
        init_path=(char*)calloc(500,1);
        strcpy(init_path,realpath(argv[1],NULL));
        depth=atoi(argv[3]);
        if(depth<=0){
            printf("The given depth is invalid!");
            return -1;
        }
    }
    pid_t child_pid,wpid;
    int status=0;
    
    child_pid = fork();
    if(child_pid==0){
        search_dirs(init_path,1,depth,argv[2],init_path,argv[1]);
    }
        
    
    while((wpid=wait(&status))>0)
    free(init_path);
    return 0;   
}