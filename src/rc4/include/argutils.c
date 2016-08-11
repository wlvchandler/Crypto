#include "argutils.h"


bool clean_arg_struct(struct arg_struct* as)
{
    as->iFile = NULL; 
    as->oFile = NULL;
    as->key = NULL;

    return (as->iFile || as->oFile || as->key) ? false : true;
}


char* parse_argv_to_str(int* cidx, int argc, char** argv)
{

    char* ret;
    int size = argc-1;

    int i;
    for (i = *cidx; i < argc && argv[i][0] != '-'; i++)
        size += strlen(argv[i]);

    ret = malloc(size + 1);

    int k = 0;
    for (; *cidx < i; (*cidx)++)
    {
        unsigned j = 0;
        unsigned _arglen = strlen(argv[*cidx]);

        while (j < _arglen)
           ret[k++] = argv[*cidx][j++];

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

    struct arg_struct ret = {NULL, NULL, NULL, false, true, true};

    if (argc == 1) //not enough arguments
    {
        printf("Failed to provide a message\n");
        ret.fail = 1;
        return ret;
    } 

    int i; for (i = 1; i < argc; ++i)
    {

        if (argv[i][0] != '-') 
        {
            printf("Need switch `-*, exiting.\n`");
    		ret.fail = true;
    		return ret;
        }

        switch (argv[i][1])
        {
            case 'h':   //output in console instead of file
                ret.outToFile = false;
                break;
            case 'd':   //decrypt
                ret.encrypt = false;
                break;
            case 'm':   //message (.txt file or cl arg)
                i++;
                ret.iFile = parse_argv_to_str(&i, argc, argv);
                --i;
                break;
            case 'o':   //output file destination
                ret.oFile = argv[++i];
                break;
            case 'k':   //key (.key/.txt file or cl arg)
                i++;
                ret.key = parse_argv_to_str(&i, argc, argv);
                --i;
                break;           
            default:
                printf("Argument %d invalid, exiting...\n", i);
                ret.fail = true;
                return ret;
        }
    }

    return ret;

}