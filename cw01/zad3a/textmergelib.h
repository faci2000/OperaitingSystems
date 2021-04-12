#ifndef textmergelib
#define textmergelib

struct LinesBlock {
    char **lines;
    char *text;
    int linesCount;
    char *fileNameA;
    char *fileNameB;
};

struct BlocksArray {
    struct LinesBlock **mainBlocksArray;
    int end;
    int size;
};

struct BlocksArray create_new_main_blocks_array(int size);
void add_lines_block_to_main_array(struct BlocksArray* blocksArray,char *fileNameA, char *fileNameB);
char** define_files_sequence(char* files_names);
void set_file_names(struct BlocksArray* blocksArray,char **fileNames,int pairsNo);
struct LinesBlock* create_new_lines_block(char *fileNameA, char *fileNameB);
void add_merged_lines_to_main_blocks_array(struct LinesBlock *linesBlock);
void merge_files(struct BlocksArray* blocksArray,int i);
int get_numbers_of_lines_in_block(struct BlocksArray* blocksArray,int index);
void delete_lines_block(struct BlocksArray* blocksArray,int index);
void delete_line_from_lines_block(struct BlocksArray* blocksArray,int blockIndex,int lineIndex);
void print_lines_blocks(struct BlocksArray* blocksArray);
void delete_all_lines_blocks(struct BlocksArray* blocksArray);
void delete_main_block(struct BlocksArray* blocksArray);

#endif