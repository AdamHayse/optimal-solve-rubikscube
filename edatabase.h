#ifndef EDATABASE_H
#define EDATABASE_H

#include "database.h"

#include <stdint.h>

#define NUM_EDGES  12
#define NUM_EFACES 2U

#ifndef HALF
  #define HALF 1
#endif
#if HALF == 1
  #define FILENAME "1"
  #define GET_INDEX(COMB) E1_get_index(COMB)
  #define FIND_COMB(INDEX, COMB) E1_decode_index(INDEX, COMB)
  #define OP >
  #ifndef TRACKED_EDGES
    #define TRACKED_EDGES 6
  #endif
  #if TRACKED_EDGES == 6
    #define TRACKED_NAME "6"
    #define BOUND 11
    #define E_DB_SIZE 21288960UL     // 12!/6! x 2^6 / 2
  #elif TRACKED_EDGES == 7
    #define TRACKED_NAME "7"
    #define BOUND 13
    #define E_DB_SIZE 255467520UL    // 12!/5! x 2^7 / 2
  #elif TRACKED_EDGES == 8
    #define TRACKED_NAME "8"
    #define BOUND 15
    #define E_DB_SIZE 2554675200ULL   // 12!/4! x 2^8 / 2
  #else
    #error "TRACKED_EDGES must be 6, 7, or 8"
  #endif
#elif HALF == 2
  #define FILENAME "2"
  #define GET_INDEX(COMB) E2_get_index(COMB)
  #define FIND_COMB(INDEX, COMB) E2_decode_index(INDEX, COMB)
  #define OP <
  #ifndef TRACKED_EDGES
    #define TRACKED_EDGES 6
  #endif
  #if TRACKED_EDGES == 6
    #define TRACKED_NAME "6"
    #define BOUND 12
    #define E_DB_SIZE 21288960UL     // 12!/6! x 2^6 / 2
  #elif TRACKED_EDGES == 7
    #define TRACKED_NAME "7"
    #define BOUND 10
    #define E_DB_SIZE 255467520UL    // 12!/5! x 2^7 / 2
  #elif TRACKED_EDGES == 8
    #define TRACKED_NAME "8"
    #define BOUND 8
    #define E_DB_SIZE 2554675200ULL   // 12!/4! x 2^8 / 2
  #else
    #error "TRACKED_EDGES must be 6, 7, or 8"
  #endif
#else
  #error "HALF can only be 1 or 2"
#endif


// Retrieve stored path length from first database.
uint8_t E1_path_length(uint8_t *comb, uint8_t *data);

// Retrieve stored path length from second database.
uint8_t E2_path_length(uint8_t *comb, uint8_t *data);

// Get index of stored combination.
uint64_t E1_get_index(uint8_t *comb);
uint64_t E2_get_index(uint8_t *comb);

// Get location of edge among remaining edges.
unsigned E1_get_loc(uint8_t *comb, unsigned edge);
unsigned E2_get_loc(uint8_t *comb, unsigned edge);

// Transform an index of the database to a combination.
void E1_decode_index(uint64_t index, uint8_t *comb);
void E2_decode_index(uint64_t index, uint8_t *comb);

// Load edge databases into arrays of size E_DB_SIZE pointed to by edb1 and edb2.
void load_edbs(uint8_t *edb1, uint8_t *edb2);

#endif
