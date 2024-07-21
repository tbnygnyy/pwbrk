#include "pwbrk.h"

#define SMALL_A_IN_DEC 97
#define CAPITAL_A_IN_DEC 65

int initProg () {
 
  printf("initProg:starting...\n");
/*
  printf("initProg: length of passwd string:%ld\n", sizeof(passwd));
  printf("initProg: length of guess string:%ld\n", sizeof(guess));
  printf("initProg: length of charArray string:%ld\n", sizeof(charArray));
*/
  int tIdx = 0;
  for (int i = 0; i <= 9; i++) {
    charArray[tIdx++] = i + '0';
  }
  
  for (int i = SMALL_A_IN_DEC; i < SMALL_A_IN_DEC+26; i++) {
    charArray[tIdx++] = i;
  }
  
  for (int i = CAPITAL_A_IN_DEC; i < CAPITAL_A_IN_DEC+26; i++) {
    charArray[tIdx++] = i;
  }
  charArray[tIdx] = '\0';
/*
  printf("initProg: array dump: tIdx now:%d\n", tIdx);
  printf("initProg: length of charArray:%ld, charArray:%s\n", sizeof(charArray), charArray);
  printf("initProg: dump complete:\n");
*/
  for (int i = 0; i < DIGEST_LEN; i++) {
    guess[i] = '\0';
  }
/*  printf("initProg: guess: %s, length of guess: %ld\n", guess, sizeof(guess)); */
  
  for (int i = 0; i < DIGEST_LEN; i++) {
    passwd[i] = '\0';
  }
/*  printf("initProg: passwd: %s, length of passwd: %ld\n", passwd, sizeof(passwd)); */
  
  return 1;
}

int guessMatch () {
  
  printf("guessMatch: starting...\n");

  for (int a = 0; a < strlen(charArray); a++) {
    if (passwd[9] == '\0') {
      printf("guessMatch has end of string in position 9\n");
      goto no9;
    } else {
      guess[9] = charArray[a];
    }
    no9:
    for (int b = 0; b < strlen(charArray); b++) {
      if (passwd[8] == '\0') {
        printf("guessMatch has end of string in position 8\n");
        goto no8;
      } else {
        guess[8] = charArray[b];
      }
      no8:
      for (int c = 0; c < strlen(charArray); c++) {
        if (passwd[7] == '\0') {
          printf("guessMatch has end of string in position 7\n");
          goto no7;
        } else {
          guess[7] = charArray[c];
        }
        no7:
        for (int d = 0; d < strlen(charArray); d++) {
          if (passwd[6] == '\0') {
            printf("guessMatch has end of string in position 6\n");
            goto no6;
          } else {
            guess[6] = charArray[d];
          }
          no6:
          for (int e = 0; e < strlen(charArray); e++) {
            if (passwd[5] == '\0') {
              printf("guessMatch has end of string in position 5\n");
              goto no5;
            } else {
              guess[5] = charArray[e];
              printf("guessMatch: working on %c in pos:%d\n", guess[5], 5);
            }
            no5:
            for (int f = 0; f < strlen(charArray); f++) {
              if (passwd[4] == '\0') {
                printf("guessMatch has end of string in position 4\n");
                goto no4;
              } else {
                guess[4] = charArray[f];
              }
              no4:
              for (int g = 0; g < strlen(charArray); g++) {
                if (passwd[3] == '\0') {
                  printf("guessMatch has end of string in position 3\n");
                  goto no3;
                } else {
                  guess[3] = charArray[g];
                }
                no3:
                for (int h = 0; h < strlen(charArray); h++) {
                  if (passwd[2] == '\0') {
                    printf("guessMatch has end of string in position 2\n");
                    goto no2;
                  } else {
                    guess[2] = charArray[h];
                  }
                  no2:
                  for (int i = 0; i < strlen(charArray); i++) {
                    if (passwd[1] == '\0') {
                      printf("guessMatch has end of string in position 1\n");
                      goto no1;
                    } else {
                      guess[1] = charArray[i];
                    }
                    no1:
                    if (checkMatch()) {
                      printf("guessMatch: match found for guess:%s and passwd:%s\n", guess, passwd);
                      return 1;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

int checkMatch(void) {
  
//  printf("checkMatch: starting\n");
  
  int match;
  for (int i = 0; i < strlen(charArray); i++) {
//    printf("checkMatch: for loop i:%d\n", i);
    guess[0] = charArray[i];
    calc_md5(guess);
//    printf("checkMatch: guess:%s pw:%s md5String:%s, md5PwString:%s\n", 
//            guess, passwd, md5String, md5PwString);
//    printf("checkMatch: idx:%d, gIdx:%d, aIdx:%d\n", idx, gIdx, aIdx);
    match = 1;
    for (int j = 0; j < 33; j++) {
//      printf("checkMatch: guess-md5:%c  pw-md5:%c index:%d\n", 
//              md5String[j], md5PwString[j], j);
      if (md5String[j] != md5PwString[j]) {
//        printf("checkMatch: failed at position:%d for guess:%s\n", j, guess);
        match = 0;
        break;
      }
    }
    if (match) {
      printf("checkMatch: returning with match found for guess:%s and passwd:%s\n", guess, passwd);
      return match;
    }
    /* usleep( 20000 ); */
  }
//  printf("checkMatch: returning, no match found idx:%d, guess[idx]: %c\n", idx, guess[idx]);
  return match;
}

void calc_md5(unsigned char *buf) {
/*  printf("calc_md5: starting...\n"); */

  EVP_MD_CTX *mdctx;
  unsigned int md5_digest_len = EVP_MD_size(EVP_md5());

  if (md5_digest_len > DIGEST_LEN) {
    printf("calc_md5: ERROR: md5_digest_len: %d is greater than DIGEST_LEN: %d/n", 
            md5_digest_len, DIGEST_LEN);
    exit(-1);
  }
  // MD5_Init
  mdctx = EVP_MD_CTX_new();
  EVP_DigestInit_ex(mdctx, EVP_md5(), NULL);

  // MD5_Update
  EVP_DigestUpdate(mdctx, buf, sizeof(buf));

  // MD5_Final
/*  md5_digest = (unsigned char *)OPENSSL_malloc(md5_digest_len); */
  EVP_DigestFinal_ex(mdctx, &md5_digest[0], &md5_digest_len);
  EVP_MD_CTX_free(mdctx);
  
  for(int i = 0; i < 16; ++i) {
    sprintf(&md5String[i*2], "%02x", (unsigned int)md5_digest[i]);
  } 
 
/*  printf("calc_md5: md5 of %s is %s, returning...\n", buf, md5String); */
}

void dumpStr(unsigned char *str) {
 
  printf("dumpStr: starting...\n");

  int strLen = strlen(str);

  printf("dumpStr: string to dump: %s, length: %d\n", str, strLen);
  printf("dumpStr: dumped string to follow\n");
  for (int i = 0; i < strLen; i++) {
    printf("%c", str[i]); 
  }
  printf("\ndumpStr:exiting...\n");
}
