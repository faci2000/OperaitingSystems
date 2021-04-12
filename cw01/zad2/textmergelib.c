#include "textmergelib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>



struct BlocksArray create_new_main_blocks_array(int size){
    struct BlocksArray newArray;

    newArray.mainBlocksArray = (struct LinesBlock**) calloc(size,sizeof(struct LinesBlock*));
    newArray.end = 0;
    newArray.size=size;

    return newArray;
}

struct LinesBlock* create_new_lines_block(char *fileNameA, char *fileNameB){
    struct LinesBlock* newLinesBlock = (struct LinesBlock*)malloc(sizeof(struct LinesBlock));

    int fileNameASize=0;
    while(fileNameA[fileNameASize]!='\0')
        fileNameASize++;

    int fileNameBSize=0;
    while(fileNameB[fileNameBSize]!='\0')
        fileNameBSize++;


    newLinesBlock->fileNameA = (char*) calloc(fileNameASize+1,sizeof(char));
    newLinesBlock->fileNameB = (char*) calloc(fileNameBSize+1,sizeof(char));
    newLinesBlock->linesCount=0;

    strcpy(newLinesBlock->fileNameA,fileNameA);
    strcpy(newLinesBlock->fileNameB,fileNameB);

    return newLinesBlock;
}

void add_lines_block_to_main_array(struct BlocksArray* blocksArray,char *fileNameA, char *fileNameB){
    struct LinesBlock* newLinesBlock=create_new_lines_block(fileNameA,fileNameB);
    blocksArray->mainBlocksArray[blocksArray->end]=newLinesBlock;
    blocksArray->end+=1;
}

void set_file_names(struct BlocksArray* blocksArray,char **fileNames,int pairsNo){
    
    for(int i=0;i<pairsNo*2;i+=2){
        add_lines_block_to_main_array(blocksArray,fileNames[i],fileNames[i+1]);
    }
    free(fileNames[0]);
    free(fileNames);
}

void add_merged_lines_to_main_blocks_array(struct LinesBlock *linesBlock){
    
    FILE *tempFile = fopen("temp.txt","r");
    
    fseek(tempFile,0L,SEEK_END);
    int neededMeomory = ftell(tempFile);
    fseek(tempFile, 0, SEEK_SET);
    linesBlock->text=(char*)malloc((neededMeomory+linesBlock->linesCount)*sizeof(char));//eventually +1 or +number of lines
    linesBlock->lines=(char**)calloc(linesBlock->linesCount,sizeof(char*));

    int i=0;//index in text
    char tempChar = getc(tempFile);
    for(int line=0;line<linesBlock->linesCount;line++){
        linesBlock->lines[line]=&(linesBlock->text[i]);
        while(tempChar!='\n'){
            linesBlock->text[i]=tempChar;
            tempChar=getc(tempFile);
            i++;
        }
        linesBlock->text[i]=tempChar;
        tempChar=getc(tempFile);
        i++;
        linesBlock->text[i]='\0';
        i++;
    }
    fclose(tempFile);
}

void merge_files(struct BlocksArray* blocksArray,int i){
    
    //for(int i=0;i<=blocksArray.end;i++){
        FILE *fileA;
        fileA = fopen(blocksArray->mainBlocksArray[i]->fileNameA,"r");
        FILE *fileB;
        fileB = fopen(blocksArray->mainBlocksArray[i]->fileNameB,"r");
        FILE *tempFile = fopen("temp.txt","w+");

        char charA=fgetc(fileA);
        bool fileAEnded=false;
        char charB=fgetc(fileB);
        bool fileBEnded=false;
        blocksArray->mainBlocksArray[i]->linesCount=0;
        while (!fileAEnded||!fileBEnded)
        {

            while (charA!='\n'&&charA!=EOF){
                fputc(charA,tempFile);
                charA=getc(fileA);
            }

            if(charA!=EOF){
                fputc(charA,tempFile);
                charA=getc(fileA);
                blocksArray->mainBlocksArray[i]->linesCount+=1;
            }   
            else if(!fileAEnded){
                fputc('\n',tempFile);
                blocksArray->mainBlocksArray[i]->linesCount+=1;

            }
                

            if(!fileAEnded&&charA==EOF)
                fileAEnded=true;


            while (charB!='\n'&&charB!=EOF){
                fputc(charB,tempFile);
                charB=getc(fileB);
            }

            if(charB!=EOF){
                fputc(charB,tempFile);
                charB=getc(fileB);
                blocksArray->mainBlocksArray[i]->linesCount+=1;
            }   
            else if(!fileBEnded){
                fputc('\n',tempFile);
                blocksArray->mainBlocksArray[i]->linesCount+=1;
            }
                
            if(!fileBEnded&&charB==EOF)
                fileBEnded=true;
        }
        
        fclose(fileA);
        fclose(fileB);
        fclose(tempFile);
        
        //add_merged_lines_to_main_blocks_array(blocksArray.mainBlocksArray[i]);

        
    //}
}

int get_numbers_of_lines_in_block(struct BlocksArray* blocksArray,int index){
    return blocksArray->mainBlocksArray[index]->linesCount;
}

void delete_lines_block(struct BlocksArray* blocksArray,int index){
    //free(blocksArray->mainBlocksArray[index]->lines);
    //free(blocksArray->mainBlocksArray[index]->text);
    //free(blocksArray->mainBlocksArray[index]->fileNameA);
    //free(blocksArray->mainBlocksArray[index]->fileNameB);
    free(blocksArray->mainBlocksArray[index]);//possible memory leak
    for(int i=index;i<blocksArray->end-1;i++){
        blocksArray->mainBlocksArray[i]=blocksArray->mainBlocksArray[i+1];
    }
    blocksArray->end--;
}

void delete_all_line_blocks(struct BlocksArray* blocksArray){
    for(int i=blocksArray->end-1;i>=0;i--){
        delete_lines_block(blocksArray,i);
    }
    blocksArray->end=0;
}

void delete_main_block(struct BlocksArray* blocksArray){
    delete_all_line_blocks(blocksArray);
    /*for(int i=0;i<blocksArray->size;i++){
        free(blocksArray->mainBlocksArray[i]);
    }*/
    free(blocksArray->mainBlocksArray);
}

void delete_line_from_lines_block(struct BlocksArray* blocksArray,int blockIndex,int lineIndex){
    
    //free(blocksArray->mainBlocksArray[blockIndex]->lines[lineIndex]);
    for(int i=lineIndex;i<blocksArray->mainBlocksArray[blockIndex]->linesCount-1;i++){
        blocksArray->mainBlocksArray[blockIndex]->lines[i]=blocksArray->mainBlocksArray[blockIndex]->lines[i+1];
    }
    blocksArray->mainBlocksArray[blockIndex]->linesCount--;
}

void print_lines_blocks(struct BlocksArray* blocksArray){
    
    for(int block=0;block<blocksArray->size;block++){
        printf("Merged %s and %s\n",blocksArray->mainBlocksArray[block]->fileNameA,blocksArray->mainBlocksArray[block]->fileNameB);
        for(int line=0;line<blocksArray->mainBlocksArray[block]->linesCount;line++)
            printf("%d. %s",(line+1),blocksArray->mainBlocksArray[block]->lines[line]);
    }
}

char** define_files_sequence(char* files_names){
    int size = sizeof(char)*strlen(files_names)+1;
    int iter=0;
    int files=1;
    char* files_names_text=calloc(size,sizeof(char));
    strcpy(files_names_text,files_names);
    while(files_names[iter]!='\0'){
        if(files_names[iter]==' ')
            files++;
        iter++;
    }
    char** files_names_divided =(char**) calloc(files,sizeof(char*));
    iter=0;
    files=1;
    files_names_divided[0]=&(files_names_text[0]);
    while(files_names[iter+1]!='\0'){
        if(files_names[iter]==' '&&files_names[iter+1]!=' '){
            files_names_text[iter]='\0';
            files_names_divided[files]=&(files_names_text[iter+1]);
            files++;
        }
        iter++;
    }
    return files_names_divided;
}
