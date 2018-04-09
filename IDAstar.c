#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

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

  // Get solved and scrambled states.
  get_scramble();

  // Get initial estimate to solve.
  unsigned threshold = maxheur(&scrambled);

  while (1) {
    int temp = search(&scrambled, 0, threshold);

    if (temp == FOUND) {
      printf("Success %u\n", threshold);
      return FOUND;
    }
    if (temp == 21) // No solution is greater than 20 moves.
    {
      printf("problem\n");
      break;
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

// Get dynamically allocated list of next nodes.
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

// Get the largest admissible heuristic.
unsigned maxheur(NODE *node) {
  if (node->heurC > node->heurE1 && node->heurC > node->heurE2)
    return node->heurC;
  else if (node->heurE1 > node->heurC && node->heurE1 > node->heurE2)
    return node->heurE1;
  else
    return node->heurE2;
}

// Get scramble from the user.
void get_scramble(void) {
  // Set up solved state
  for (int i=0; i<8; i++)
    solved.corners[i] = 3*i;
  for (int i=0; i<12; i++)
    solved.edges[i] = 2*i;
  solved.heurC = 0;
  solved.heurE1 = 0;
  solved.heurE2 = 0;

  // Get scramble algorithm from user.
  char scramble[256];
  NODE states[32];
  states[0] = solved;
  fgets(scramble, 256, stdin);

  // Tokenize user input and perform moves.
  char* token = strtok(scramble, " \n()[]\t{}");
  int i=0;
  while (token) {
    if (strcmp(token, "U") == 0)
      turn_U(&states[i], &states[i+1]);
    else if (strcmp(token, "U2") == 0)
      turn_U2(&states[i], &states[i+1]);
    else if (strcmp(token, "U'") == 0)
      turn_Uprime(&states[i], &states[i+1]);
    else if (strcmp(token, "F") == 0)
      turn_F(&states[i], &states[i+1]);
    else if (strcmp(token, "F2") == 0)
      turn_F2(&states[i], &states[i+1]);
    else if (strcmp(token, "F'") == 0)
      turn_Fprime(&states[i], &states[i+1]);
    else if (strcmp(token, "L") == 0)
      turn_L(&states[i], &states[i+1]);
    else if (strcmp(token, "L2") == 0)
      turn_L2(&states[i], &states[i+1]);
    else if (strcmp(token, "L'") == 0)
      turn_Lprime(&states[i], &states[i+1]);
    else if (strcmp(token, "B") == 0)
      turn_B(&states[i], &states[i+1]);
    else if (strcmp(token, "B2") == 0)
      turn_B2(&states[i], &states[i+1]);
    else if (strcmp(token, "B'") == 0)
      turn_Bprime(&states[i], &states[i+1]);
    else if (strcmp(token, "R") == 0)
      turn_R(&states[i], &states[i+1]);
    else if (strcmp(token, "R2") == 0)
      turn_R2(&states[i], &states[i+1]);
    else if (strcmp(token, "R'") == 0)
      turn_Rprime(&states[i], &states[i+1]);
    else if (strcmp(token, "D") == 0)
      turn_D(&states[i], &states[i+1]);
    else if (strcmp(token, "D2") == 0)
      turn_D2(&states[i], &states[i+1]);
    else if (strcmp(token, "D'") == 0)
      turn_Dprime(&states[i], &states[i+1]);
    else {
      printf("Invalid scramble");
      exit(0);
    }
    token = strtok(NULL, " \n()[]\t{}");
    i++;
  }
  scrambled = states[i];
}
