#ifndef CDATABASE_H
#define CDATABASE_H

#include "database.h"

#include <stdint.h>

#define NUM_CORNERS  8
#define NUM_CFACES   3
#define C_DB_SIZE 44089920

// Retrieve stored path length from database.
uint8_t C_path_length(uint8_t *comb, uint8_t *data);

// Get index of stored combination.
unsigned C_get_index(uint8_t *comb);

// Transform an index of the database to a combination.
void C_decode_index(unsigned index, uint8_t *comb);

// Load corners database into array of size C_DB_SIZE pointed to by cdb.
void load_cdb(uint8_t *cdb);

#endif
