#define NUM_CORNERS  8U
#define NUM_CFACES   3U
#define C_DB_SIZE 44089920

uint8_t C_path_length(uint8_t *comb, uint8_t *data);
unsigned C_get_index(uint8_t *comb);
unsigned C_lex_pos(uint8_t *comb, unsigned remain);
void get_comb(unsigned index);

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
  for (i=NUM_CORNERS; i>1; i--)
    add += fact(i-1) * C_lex_pos(comb+NUM_CORNERS-i, i-1);

  // Scale by NUM_CFACES to the NUM_CORNERS-1 power for permutation offset.
  add *= power(NUM_CFACES, NUM_CORNERS-1);

  // Calculate which orientation number for orientation offset.
  for (i=0; i<NUM_CORNERS-1; i++)
    add += comb[i] % NUM_CFACES * power(NUM_CFACES, NUM_CORNERS-i-2);
  return add;
}

// Determine lexicographic position among remaining elements.
unsigned C_lex_pos(uint8_t *comb, unsigned remain) {
  unsigned pos = 0, i;
  for (i=1; i<=remain; i++)
    if (comb[0] > comb[i])
      pos++;
  return pos;
}
/*
uint8_t C_node[8];
void C_get_comb(unsigned index) {

  // Find corner orientations.
  unsigned i, orien = index%power(3,7);
  index /= power(3,7);
  for (i=7; i<=0; i--) {
    C_node[i] = orien%3 + index / fact(i);
    orien /= 3;
    index %= fact(i);
  }

} */
