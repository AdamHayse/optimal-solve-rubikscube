/*
 *  This program generates a database that stores all
 *  combinations of the corner pieces of a Rubik's cube.
 *
 *  The minimum number of moves never exceeds 11, 
 *  so only 4 bits is needed to store this value.
 *  I store two values per byte to save memory.
 *
 *  Cubie 1    YOG  0   GYO  1   OGY  2
 *  Cubie 2    YGR  3   RYG  4   GRY  5
 *  Cubie 3    YRB  6   BYR  7   RBY  8
 *  Cubie 4    YBO  9   OYB 10   BOY 11
 *  Cubie 5    WGO 12   OWG 13   GOW 14
 *  Cubie 6    WRG 15   GWR 16   RGW 17
 *  Cubie 7    WBR 18   RWB 19   BRW 20
 *  Cubie 8    WOB 21   BWO 22   OBW 23
 *  
 *  Yellow face is Up, Orange face is Front.
 *  Solved corners position = {0, 3, 6, 9, 12, 15, 18, 21}
 *      1 ___________ 2
 *       /|         /|
 *      / |        / |
 *   0 /__|_______/3 |
 *    |   |      |   |
 *    |   |      |   |
 *    | 5 |______|___| 6
 *    |  /       |  /
 *    | /        | /
 *  4 |/_________|/ 7
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include "moves.h"
#include "cdatabase.h"

static uint8_t database[C_DB_SIZE];
static uint8_t comb[NUM_CORNERS];
static uint8_t temp[NUM_CORNERS];
static unsigned depth;
static unsigned hvalues[20];

static void breadth_first_search(void);

int main(void) {

  // Set first entry to 0 and all other states to 0xFF.
  database[0] = 0x0F;
  for (uint64_t i=1; i<C_DB_SIZE; i++)
    database[i] = 0xFF;

  // Put all turn functions in a static array of functions called moves.
  initialize_turns();

  // Show progress tracker.
  update_percent();

  // Do BFS by expanding only nodes of a given depth on each pass until database is full.
  depth = 0;
  int done=0;
  while (!done) {
    done = 1;
    for (unsigned i=0; i<C_DB_SIZE; i++) {

      if (database[i]>>4 == depth) {
        C_decode_index(i*2, comb);
        breadth_first_search();
        hvalues[depth]++;
        done = 0;
      }
      if ((database[i]&0x0F) == depth) {
        C_decode_index(i*2+1, comb);
        breadth_first_search();
        hvalues[depth]++;
        done = 0;
      }
    }
    depth++;
  }

  // Write database to a file.
  int fd;
  if ((fd=creat("pattern_databases/corners.patdb", 0644)) == -1) {
    perror("\nUnable to create file\n");
    exit(1);
  }
  if (write(fd, database, C_DB_SIZE) == -1) {
    perror("\nThere was a problem writing to the file.\n");
    exit(1);
  }
  if (close(fd) == -1) {
    perror("\nThere was a problem closing the file.\n");
    exit(1);
  }
  printf("\rDatabase generation 100%%\nDone.\n");

  // Print table of heuristic values.
  for (unsigned i=0; i<depth-1; i++)
    printf("%2u move to solve:  %u\n", i, hvalues[i]);
}

void breadth_first_search(void) {

  // Add NEW combinations to the end of the queue
  unsigned index, add, pos;
  for (int i=0; i<18; i++) {

    // Perform turn.
    (*movesC[i])(comb, temp);

    // If new combination hasn't been seen, add value of depth+1 to database.
    index = C_get_index(temp);
    if (index/2 > C_DB_SIZE)
      exit(0);
    add = index / 2;
    pos = index % 2;  // 0 = left 4 bits  1 = right 4 bits
    if ((pos ? database[add] & 0x0F : database[add] >> 4) == 15) {

   // printf("%u %u %u\n", i, depth+1, index);

      // Add depth+1 to database.
      if (pos)
        database[add] = database[add] & ((depth+1) | 0xF0);
      else
        database[add] = database[add] & (((depth+1) << 4) | 0x0F);

      // Increase fill amount.
      fill_amount++;
      if ((double)fill_amount / (C_DB_SIZE * 2) > fill_percent + .01)
        update_percent();
    }
  }
}
