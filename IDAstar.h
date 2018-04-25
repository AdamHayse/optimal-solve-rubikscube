#ifndef IDASTAR_H
#define IDASTAR_H

#include <stdint.h>
#include "cdatabase.h"
#include "edatabase.h"

#define FOUND 0

typedef struct node {
  uint8_t corners[8];
  uint8_t edges[12];
  unsigned h;
  uint8_t moves[20];  // Moves performed to reach this node
} NODE;

void IDAstar(char *av[]);

// Recursive search function
unsigned search(NODE *node, unsigned g, unsigned threshold);

// Get dynamically allocated list of next nodes.
NODE* next_nodes(NODE *node);

// Get the largest admissible heuristic.
uint8_t maxh(uint8_t c, uint8_t e1, uint8_t e2);

// Get scramble from the user.
void do_scramble(void);

// Print a move.
void print_move(uint8_t move);

void add_move(uint8_t move);

void random_scramble(void);

// Returns the number of moves performed.
int do_moves(void);

void stop(int sig);

extern uint8_t *cdatabase;
extern uint8_t *e1database;
extern uint8_t *e2database;

#endif
