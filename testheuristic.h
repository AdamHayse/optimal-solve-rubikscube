#ifndef TESTHEURISTIC_H
#define TESTHEURISTIC_H

#include <stdint.h>

// Driver function for individual scramble tests.
void test_heuristic(void);

// Creates an ASCII representation of the cube in the CLI.
void display_cube(uint8_t *corners, uint8_t *edges);

/* Checks to see if a given combination of the cube is
   a member of the subgraph that contains the solution state. */
unsigned valid_comb(uint8_t *corners, uint8_t *edges);

// Display the array representation of a scramble.
void display_scramble(uint8_t *corners, uint8_t *edges);

// Return 0 if bijective, difference otherwise.
int64_t E1_bijective(uint8_t *edges);
int64_t E2_bijective(uint8_t *edges);

#endif
