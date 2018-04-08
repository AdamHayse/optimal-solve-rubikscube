/*
 * This file contains functions for converting permutations to 
 * indicies and vice versa.  It also contains a function that
 * extracts heuristic values from the corners pattern database.
 */

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
  for (i=7; i>0; i--) {
    int p4 = comb[i]/3 * 4;
    add += fact[i] * (state >> p4 & 15);
    state -= 0x1111111111111110ULL << p4;
  }

  // Scale for permutation offset.
  add *= 2187;  // power(NUM_CFACES, NUM_CORNERS-1)

  // Calculate which orientation number for orientation offset.
  for (i=0; i<7; i++)
    add += comb[i] % NUM_CFACES * three_to_the[i];

  return add;
}

void load_cdb(uint8_t *cdb) {
  int fd;
  if ((fd = open("pattern_databases/corners.patdb", O_RDONLY)) == -1) {
    perror("Could not open corners.patdb");
    exit(1);
  }
  if (read(fd, cdb, C_DB_SIZE) == -1) {
    perror("Problem reading corners.patdb");
    exit(1);
  }
  if (close(fd) == -1) {
    perror("Problem closing corners.patdb");
    exit(1);
  }
}

