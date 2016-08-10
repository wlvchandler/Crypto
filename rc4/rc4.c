/*
*
* compile with makefile or: 
*           $ gcc -std=c99 -o rc4 -Wall -Wextra -pedantic argutils.c rc4.c
* 
* example execution using key `mykey`, plaintext file `test.txt`, and ciphertext file `testout.txt`:
*           $ rc4 -K mykey -M test.txt -O testout.txt
*/

#include "argutils.h"


static inline void swap (int* x, int* y)
{
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
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
    if (args.key)   {
        if (strstr(args.key, ".key") != NULL || strstr(args.key, ".txt") != NULL)
            key = parse_file(args.key);
        else
            key = args.key;
    } else  {
        printf("No key provided (use `-K` option to provide text or a .key file). Exiting...\n");
        return -2;
    }

    printf("In main: got key:\t%s\n", key);

//Get message
    if (args.iFile) {
        if (strstr(args.iFile, ".txt") != NULL)
            message = parse_file(args.iFile);
        else
            message = args.iFile;
    } else {
        printf("No Message (use `-m` option to provide text or `-M` to provide a .txt file). Exiting...\n");
        return -3;
    }


    printf("In main: got message:\t%s\n", message);


//Output file name
    outFile = args.oFile == NULL ? "out" : args.oFile;

    printf("In main: output to:\t%s\n", outFile);

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