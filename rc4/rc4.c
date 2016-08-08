#include <string.h>
#include <stdio.h>
#include <stdlib.h>


struct arg_struct 
{
	char * iFile;
	char * oFile;
	char * key;
	int fail;
};


static inline void swap (int* x, int* y)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
} 


/*
% Parse command line arguments into one string
% Made to take key or message from command line

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
*/


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


/*TODO - more secure way to get file size*/
static char* parse_file(const char* filename)
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


/*Convert key string into an array of decimal ASCII identifiers*/
static unsigned short * convert_key(const char * key, unsigned len)
{
	 unsigned short * ret = malloc(sizeof(int) * len);

	 unsigned i; for ( i = 0; i < len; ++i )
	 {
	 	ret[i] = key[i];
	 }

	 return ret;
}


/*RC4 Key-scheduling algorithm*/
void _ksa(int S[256], const char* key)
{
	int i, j = 0;
	unsigned keylen = strlen(key);

	unsigned short * keynums = convert_key(key, keylen);

	for (i = 0; i < 256; ++i)
		S[i] = i;

	for (i = 0; i < 256; ++i)
	{
		j = (j + S[i] + keynums[i % keylen]) % 256;
		swap(&S[i], &S[j]);
	}

	free(keynums);
}


/*RC4 pseudo-random generation algorithm*/
int _prga(int S[256])
{
	static int i = 0;
	static int j = 0;

	i = (i+1) % 256;
	j = (j+S[i]) % 256;

	swap(&S[i], &S[j]);

	return S[(S[i]+S[j]) % 256];	
}


void RC4encrypt(const char* message, const char* key, FILE* outFile)
{
	int p_array[256] = {0};

	_ksa(p_array, key);

	unsigned i; for (i = 0; i < strlen(message); ++i)
	{
		fprintf(outFile, "%02X", message[i] ^ _prga(p_array));
	}

	fprintf(outFile, "\n");
}


int main(int argc, char** argv)
{

	struct arg_struct args = parse_args(argc, argv);

	if (args.fail) return -1;

	char * key;
	char * message;
	char * outFile;


//Get key
	if (args.key)	{
		if (strstr(args.key, ".key") != NULL)
			key = parse_file(args.key);
		else
			key = args.key;
	} else 	{
		printf("No key provided (use `-K` option to provide text or a .key file). Exiting...\n");
		return -2;
	}


//Get message
	if (args.iFile) {
		if (strstr(args.iFile, ".txt") != NULL)
			message = parse_file(args.iFile);
		else
			message = args.iFile;
	} else {
		printf("No Message (use `-M` option to provide text or a .txt file). Exiting...\n");
		return -3;
	}


//Output file name
	outFile = args.oFile == NULL ? "out" : args.oFile;
	FILE * ofp = fopen(outFile, "w");

	if (ofp == NULL)
	{ 
		printf("Failed to open output file. Exiting..."); 
		return -4; 
	}


//Perform encryption
	RC4encrypt(message, key, ofp);


//Release pointers if necessary 
	free(key);
	free(message);
	fclose(ofp);

	return 0;
	
}