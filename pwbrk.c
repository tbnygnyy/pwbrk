#include "pwbrk.h"

/* clean up the global-ness */
unsigned char passwd[DIGEST_LEN + 1];
unsigned char guess[DIGEST_LEN + 1];
unsigned char charArray[NUM_CHARS];
unsigned char md5_digest[DIGEST_LEN];
unsigned char md5_pw[DIGEST_LEN];
char md5String[33];
char md5PwString[33];


int idx, gIdx, aIdx;

int main() {

  printf("main: starting... \n");
  clock_t begin = clock();
  
  int rc = 0;
  rc = initProg();
  if (rc) {
    printf("main: program inialized ok\n");
  } else {
    printf("main: problem during init hombre, terminating\n");
    exit(-13);
  }

  passwd[0] = 'Z';
  passwd[1] = 'Z';
  passwd[2] = 'Z';
  passwd[3] = 'Z';
  passwd[4] = 'Z';

  printf("main: try to break %s\n", passwd);
  calc_md5(&passwd[0]);
  for (int i = 0; i < 33; i++) {
    md5PwString[i] = md5String[i];
  }
  printf("main: for pw:%s md5PwString:%s\n", passwd, md5PwString);

  idx = 0;
  guess[idx] = '1';
  gIdx = 0;
  aIdx = 0;
  if (guessMatch()) {
    printf("main:match found! passwd:%s, guess:%s\n", passwd, guess);
    printf("main:guessMatch() found a match, idx:%d, gIdx:%d, aIdx:%d\n", idx, gIdx, aIdx);
    printf("main:dump passwd\n");
    dumpStr(&passwd[0]);
    printf("main:dump guess\n");
    dumpStr(&guess[0]);
  } else {
    printf("main:no match found! passwd:%s, guess:%s\n", passwd, guess);
    printf("main:guessMatch() did not find a match, idx:%d, gIdx:%d, aIdx:%d\n", idx, gIdx, aIdx);
    printf("main:dump passwd\n");
    dumpStr(&passwd[0]);
    printf("main:dump guess\n");
    dumpStr(&guess[0]);
  }
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("main: program took %f\n", time_spent);
}
