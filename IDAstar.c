#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#include "moves.h"
#include "cdatabase.h"
#include "edatabase.h"
#include "IDAstar.h"

static uint8_t cdatabase[C_DB_SIZE];
static uint8_t e1database[E_DB_SIZE];
static uint8_t e2database[E_DB_SIZE];

static NODE solved;
static NODE scrambled;

// IDA* driver
int main(void) {

  // Load pattern databases.
  load_cdb(cdatabase);
  load_edbs(e1database, e2database);

  // Set solved and scrambled states
  initialize_nodes();

  // Get initial estimate to solve.
  unsigned threshold = maxheur(&scrambled);

  while (1) {
    int temp = search(&scrambled, 0, threshold);
    if (temp == FOUND)
      return FOUND;
    if (temp == 21) // No solution is greater than 20 moves.
      return;
    threshold = temp;
  }
}

// Recursive search function
unsigned search(NODE *node, unsigned g, unsigned threshold) {
  unsigned f = g + maxheur(node);
  if (f > threshold)
    return f;
  if (node->heurC == 0 && node->heurE1 == 0 && node->heurE2 == 0)
    return FOUND;
  unsigned min = UINT_MAX;
}

// Set up the scrambled state node and the solved state node.
void initialize_nodes(void) {
  solved.corners = {0, 3, 6, 9, 12, 15, 18, 21};
  solved.edges = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22};
  solved.encodeC = 88177653;
  solved.encodeE1 = 0;
  solved.encodeE2 = 42577856;
  solved.heurC = 0;
  solved.heurE1 = 0;
  solved.heurE2 = 0;

  // Find test scramble later.
  scrambled.corners = {0, 3, 6, 9, 12, 15, 18, 21};
  scrambled.edges = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22};
  scrambled.encodeC = 88177653;
  scrambled.encodeE1 = 0;
  scrambled.encodeE2 = 42577856;
  scrambled.heurC = 0;
  scrambled.heurE1 = 0;
  scrambled.heurE2 = 0;
}

// Get the largest admissible heuristic.
unsigned maxheur(NODE *node) {
  if (node->heurC > node->heurE1 && node->heurC > node->heurE2)
    return node->heurC;
  else if (node->heurE1 > node->heurc && node->heurE1 > node->heurE2)
    return node->heurE1;
  else
    return node->heurE2;
}
