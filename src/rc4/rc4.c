#include "include/argutils.h"
#include "include/crypto.h"


void encrypt(const char* message, const char* key, FILE* outFile)
{
    char* encrypted = rc4_encrypt(message, key);

    if (outFile)
        fprintf(outFile, "%s", encrypted);
    else
        printf("%s", encrypted);

    free(encrypted);
}

void decrypt(const char* message, const char* key, FILE* outFile)
{
    char* decrypted = rc4_decrypt(message, key);

    if (outFile)
        fprintf(outFile, "%s", decrypted);
    else
        printf("%s", decrypted);

    free(decrypted);
}



int main(int argc, char** argv)
{

    struct arg_struct args = parse_args(argc, argv);

    if (args.fail) return -1;

    char *key, *message, *outFile;
    FILE * ofp;


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


    //Output method
    if (args.outToFile){
        outFile = args.oFile == NULL ? "out" : args.oFile;
        ofp = fopen(outFile, "w");

        if (ofp == NULL) { 
            printf("Failed to open output file. Exiting..."); 
            return -4; 
        }

    } else ofp = NULL;


    //Use cipher
    if (args.encrypt)
        encrypt(message, key, ofp);
    else
        decrypt(message, key, ofp);


    //Release pointers if necessary
    clean_arg_struct(&args);
    free(key);
    free(message);
    fclose(ofp);

    return 0;
    
}