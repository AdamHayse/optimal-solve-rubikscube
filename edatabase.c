/*
 * This file contains functions for converting permutations to 
 * indicies and vice versa.  It also contains a function that
 * extracts heuristic values from the edge pattern databases.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "edatabase.h"
#include "mymath.h"

// Retrieve stored path length from first database.
uint8_t E1_path_length(uint8_t *comb, uint8_t *database) {
  uint64_t index = E1_get_index(comb);
  uint64_t add = index / 2;
  unsigned pos = index % 2;

  // If index is odd, get right 4 bits.  Else, get left 4 bits.
  return pos ? database[add] & 0x0F : database[add] >> 4;
}

// Retrieve stored path length from second database.
uint8_t E2_path_length(uint8_t *comb, uint8_t *database) {
  uint64_t index = E2_get_index(comb);
  uint64_t add = index / 2;
  unsigned pos = index % 2;

  // If index is odd, get right 4 bits.  Else, get left 4 bits.
  return pos ? database[add] & 0x0F : database[add] >> 4;
}

// Get index of stored combination.
uint64_t E1_get_index(uint8_t *comb) {
  uint64_t add = 0;

  // Calculate which permutation number.
  for (int i=0; i<TRACKED_EDGES; i++) {
    add += E1_get_loc(comb, i) * (fact[NUM_EDGES-i-1]/fact[NUM_EDGES-TRACKED_EDGES]);
  }

  // Scale for permutation offset.
  add *= two_to_the[TRACKED_EDGES];  // power(NUM_EFACES, TRACKED_EDGES) 

  // Calculate which orientation number for orientation offset.
  for (int i=0; i<TRACKED_EDGES; i++)
    for (int j=0; j<NUM_EDGES; j++)
      if (comb[j]/2 == i) {
        add += comb[j] % NUM_EFACES * two_to_the[i];
        break;
      }

  return add;
}

uint64_t E2_get_index(uint8_t *comb) {
  uint64_t add = 0;

  // Calculate which permutation number.
  for (int i=NUM_EDGES-TRACKED_EDGES; i<12; i++)
    add += E2_get_loc(comb, i) * (fact[NUM_EDGES-i+(NUM_EDGES-TRACKED_EDGES-1)]/fact[NUM_EDGES-TRACKED_EDGES]);

  // Scale for permutation offset.
  add *= two_to_the[TRACKED_EDGES];  // power(NUM_EFACES, TRACKED_EDGES) 

  // Calculate which orientation number for orientation offset.
  for (int i=0; i<TRACKED_EDGES; i++)
    for (int j=0; j<NUM_EDGES; j++)
      if (comb[j]/2 == i+NUM_EDGES-TRACKED_EDGES) {
        add += comb[j] % NUM_EFACES * two_to_the[i];
        break;
      }

  return add;
}

void load_edbs(uint8_t *edb1, uint8_t *edb2) {
  int fd;
  if ((fd = open("pattern_databases/edges1_" TRACKED_NAME ".patdb", O_RDONLY)) == -1) {
    perror("Could not open edges1_" TRACKED_NAME ".patdb");
    exit(1);
  }
  if (read(fd, edb1, E_DB_SIZE) == -1) {
    perror("Problem reading edges1_" TRACKED_NAME ".patdb");
    exit(1);
  }
  if (close(fd) == -1) {
    perror("Problem closing edges1_" TRACKED_NAME ".patdb");
    exit(1);
  }

  if ((fd = open("pattern_databases/edges2_" TRACKED_NAME ".patdb", O_RDONLY)) == -1) {
    perror("Could not open edges2_" TRACKED_NAME ".patdb");
    exit(1);
  }
  if (read(fd, edb2, E_DB_SIZE) == -1) {
    perror("Problem reading edges2_" TRACKED_NAME ".patdb");
    exit(1);
  }
  if (close(fd) == -1) {
    perror("Problem closing edges2_" TRACKED_NAME ".patdb");
    exit(1);
  }
}

 // Get location of edge among remaining edges.
unsigned E1_get_loc(uint8_t *comb, unsigned edge) {
  unsigned loc=0;

  for (int i=0; i<NUM_EDGES; i++) {
    // Increment if piece is larger than tested edge.
    if (comb[i]/NUM_EFACES > edge)
      loc++;
    if (comb[i]/NUM_EFACES == edge)
      return loc;
  }
  printf("There was a problem in E1_get_loc\n");
  exit(0);
}

unsigned E2_get_loc(uint8_t *comb, unsigned edge) {
  unsigned loc=0;

  for (int i=(NUM_EDGES-TRACKED_EDGES); i<NUM_EDGES+(NUM_EDGES-TRACKED_EDGES); i++) {
    // Increment if piece is smaller than tested edge.
    if ((comb[i%NUM_EDGES]/NUM_EFACES-(NUM_EDGES-TRACKED_EDGES))%NUM_EDGES > (edge+TRACKED_EDGES)%NUM_EDGES)
      loc++;
    if (comb[i%NUM_EDGES]/NUM_EFACES == edge)
      return loc;
  }
  printf("There was a problem in E2_get_loc\n");
  exit(0);
}

void E1_decode_index(uint64_t index, uint8_t *comb) {
  uint64_t temp = index/two_to_the[TRACKED_EDGES];
  for (int i=0; i<NUM_EDGES; i++) {
    comb[i] = TRACKED_EDGES*2;
  }
  unsigned long long state = 0xfedcba9876543210ULL;
  for (int i = 0; i < TRACKED_EDGES; i++) {
    int p4 = temp/(fact[11-i]/fact[NUM_EDGES-TRACKED_EDGES]) * 4;
    temp %= (fact[11-i]/fact[NUM_EDGES-TRACKED_EDGES]);
    comb[(state >> p4) & 15] = 2*i + ((index % two_to_the[TRACKED_EDGES] >> i) % 2);
    unsigned long long mask = ((unsigned long long)1 << p4) - 1;
    state = (state & mask) | ((state >> 4) & ~mask);
  }    
}

void E2_decode_index(uint64_t index, uint8_t *comb) {
  uint64_t temp = index/two_to_the[TRACKED_EDGES];
  for (int i=0; i<NUM_EDGES; i++) {
    comb[i] = (NUM_EDGES-TRACKED_EDGES)*2-1;
  }
  unsigned long long state = 0xfedcba9876543210ULL;
  for (int i = NUM_EDGES-TRACKED_EDGES; i < NUM_EDGES; i++) {
    int p4 = ((temp/(fact[NUM_EDGES-i+(NUM_EDGES-TRACKED_EDGES-1)]/fact[NUM_EDGES-TRACKED_EDGES]))+TRACKED_EDGES)%12 * 4 ;
    temp %= (fact[NUM_EDGES-i+(NUM_EDGES-TRACKED_EDGES-1)]/fact[NUM_EDGES-TRACKED_EDGES]);
    comb[(state >> p4) & 15] = 2*i + (index >> (i-(NUM_EDGES-TRACKED_EDGES))) % 2;
    unsigned long long mask = ((unsigned long long)1 << p4) - 1;
    state = (state & mask) | ((state >> 4) & ~mask);
  }
}
