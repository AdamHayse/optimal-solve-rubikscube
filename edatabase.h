#define NUM_EDGES  12U
#define NUM_EFACES 2U
#define E_DB_SIZE 21288960

uint8_t E1_path_length(uint8_t *comb, uint8_t *data);
unsigned E1_get_index(uint8_t *comb);
uint8_t E2_path_length(uint8_t *comb, uint8_t *data);
unsigned E2_get_index(uint8_t *comb);

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

  // Calculate which permutation number.
  unsigned long long state = 0xFEDCBA9876543210;
  for (i=0; i<5; i++) {
    int p4 = comb[i]/2 * 4;
    add = (11-i) * (add + (state >> p4 & 15));
    state -= 0x1111111111111110 << p4;
  }
    add += state >> comb[5]/2 * 4 & 15; 

  // Scale for permutation offset.
  add *= 64;  // power(NUM_EFACES, NUM_EDGES-6) 

  // Calculate which orientation number for orientation offset.
  for (i=0; i<6; i++)
      add += comb[i] % NUM_EFACES * two_to_the[i];

  return add;
}

unsigned E2_get_index(uint8_t *comb) {
  unsigned i, add = 0;

  // Calculate which permutation number.
  unsigned long long state = 0xFEDCBA9876543210;
  for (i=11; i>6; i--) {
    int p4 = comb[i]/2 * 4;
    add = i * (add + (state >> p4 & 15));
    state -= 0x1111111111111110 << p4;
  }
    add += state >> comb[6]/2 * 4 & 15; 

  // Scale for permutation offset.
  add *= 64;  // power(NUM_EFACES, NUM_EDGES-6) 

  // Calculate which orientation number for orientation offset.
  for (i=0; i<6; i++)
      add += comb[i] % NUM_EFACES * two_to_the[i];

  return add;
}
