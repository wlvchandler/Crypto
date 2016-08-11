#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


struct arg_struct 
{
    char * iFile;
    char * oFile;
    char * key;
    bool fail;
    bool encrypt;
};


extern char* parse_argv_to_str(int* cidx, int argc, char** argv);

extern char* parse_file(const char* filename);

extern struct arg_struct parse_args(int argc, char** argv);