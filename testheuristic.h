#ifndef TESTHEURISTIC_H
#define TESTHEURISTIC_H

#include <stdint.h>

// Creates an ASCII representation of the cube in the CLI.
void display_cube(uint8_t *corners, uint8_t *edges);

/* Checks to see if a given combination of the cube is
   a member of the subgraph that contains the solution state. */
unsigned valid_comb(uint8_t *corners, uint8_t *edges);

#endif
