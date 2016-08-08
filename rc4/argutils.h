#include <stdlib.h>
#include <string.h>


struct arg_struct 
{
	char * iFile;
	char * oFile;
	char * key;
	int fail;
};


extern char* parse_argv_to_str(int argc, char** argv);

extern char* parse_file(const char* filename);

extern struct arg_struct parse_args(int argc, char** argv);