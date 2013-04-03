#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "skein.h"


void print_bytes(u08b_t *bytes, int num_bytes)
{
  int i = 0;
  for (i = 0; i < num_bytes; i++) {
    printf("%02x", bytes[i]);
  }
  printf("\n");
}


// *************************************************************************

int hashit(const char *msg, int nbytes, size_t hashbitlen, int verbose)
{
  Skein1024_Ctxt_t ctx;
  static u08b_t hashval[128];
 
  if (verbose) {
    //printf("input: (%d bytes)\n", nbytes);
    //print_bytes((u08b_t *) msg, nbytes);
  }
  Skein1024_Init(&ctx, hashbitlen);
  Skein1024_Update(&ctx, msg, nbytes);
  Skein1024_Final(&ctx, hashval);

  if (verbose) {
    //printf("output:\n");
    //print_bytes(hashval, hashbitlen / 8);
  }
  return distanceCalculator(hashval);
}

int distanceCalculator(unsigned char *hash){
  unsigned char *target = "\x5b\x4d\xa9\x5f\x5f\xa0\x82\x80\xfc\x98\x79\xdf\x44\xf4\x18\xc8\xf9\xf1\x2b\xa4\x24\xb7\x75\x7d\xe0\x2b\xbd\xfb\xae\x0d\x4c\x4f\xdf\x93\x17\xc8\x0c\xc5\xfe\x04\xc6\x42\x90\x73\x46\x6c\xf2\x97\x06\xb8\xc2\x59\x99\xdd\xd2\xf6\x54\x0d\x44\x75\xcc\x97\x7b\x87\xf4\x75\x7b\xe0\x23\xf1\x9b\x8f\x40\x35\xd7\x72\x28\x86\xb7\x88\x69\x82\x6d\xe9\x16\xa7\x9c\xf9\xc9\x4c\xc7\x9c\xd4\x34\x7d\x24\xb5\x67\xaa\x3e\x23\x90\xa5\x73\xa3\x73\xa4\x8a\x5e\x67\x66\x40\xc7\x9c\xc7\x01\x97\xe1\xc5\xe7\xf9\x02\xfb\x53\xca\x18\x58\xb6";
  
  int i =0;
  unsigned int total = 0;
  unsigned int temp = 0;
  for(i=0; i<128; i++)
      { temp = hash[i] ^ target[i];
        while(temp>0){
            if(temp & 0x1) total ++;
                temp = temp /2;
        };
      };
  
  unsigned int bitsToBreak = 400;
  if(total < bitsToBreak){
        printf("total bits wrong by %d bits\n", total);
        printf("\n\n\nSTARTMESSaGE:%sENDMESSAGE\n\n\n",hash);
        return 0;
  }
     
  return total;
}


// *************************************************************************

int main(int argc, char **argv)
{
  srand(time(NULL));
  u08b_t message[128];
  int i = 0;
  long tries = 0;
  while(1){
      for(i=0;i<127;i++){
          message[i] = rand();
      }
      
        if(hashit(message, 128, 1024, 0)==0){
            return 0;
        }
        tries ++;
        if(tries % 1000 == 0){
            printf("\n tried %d times \n seed: %d",tries, rand());
            //srand(time(NULL));
        }
  }
  return 0;
}

