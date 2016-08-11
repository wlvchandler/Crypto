#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned short ushort;



/*UTILS*/
#define swap(a, b)   ((&(a) == &(b)) ? (a) : ((a)^=(b),(b)^=(a),(a)^=(b)))


/*RC4*/

//Alias for rc4 encryption
char*    rc4_encrypt(const char* message, const char* key);

//Alias for rc4 decryption
char*    rc4_decrypt(const char* message, const char* key);
