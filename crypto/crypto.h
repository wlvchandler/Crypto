#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned short ushort;



/*UTILS*/
#define swap(a, b)   ((&(a) == &(b)) ? (a) : ((a)^=(b),(b)^=(a),(a)^=(b)))


/*RC4*/

// convert key string to array of numbers
ushort*  convert_key(const char * key, unsigned len);

// RC4 Key-Scheduling algorithm
void     _ksa(int S[256], const char* key);

// RC4 Pseudo-random generation algorithm
int      _prga(int S[256], int* i, int* j);

// Actual RC4 implementation
char*    rc4(const char* message, const char* key, bool encrypt);

//Alias for rc4 encryption
char*    rc4_encrypt(const char* message, const char* key);

//Alias for rc4 decryption
char*    rc4_decrypt(const char* message, const char* key);
