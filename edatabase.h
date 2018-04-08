#ifndef EDATABASE_H
#define EDATABASE_H

#include "database.h"

#include <stdint.h>

#define NUM_EDGES  12U
#define NUM_EFACES 2U
#define E_DB_SIZE 21288960 

// Retrieve stored path length from first database.
uint8_t E1_path_length(uint8_t *comb, uint8_t *data);

// Retrieve stored path length from second database.
uint8_t E2_path_length(uint8_t *comb, uint8_t *data);

// Get index of stored combination.
unsigned E1_get_index(uint8_t *comb);
unsigned E2_get_index(uint8_t *comb);

void load_edbs(uint8_t *edb1, uint8_t *edb2);

#endif
