//
//  Encryp.c
//  CSC152 Project
//
//  Created by Qixuan Chai on 9/23/15.
//
//


#include "chacha20_simple.h"//implementation for the program
#include <string.h>//memcpy a
#include <stdio.h>//standard printf and fread and fwrite
#include <stdint.h>//for uint8_t (unsigned int with size of 8 bit _ specifys type)


int main(int argc, char **argv) {//** for string array and * is pointed to the character string.
    //argc= argument counter and argv is argument vector - basically arugments.
    int a;
    uint8_t plain[64];
    uint8_t nonce[8];
    uint8_t key[32];
    chacha20_ctx chacha;//set up chacha as object for use later -combined of nonce and key. Also holds extra stuff same as java
    int done=0;
    uint8_t crypt[64];// created for encryted buffer
    
    
    
    /* verify a key is given */
    if (argc != 2 || strlen(argv[1]) > 32) {
        fprintf(stderr, "usage: %s <key of up to 32 characters>\n", argv[0]);
        return EXIT_FAILURE;
    }
    //once verified we can put keys and nonce into the array.
    
    FILE* f = fopen("/dev/urandom", "rb");//open randon number generator to generate random bytes
    //f points to a file and is declared above
    fread(nonce, 1, 8, f);//read from file f and insert into nonce
    fwrite(nonce, 1, 8, stdout);

    //explanation to argc and argv is below
    
/* $.decrypt "key"
    argc = 2
    argv = {"./decrypt", "key"}
 */

 
 
    fclose(f);//close file with vairable f
    memset(key, 0, 32);//resetting the memory to 0- clearing the full length of 32 bytes of buffer
    memcpy(key, argv[1],strlen(argv[1]));//copying the string lenth of the argument 1 into key
    
    chacha20_setup(&chacha, key, 32, nonce);// chacha is object and 32 is so that the implementation knows that we use 32-bytes of key
    //putting both the key and the nonce into the object //constructor. setting up the object.
    while (!done) {//
        
        size_t len_read = fread(plain, 1, 64, stdin);//returns the length read into the plain array
        
        chacha20_encrypt(&chacha, plain, crypt, len_read);//encrypt the plain into crypt through chacha with the length read
        
        fwrite(crypt, 1, len_read,stdout);//writes out the amount of crypt with the length read to the screen
        
        if (len_read!= 64) {//if length read isnt 64 then return done as 1 which would lead to completing the while loop.
            done=1;
        }
    }
    //to link file gcc -o Encryp Encryp.o chacha20_simple.o
    //-c to compile each to an object file seperately.
}

