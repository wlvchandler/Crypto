#include <stdilib.h>
#include <string.h>


struct arg_struct 
{
	char * iFile;
	char * oFile;
	char * key;
	int fail;
};


char* parse_argv_to_str(int argc, char** argv)
{

	char* ret;
	int size = argc-1;

	int i;
	for (i = 1; i < argc; i++)
		size += strlen(argv[i]);

	ret = malloc(size + 1);

	int k = 0;
	for (i = 1; i < argc; i++)
	{
		unsigned j = 0;
		unsigned _arglen = strlen(argv[i]);

		while (j < _arglen)
			ret[k++] = argv[i][j++];

		ret[k++] = ' ';
	}

	ret[--k] = 0;

	return ret;
}



/*TODO - more secure way to get file size*/
char* parse_file(const char* filename)
{
	FILE* fp = fopen(filename, "rb");

	/*get file size, not secure*/
	fseek(fp, 0, SEEK_END);
	size_t filesize = ftell(fp);
	rewind(fp);

	char* contents = malloc (filesize+1);
	fread(contents, sizeof(char), filesize, fp);
	contents[filesize] = 0;

	fclose(fp);

	return contents;
}



struct arg_struct parse_args(int argc, char** argv)
{

	struct arg_struct ret = {NULL, NULL, NULL, 0};

	if (argc == 1) //not enough arguments
	{
		printf("Failed to provide a message\n");
		ret.fail = 1;
		return ret;
	} 

	int i; for (i = 0; i < argc; ++i)
	{
		if (argv[i][0] != '-') 
		{
			ret.fail = 1;
			return ret;
		}

		switch (argv[i][1])
		{
			case 'M':
				printf("");
				ret.iFile = argv[++i];
				break;
			case 'O':
				ret.oFile = argv[++i];
				break;
			case 'K':
				ret.key = argv[++i];
				break;
			default:
				printf("Argument %d invalid, exiting...\n", i);
				ret.fail = 1;
				return ret;
		}
	}

	return ret;

}