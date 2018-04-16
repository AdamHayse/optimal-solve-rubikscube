#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

#include "testheuristic.h"
#include "edatabase.h"
#include "cdatabase.h"

static uint8_t temp[NUM_EDGES];


int main(void) {

  for (int64_t i=0; i<(signed)C_DB_SIZE; i++) {
    C_decode_index(i, temp);
    if (C_get_index(temp) - i != 0) {
      printf("C is not bijective.\n");
      exit(0);
    }
  }
  printf("C is bijective.\n");

  for (int64_t i=0; i<(signed long long)E_DB_SIZE; i++) {
    E1_decode_index(i, temp);
    if (E1_get_index(temp) - i != 0) {
      printf("E1 is not bijective.\n");
      exit(0);
    }
  }
  printf("E1 is bijective.\n");

  for (int64_t i=0; i<(signed long long)E_DB_SIZE; i++) {
    E2_decode_index(i, temp);
    if (E2_get_index(temp) - i != 0) {
      printf("E2 is not bijective.\n");
      exit(0);
    }
  }
  printf("E2 is bijective.\n");
}
