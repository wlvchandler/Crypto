#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static inline void swap (int* x, int* y)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
} 


/*
	Parse command line arguments into one string
	Made to take key or message from command line
*/
/*
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


void RC4encrypt(const char* message, const char* key)
{
	int p_array[256] = {0};

	_ksa(p_array, key);

	printf("%s\n", message);

	unsigned i; for (i = 0; i < strlen(message); ++i)
	{
		printf("%02X", message[i] ^ _prga(p_array));
	}

	printf("\n");
}


int main(int argc, char** argv)
{

	if (argc == 1)
	{
		printf("Failed to provide a key\n");
		return -1;
	}

	char * key = parse_argv(argc,argv);

	RC4encrypt("This message is encrypted", key);

	free(key);

	return 0;
}