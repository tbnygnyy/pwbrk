#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/params.h>

#define NUM_CHARS 256
#define MD5_DIGEST_SIZE 64
#define DIGEST_LEN 16

extern unsigned char guess[DIGEST_LEN + 1];
extern unsigned char passwd[DIGEST_LEN + 1];
extern unsigned char charArray[NUM_CHARS];
extern unsigned char md5_digest[DIGEST_LEN];
extern unsigned char md5_pw[DIGEST_LEN];
extern int idx, gIdx, aIdx;
extern char md5String[33];
extern char md5PwString[33];

int initProg(void);
int guessMatch(void);
void calc_md5(unsigned char *);
void dumpStr(unsigned char *);
int checkMatch(void);
