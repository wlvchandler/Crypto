#include "argutils.h"

char* parse_argv_to_str(int* cidx, int argc, char** argv)
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

	*argc = i;

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

	int i; for (i = 1; i < argc; ++i)
	{

		printf("Parsing args: argv[%d] = %s\n", i, argv[i]);

		if (argv[i][0] != '-') 
		{
            printf("Need switch `-*, exiting.\n`");
			ret.fail = 1;
			return ret;
		}

		switch (argv[i][1])
		{
			case 'M':
				ret.iFile = argv[++i];
				printf("Option is -M, filename: %s\n", ret.iFile);
				break;
			case 'm':
				ret.iFile = parse_argv_to_str(&i, argc, argv);
				printf("Option is -m, message: %s\n", ret.iFile);
				break;
			case 'O':
				ret.oFile = argv[++i];
				printf("Option is -O, filename: %s\n", ret.oFile);
				break;
			case 'K':
				ret.key = argv[++i];
				printf("Option is -K, key: %s\n", ret.key);
				break;
			default:
				printf("Argument %d invalid, exiting...\n", i);
				ret.fail = 1;
				return ret;
		}
	}

	return ret;

}