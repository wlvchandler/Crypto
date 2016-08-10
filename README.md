My own implementations of some various cryptographic functions and ciphers. 

# Cryptography function library
  In directory `crypto`, contains all functions/ciphers needed for includes.


# RC4:

##Using library functions:
  - Both functions work exactly the same, and very straightforward. Replace "XX" with "en" or "de" for encryption/decryption.
  - `char* rc4_XXcrypt(const char* message, const char* key)`
    - `message` : the message to be encrypted/decrypted
    - `key` : the key to use for the process
    - Return value is the encrypted/decrypted string.
  Example:
    ```C
    
    char* encrypted = rc4_encrypt("Hello, World!", "1234567890");
    char* decrypted = rc4_decrypt(encrypted, "1234567890");
    ```


##Running the cipher as a command
  - `rc4/bin/` has executables (just windows for now)
  - Compilation:
    - Use makefile included (not tested yet)
    - GCC (tested): `$ gcc -std=c99 -O3 -o rc4 -Wall -Wextra -pedantic argutils.c rc4.c`
  - Usage: `$ rc4 -m message -k key [-o outputFile]`
  - Required:
    - `-m`: Message on which to use cipher. Can be:
      - a filename, like `-m messageToEncrypt.txt`. So far only supports .txt format.
      - explicitly given, like `-m Please Encrypt this Message for me boss`. 
    - `-k`: Specify the key to use for encryption. Can be:
      - a filename, like `-k test_key.key`. So far only supports .txt and .key format.
      - explicitly given, like `-k A key for your thoughts, sir.`
  - Optional:
    - `-o` : Specify output file. If left out, default is a file called `out` (no extension) in current directory.
  - Examples
    - `$ rc4 -m Encrypt this message. -k mykey -o outfile.txt`
    - `$ rc4 -k TiXsd32UooF8xiu -m message.txt`
    - `$ rc4 -k keyfile.key -m message.txt -o output.txt`

