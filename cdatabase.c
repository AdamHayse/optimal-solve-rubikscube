/*
 * This file contains functions for converting permutations to 
 * indicies and vice versa.  It also contains a function that
 * extracts heuristic values from the corners pattern database.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <limits.h>
#include "cdatabase.h"
#include "mymath.h"


// Retrieve stored path length from database.
uint8_t C_path_length(uint8_t *comb, uint8_t *database) {
  unsigned index = C_get_index(comb);
  unsigned add = index / 2;
  unsigned pos = index % 2;

  // If index is odd, get right 4 bits.  Else, get left 4 bits.
  return pos ? database[add] & 0x0F : database[add] >> 4;
}

// Get index of stored combination.
unsigned C_get_index(uint8_t *comb) {
  unsigned i, add = 0;

  // Calculate which permutation number.
  unsigned long long state = 0xFEDCBA9876543210;
  for (i=0; i<7; i++) {
    int p4 = comb[i]/3 * 4;
    add += fact[7-i] * (state >> p4 & 15);
    state -= 0x1111111111111110ULL << p4;
  }

  // Scale for permutation offset.
  add *= 2187;  // power(NUM_CFACES, NUM_CORNERS-1)

  // Calculate which orientation number for orientation offset.
  for (int i=0; i<7; i++)
    add += comb[i] % NUM_CFACES * three_to_the[i];

  return add;
}

// Transform an index of the database to a combination.
void C_decode_index(unsigned index, uint8_t *comb) {
  int orient = 0, piece = 0;
  unsigned temp = index/three_to_the[7];
  unsigned long long state = 0xfedcba9876543210ULL;
  for (int i=0; i<7; i++) {
    int p4 = temp/fact[7-i] * 4;
    temp %= fact[7-i];
    comb[i] = 3*((state >> p4) & 15) + (index % three_to_the[7] / three_to_the[i]) % 3;
    piece += comb[i]/3;
    orient += comb[i];
    unsigned long long mask = ((unsigned long long)1 << p4) - 1;
    state = (state & mask) | ((state >> 4) & ~mask);
  }
  piece = 28 - piece;
  switch (orient%3) {
    case 0:  comb[7] = piece * 3; break;
    case 1:  comb[7] = piece * 3 + 2; break;
    case 2:  comb[7] = piece * 3 + 1; break;
  }
}

// Load corners database into array of size C_DB_SIZE pointed to by cdb.
void load_cdb(uint8_t *cdb) {
  int fd;
  int amount, remain;

  // Load corners database
  if ((fd = open("pattern_databases/corners.patdb", O_RDONLY)) == -1) {
    perror("Could not open corners.patdb");
    exit(1);
  }
  remain = C_DB_SIZE;
  while ((amount=read(fd, cdb+C_DB_SIZE-remain, 1048576)) != 0) {
    if (amount == -1) {
      perror("Problem reading corners.patdb");
      exit(1);
    }
    remain -= amount;
  }
  if (close(fd) == -1) {
    perror("Problem closing corners.patdb");
    exit(1);
  }
}
