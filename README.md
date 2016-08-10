My own implementations of some various cryptographic functions and ciphers. Setup as commands for now...



# RC4:
##Compilation
  - Use makefile included (not tested yet)
  - GCC (tested): `$ gcc -std=c99 -o rc4 -Wall -Wextra -pedantic argutils.c rc4.c`
  
##Running the cipher
  - `$ rc4 [-options]`
  - Required:
    - `-m`: Message on which to use cipher. Can be:
      - a filename, like `-m messageToEncrypt.txt`. So far only supports .txt format.
      - explicitly given, like `-m Please Encrypt this Message for me boss`. 
    - `-k`: Specify the key to use for encryption. Can be:
      - a filename, like `-k test_key.key`. So far only supports .txt and .key format.
      - explicitly given, like `-k A key for your thoughts, sir.`
  - Optional:
    - `-o` : Specify output file. If left out, default is a file called `out` (no extension) in current directory.

 ##Examples
  - `$ rc4 -m Encrypt this message. -k mykey -o outfile.txt`
  - `$ rc4 -k TiXsd32UooF8xiu -m message.txt`
  - `$ rc4 -k keyfile.key -m message.txt -o output.txt`

