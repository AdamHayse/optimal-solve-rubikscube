#ifndef IDASTAR_H
#define IDASTAR_H

#include <stdint.h>
#include "cdatabase.h"
#include "edatabase.h"

typedef struct node {
  uint8_t corners[8];
  uint8_t edges[12];
/*  unsigned encodeC;
  unsigned encodeE1;
  unsigned encodeE2; */
  unsigned heurC;
  unsigned heurE1;
  unsigned heurE2;
  unsigned lastmove;  // 0 to 17
} NODE;

// Recursive search function
unsigned search(NODE *node, unsigned g, unsigned threshold);

NODE* next_nodes(NODE *node);

// Set up the scrambled state node and the solved state node.
void initialize_nodes(void);

// Get the largest admissible heuristic.
unsigned maxheur(NODE *node);

extern uint8_t cdatabase[C_DB_SIZE];
extern uint8_t e1database[E_DB_SIZE];
extern uint8_t e2database[E_DB_SIZE];

#endif
