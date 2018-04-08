#ifndef IDASTAR_H
#define IDASTAR_H

// Set up the scrambled state node and the solved state node.
void initialize_nodes(void);

typedef struct node {
  uint8_t corners[8];
  uint8_t edges[12];
  unsigned encodeC;
  unsigned encodeE1;
  unsigned encodeE2;
  unsigned heurC;
  unsigned heurE1;
  unsigned heurE2;
} NODE;

// Get the largest admissible heuristic.
unsigned maxheur(NODE *node);

unsigned search(NODE *node, unsigned g, unsigned threshold)

#endif
