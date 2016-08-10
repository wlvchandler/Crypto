#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef unsigned short ushort;



/*UTILS*/

static inline void swap (int* x, int* y);



/*RC4*/

// convert key string to array of numbers
static ushort*  convert_key(const char * key, unsigned len);

// RC4 Key-Scheduling algorithm
static void     _ksa(int S[256], const char* key);

// RC4 Pseudo-random generation algorithm
static int      _prga(int S[256]);

// Actual RC4 implementation
static char*    rc4(const char* message, const char* key, char* retStr, bool encrypt);

//Alias for rc4 encryption
extern char*    rc4_encrypt(const char* message, const char* key, char* encrypted);

//Alias for rc4 decryption
extern char*    rc4_decrypt(const char* message, const char* key, char* decrypted);
