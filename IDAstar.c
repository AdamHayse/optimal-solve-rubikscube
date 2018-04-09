#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#include "searchmoves.h"
#include "cdatabase.h"
#include "edatabase.h"
#include "IDAstar.h"

#define FOUND 50

uint8_t cdatabase[C_DB_SIZE];
uint8_t e1database[E_DB_SIZE];
uint8_t e2database[E_DB_SIZE];

static NODE solved;
static NODE scrambled;

// IDA* driver
int main(void) {

  // Load pattern databases and initialize turns.
  load_cdb(cdatabase);
  load_edbs(e1database, e2database);
  initialize_turns();

  // Set solved and scrambled states.
  initialize_nodes();

  // Get initial estimate to solve.
  unsigned threshold = maxheur(&scrambled);

  while (1) {
    int temp = search(&scrambled, 0, threshold);
    if (temp == FOUND) {
      return FOUND;
      printf("Success\n");
    }
    if (temp == 21) // No solution is greater than 20 moves.
    {
      return 0;
      printf("problem\n");
    }
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

  NODE *nodelist = next_nodes(node);
  for (int i=0; i<15; i++) {
    unsigned temp = search(nodelist+i, g+1, threshold);
    if (temp == FOUND)
      return FOUND;
    if (temp < min)
      min = temp;
  }
  free(nodelist);
  return min;
}

NODE* next_nodes(NODE *node) {
  // Returns a list of all possible next nodes from node.
  NODE *next = (NODE*)malloc(15*sizeof(NODE));
  int i=0;
  unsigned lastmove = node->lastmove;
  for (int j=0; j<18; j++) {
    // Don't turn the same face twice.
    if (j/3 != lastmove/3) {
      (*moves[j])(node, next+i);
      next[i].lastmove = j;
      i++;
    }
  }
  return next;
}

// Set up the scrambled state node and the solved state node.
void initialize_nodes(void) {
  for (int i=0; i<8; i++)
    solved.corners[i] = 3*i;

  for (int i=0; i<12; i++)
    solved.edges[i] = 2*i;

 /* solved.encodeC = 88177653;
  solved.encodeE1 = 0;
  solved.encodeE2 = 42577856; */
  solved.heurC = 0;
  solved.heurE1 = 0;
  solved.heurE2 = 0;

  // Find test scramble later.
  for (int i=0; i<8; i++)
    scrambled.corners[i] = 3*i;

  for (int i=0; i<12; i++)
    scrambled.edges[i] = 2*i;
 /* scrambled.encodeC = 88177653;
  scrambled.encodeE1 = 0;
  scrambled.encodeE2 = 42577856; */
  scrambled.heurC = 0;
  scrambled.heurE1 = 0;
  scrambled.heurE2 = 0;
  scrambled.lastmove = UINT_MAX;
}

// Get the largest admissible heuristic.
unsigned maxheur(NODE *node) {
  if (node->heurC > node->heurE1 && node->heurC > node->heurE2)
    return node->heurC;
  else if (node->heurE1 > node->heurC && node->heurE1 > node->heurE2)
    return node->heurE1;
  else
    return node->heurE2;
}
