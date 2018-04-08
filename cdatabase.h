#ifndef CDATABASE
#define CDATABASE

#include "database.h"

#include <stdint.h>

#define NUM_CORNERS  8U
#define NUM_CFACES   3U
#define C_DB_SIZE 44089920

// Retrieve stored path length from database.
uint8_t C_path_length(uint8_t *comb, uint8_t *data);

// Get index of stored combination.
unsigned C_get_index(uint8_t *comb);

#endif
