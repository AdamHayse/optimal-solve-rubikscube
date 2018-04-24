// A good portion of this program is currently spaghetti, but it works.  Will fix.

// ./IDAstar7 -g (Place to store scrambles) (length of every scramble) (number of scrambles to generate)
// Example call to generate 1000 scrambles of size 13 and put them in a file called 13.txt:
//    ./IDAstar7 -g scrambles/13.txt 13 1000

// ./IDAstar7 (file containing scrambles) (file to write statistic to)
// Example call to test scrambles:
//    ./IDAstar7 scrambles/13.txt results/13_7.txt

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <time.h>

#include "searchmoves.h"
#include "cdatabase.h"
#include "edatabase.h"
#include "IDAstar.h"

uint8_t *cdatabase;
uint8_t *e1database;
uint8_t *e2database;

static int gflag = 0;
static NODE solved;
static NODE scrambled;
static uint64_t explored = 0;
static FILE *fps, *fpr;
static fpos_t pos;
static int num_moves, num_scrambles;
static char scramble[256], tokscramble[256];

// IDA* driver
void IDAstar(char *av[]) {

  // If generate options selected.
  if (strcmp(av[1], "-g") == 0) {
    gflag = 1;
    num_moves = atoi(av[3]);
    num_scrambles = atoi(av[4]);
    srand(time(0));
  }

  // Get memory for the database.
  if (((cdatabase=(uint8_t*)malloc(C_DB_SIZE)) == NULL) ||
      ((e1database=(uint8_t*)malloc(E_DB_SIZE)) == NULL) ||
      ((e2database=(uint8_t*)malloc(E_DB_SIZE)) == NULL)) {
    perror("Not enough memory for database.\n");
    exit(1);
  }

  // Load pattern databases and initialize turns.
  load_cdb(cdatabase);
  load_edbs(e1database, e2database);
  initialize_turns();

  // Load scrambles file and create results file if gflag unset.
  if (!gflag && (((fps=fopen(av[1], "r")) == NULL) || ((fpr=fopen(av[2], "w")) == NULL))) {
    perror("Couldn't open file");
    exit(1);
  }
  // Create file that will contain list of scrambles if gflag is set.
  if (gflag && (fpr=fopen(av[2], "w")) == NULL) {
      perror("Couldn't open file");
      exit(1);
   }

  while (1) {

    // Get solved and scrambled states.
    do_scramble();

    explored = 0;
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
    if (!gflag) {
      printf("Solution: ");
      for (unsigned i=0; i<threshold; i++)
        print_move(solved.moves[i]);
      fprintf(fpr, "\t");
      printf("\n\n");
      fprintf(fpr, "%u\t%lu\n", threshold, explored);
    }
    else {
      // 
      if (threshold == num_moves) {
        num_scrambles--;
        fprintf(fpr, "%s", scramble);
        fprintf(fpr, "\n");
        printf("Good scramble  Remaining: %i\n", num_scrambles);
        // If no scrambles are left, close file and exit program.
        if (!num_scrambles) {
          fclose(fpr);
          exit(0);
        }
      }
      // 
      else {
        printf("Bad scramble  Remaining: %i\n", num_scrambles);
      }
    }
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
  for (unsigned i=0; i<sizeof(nodelist)/sizeof(NODE); i++)
    for (unsigned j=0; j<g; j++)
      nodelist[i].moves[j] = node->moves[j];

  // Assign moves to child nodes.
  unsigned i=0;
  for (unsigned j=0; j<18; j++) {
    // Don't turn the same face twice.
    if (g == 0 || j/3 != node->moves[g-1]/3) {
      (*moves[j])(node, nodelist+i);
      nodelist[i].moves[g] = j;
      i++;
    }
  }

  // Perform search on each child node.
  for (unsigned i=0; i<sizeof(nodelist)/sizeof(NODE); i++) {
    explored++;
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
  if (c >= e1 && c >= e2)
    return c;
  else if (e2 >= c && e2 >= e1)
    return e2;
  else
    return e1;
}

// Scramble the cube.
void do_scramble(void) {

  // Set up solved state node.
  for (int i=0; i<8; i++)
    solved.corners[i] = 3*i;
  for (int i=0; i<12; i++)
    solved.edges[i] = 2*i;
  solved.h = 0;

  // If gflag unset, get scramble algorithm from user.
  if (!gflag && fgets(scramble, 256, fps) == NULL) {
    fclose(fps);
    fclose(fpr);
    exit(0);
  }
  if (!gflag)
    strcpy(tokscramble,scramble);

  // If gflag set, get random scramble.
  if (gflag)
    random_scramble();

  // Scramble the solved cube with scramble algorithm.
  if (gflag)
    do_moves();
  else {
    num_moves = do_moves();
    fprintf(fpr, "%s", scramble);
    printf("Scramble: %s", scramble);
    fseek(fpr, -1, SEEK_CUR);
    fprintf(fpr, "\t%u\t", num_moves);
  }
}

void print_move(uint8_t move) {
  switch(move) {
    case 0:  printf("U "); fprintf(fpr, "U "); break;
    case 1:  printf("U2 "); fprintf(fpr, "U2 "); break;
    case 2:  printf("U' "); fprintf(fpr, "U' "); break;
    case 3:  printf("F "); fprintf(fpr, "F "); break;
    case 4:  printf("F2 "); fprintf(fpr, "F2 "); break;
    case 5:  printf("F' "); fprintf(fpr, "F' "); break;
    case 6:  printf("L "); fprintf(fpr, "L "); break;
    case 7:  printf("L2 "); fprintf(fpr, "L2 "); break;
    case 8:  printf("L' "); fprintf(fpr, "L' "); break;
    case 9:  printf("B "); fprintf(fpr, "B "); break;
    case 10:  printf("B2 "); fprintf(fpr, "B2 "); break;
    case 11:  printf("B' "); fprintf(fpr, "B' "); break;
    case 12:  printf("R "); fprintf(fpr, "R "); break;
    case 13:  printf("R2 "); fprintf(fpr, "R2 "); break;
    case 14:  printf("R' "); fprintf(fpr, "R' "); break;
    case 15:  printf("D "); fprintf(fpr, "D "); break;
    case 16:  printf("D2 "); fprintf(fpr, "D2 "); break;
    case 17:  printf("D' "); fprintf(fpr, "D' "); break;
  }
}

// Perform moves on scramble string.
int do_moves(void) {
  NODE states[32];  // Can enter 32 moves.
  states[0] = solved;
  // Tokenize user input and perform moves.
  char* token = strtok(tokscramble, " \n()[]\t{}");
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
  return i;
}

void random_scramble(void) {
  uint8_t moves[20];
  scramble[0] = '\0';
  moves[0] = rand()%18;
  add_move(moves[0]);
  int i=1;
  while (i<num_moves) {
    if (moves[i-1]/3 != (moves[i]=rand()%18)/3) {
      add_move(moves[i]);
      i++;
    }
  }
  strcpy(tokscramble, scramble);
  printf("%s", scramble);
}

void add_move(uint8_t move) {
  switch(move) {
    case 0:  strcat(scramble, "U "); break;
    case 1:  strcat(scramble, "U2 "); break;
    case 2:  strcat(scramble, "U' "); break;
    case 3:  strcat(scramble, "F "); break;
    case 4:  strcat(scramble, "F2 "); break;
    case 5:  strcat(scramble, "F' "); break;
    case 6:  strcat(scramble, "L "); break;
    case 7:  strcat(scramble, "L2 "); break;
    case 8:  strcat(scramble, "L' "); break;
    case 9:  strcat(scramble, "B "); break;
    case 10:  strcat(scramble, "B2 "); break;
    case 11:  strcat(scramble, "B' "); break;
    case 12:  strcat(scramble, "R "); break;
    case 13:  strcat(scramble, "R2 "); break;
    case 14:  strcat(scramble, "R' "); break;
    case 15:  strcat(scramble, "D "); break;
    case 16:  strcat(scramble, "D2 "); break;
    case 17:  strcat(scramble, "D' "); break;
  }
}
