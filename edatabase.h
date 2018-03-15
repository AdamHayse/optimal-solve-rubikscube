#define NUM_EDGES  12U
#define NUM_EFACES 2U
#define E_DB_SIZE 21288960

uint8_t E1_path_length(uint8_t *comb, uint8_t *data);
unsigned E1_get_index(uint8_t *comb);
unsigned E1_get_loc(uint8_t *comb, unsigned edge);
uint8_t E2_path_length(uint8_t *comb, uint8_t *data);
unsigned E2_get_index(uint8_t *comb);
unsigned E2_get_loc(uint8_t *comb, unsigned edge);

// Retrieve stored path length from first database.
uint8_t E1_path_length(uint8_t *comb, uint8_t *database) {
  unsigned index = E1_get_index(comb);
  unsigned add = index / 2;
  unsigned pos = index % 2;

  // If index is odd, get right 4 bits.  Else, get left 4 bits.
  return pos ? database[add] & 0x0F : database[add] >> 4;
}

// Retrieve stored path length from second database.
uint8_t E2_path_length(uint8_t *comb, uint8_t *database) {
  unsigned index = E2_get_index(comb);
  unsigned add = index / 2;
  unsigned pos = index % 2;

  // If index is odd, get right 4 bits.  Else, get left 4 bits.
  return pos ? database[add] & 0x0F : database[add] >> 4;
}

// Get index of stored combination.
unsigned E1_get_index(uint8_t *comb) {
  unsigned i, add = 0;

  // Calculate permutation number.
  for (i=0; i<6; i++)
    add += E1_get_loc(comb, i) * (fact(NUM_EDGES-i-1)/fact(6));

  // Scale by NUM_EFACES to the NUM_EDGES-6 power for permutation offset.
  add *= power(NUM_EFACES, NUM_EDGES-6);

  // Calculate which orientation number for orientation offset.
  int j=5;
  for (i=0; i<NUM_EDGES; i++)
    if (comb[i]/2 <  6) {
      add += comb[i] % NUM_EFACES * power(NUM_EFACES, j);
      j--;
    }

  return add;
}

unsigned E2_get_index(uint8_t *comb) {
  unsigned i, add = 0;

  // Calculate permutation number.
  for (i=6; i<NUM_EDGES; i++)
    add += E2_get_loc(comb, i) * (fact(NUM_EDGES-i+5)/fact(6));

  // Scale by NUM_EFACES to the NUM_EDGES-6 power for permutation offset.
  add *= power(NUM_EFACES, NUM_EDGES-6);

  // Calculate which orientation number for orientation offset.
  int j=5;
  for (i=0; i<NUM_EDGES; i++)
    if (comb[i]/2 >=  6) {
      add += comb[i] % NUM_EFACES * power(NUM_EFACES, j);
      j--;
    }

  return add;
}

// Get location of edge among remaining edges.
unsigned E1_get_loc(uint8_t *comb, unsigned edge) {
  unsigned i, loc=0;

  for (i=0; i<NUM_EDGES; i++) {
    // Increment if piece is larger than tested edge.
    if (comb[i]/2 > edge)
      loc++;
    if (comb[i]/2 == edge)
      return loc;
  }
}

unsigned E2_get_loc(uint8_t *comb, unsigned edge) {
  unsigned i, loc=0;
  for (i=6; i<NUM_EDGES+6; i++) {
    // Increment if piece is smaller than tested edge.
    if ((comb[i%NUM_EDGES]/2-6)%12 > (edge+6)%NUM_EDGES)
      loc++;
    if (comb[i%NUM_EDGES]/2 == edge)
      return loc;
  }
}
