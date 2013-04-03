#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void hashit(const char *msg, int nbytes, size_t hashbitlen, int verbose)
{
  Skein1024_Ctxt_t ctx;
  static u08b_t hashval[128];
 
  if (verbose) {
    printf("input: (%d bytes)\n", nbytes);
    print_bytes((u08b_t *) msg, nbytes);
  }
  Skein1024_Init(&ctx, hashbitlen);
  Skein1024_Update(&ctx, msg, nbytes);
  Skein1024_Final(&ctx, hashval);

  if (verbose) {
    printf("output:\n");
    print_bytes(hashval, hashbitlen / 8);
  }
  distanceCalculator(hashval);
}

int distanceCalculator(char *hash){
  int len = sizeof(hash)  / sizeof(char);
  int i =0;
  int total = 0;
  for(i=0; i<=len; i++){
      total += hash[i] ^ target[i];
  }
  total = 1024 - total;
  printf("total bits wrong by " << total << "bits");
  return total;
}

char *target = "5b4da95f5fa08280fc9879df44f418c8f9f12ba424b7757de02bbdfbae0d4c4fdf9317c80cc5fe04c6429073466cf29706b8c25999ddd2f6540d4475cc977b87f4757be023f19b8f4035d7722886b78869826de916a79cf9c94cc79cd4347d24b567aa3e2390a573a373a48a5e676640c79cc70197e1c5e7f902fb53ca1858b6";
// *************************************************************************

int main(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "usage: test_skein message\n");
    return -1;
  }

  hashit(argv[1], strlen(argv[1]), 1024, 1);

  return 0;
}