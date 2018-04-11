#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

#include "searchmoves.h"
#include "cdatabase.h"
#include "edatabase.h"
#include "IDAstar.h"

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


  while (1) {
    // Get solved and scrambled states.
    get_scramble();
printf("%u\n", E2_path_length(scrambled.edges, e2database));
    // Get initial estimate to solve.
    unsigned threshold = scrambled.h;
    int length;
    // Search for a solution.
    while (1) {
      length = search(&scrambled, 0, threshold);

      if (length == 21) // No solution is greater than 20 moves.
      {
        printf("There was a problem.\n");
        exit(0);
      }
      if (length == FOUND)
        break;
      threshold = length;
    }

    // Print solution.
    for (int i=0; i<threshold; i++)
      printmove(solved.moves[i]);

    putchar('\n');
  }
}

// Recursive search function
unsigned search(NODE *node, unsigned g, unsigned threshold) {
  unsigned f = g + node->h;

  // Depth limit imposed by the heuristic and current depth.
  if (f > threshold)
    return f;

  // Only node where h equals 0 is the solved state.
  if (node->h == 0)
    return FOUND;

  unsigned min = UINT_MAX;

  // Assign all previous moves up to this point to new child nodes.
  NODE nodelist[g ? 15 : 18];
  int i, j;
  for (i=0; i<sizeof(nodelist)/sizeof(NODE); i++)
    for (j=0; j<g; j++)
      nodelist[i].moves[j] = node->moves[j];

  // Assign moves to child nodes.
  i=0;
  for (j=0; j<18; j++) {
    // Don't turn the same face twice.
    if (g == 0 || j/3 != node->moves[g-1]/3) {
      (*moves[j])(node, nodelist+i);
      nodelist[i].moves[g] = j;
      i++;
    }
  }

  // Perform search on each child node.
  for (i=0; i<sizeof(nodelist)/sizeof(NODE); i++) {
    printf("Turning ");
    printmove(nodelist[i].moves[g]);
    printf("\n");

    unsigned length = search(nodelist+i, g+1, threshold);
    if (length == FOUND) {
        solved.moves[g] = nodelist[i].moves[g];  // Populate static solved node with the moves.
        return FOUND;
    }
    if (length < min)
      min = length;
  }
  return min;
}

// Get the largest admissible heuristic.
uint8_t maxh(uint8_t c, uint8_t e1, uint8_t e2) {
  if (c > e1 && c > e2)
    return c;
  if (e1 > c && e1 > e2)
    return e1;
  else
    return e2;
}

// Get scramble from the user.
void get_scramble(void) {

  // Set up solved state node.
  for (int i=0; i<8; i++)
    solved.corners[i] = 3*i;
  for (int i=0; i<12; i++)
    solved.edges[i] = 2*i;
  solved.h = 0;

  // Get scramble algorithm from user.
  char scramble[256];
  NODE states[32];  // Can enter 32 moves.
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

void printmove(uint8_t move) {
  switch(move) {
    case 0:  printf("U "); break;
    case 1:  printf("U2 "); break;
    case 2:  printf("U' "); break;
    case 3:  printf("F "); break;
    case 4:  printf("F2 "); break;
    case 5:  printf("F' "); break;
    case 6:  printf("L "); break;
    case 7:  printf("L2 "); break;
    case 8:  printf("L' "); break;
    case 9:  printf("B "); break;
    case 10:  printf("B2 "); break;
    case 11:  printf("B' "); break;
    case 12:  printf("R "); break;
    case 13:  printf("R2 "); break;
    case 14:  printf("R' "); break;
    case 15:  printf("D "); break;
    case 16:  printf("D2 "); break;
    case 17:  printf("D' "); break;
  }
}
