#include "crypto.h"

// convert key string to array of numbers
static ushort*     _convert_key(const char * key, unsigned len);

// RC4 Key-Scheduling algorithm
static void        _ksa(int S[256], const char* key);

// RC4 Pseudo-random generation algorithm
static inline int  _prga(int S[256], int* i, int* j);

// Actual RC4 implementation, use one of below
static char*    rc4(const char* message, const char* key, bool encrypt);


/*******
* RC4
********/

/*Convert key string into an array of decimal ASCII identifiers*/
static ushort * _convert_key(const char * key, unsigned len)
{
     unsigned short * ret = malloc(sizeof(int) * len);

     unsigned i; for ( i = 0; i < len; ++i )
     {
        ret[i] = key[i];
     }

     return ret;
}


/*RC4 Key-scheduling algorithm*/
static void _ksa(int S[256], const char* key)
{
    int i, j = 0;
    unsigned keylen = strlen(key);

    unsigned short * keynums = _convert_key(key, keylen);

    for (i = 0; i < 256; ++i)
        S[i] = i;

    for (i = 0; i < 256; ++i)
    {
        j = (j + S[i] + keynums[i % keylen]) % 256;
        swap(S[i], S[j]);
    }

    free(keynums);
}


/*RC4 pseudo-random generation algorithm*/
static int _prga(int S[256], int* i, int* j)
{
    *i = (*i+1) % 256;
    *j = (*j+S[*i]) % 256;

    swap(S[*i], S[*j]);

    return S[(S[*i]+S[*j]) % 256];    
}


static char * rc4(const char* message, const char* key, bool encrypt)
{
    int p_array[256] = {0}; 
    int y = 0, z = 0;

    size_t msglen = strlen(message);
    size_t retlen = encrypt ? (msglen*2) : (msglen/2);

    char* retStr = malloc(retlen+1);

    //Run Key-Scheduling algorithm
    _ksa(p_array, key);

    if (!encrypt) {
        char * dst = retStr;
        char * end = retStr + retlen;
        unsigned hex;

        /*Decrypt message*/
        while (dst < end && sscanf(message, "%2x", &hex) == 1){
            *dst++ = _prga(p_array, &y, &z) ^ hex;
            message += 2;
        }

    } else {
        /*Encrypt message*/
        for (unsigned i = 0; i < msglen; ++i)
            sprintf(&retStr[i*2], "%02X", message[i] ^ _prga(p_array, &y, &z));

    }
   
    retStr[retlen] = '\0';

    return retStr;
}


char* rc4_encrypt(const char* message, const char* key)
{
    return rc4(message, key, true);
}

char* rc4_decrypt(const char* message, const char* key)
{
    return rc4(message, key, false);
}

