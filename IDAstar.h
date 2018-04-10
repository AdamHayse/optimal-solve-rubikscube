#ifndef IDASTAR_H
#define IDASTAR_H

#include <stdint.h>
#include "cdatabase.h"
#include "edatabase.h"

typedef struct node {
  uint8_t corners[8];
  uint8_t edges[12];
  unsigned heurC;
  unsigned heurE1;
  unsigned heurE2;
  uint8_t moves[20];  // Moves performed to reach this node
} NODE;

// Recursive search function
unsigned search(NODE *node, unsigned g, unsigned threshold);

// Get dynamically allocated list of next nodes.
NODE* next_nodes(NODE *node);

// Get the largest admissible heuristic.
unsigned maxheur(NODE *node);

// Get scramble from the user.
void get_scramble(void);

void printmove(uint8_t move);

extern uint8_t cdatabase[C_DB_SIZE];
extern uint8_t e1database[E_DB_SIZE];
extern uint8_t e2database[E_DB_SIZE];

#endif
