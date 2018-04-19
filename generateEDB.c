/*
 *  This program generates a database that stores all
 *  combinations of the edge pieces of a Rubik's cube.
 *
 *  The minimum number of moves never exceeds 11, 
 *  so only 4 bits is needed to store this value.
 *  I store two values per byte to save memory.
 *
 *  Cubie 1    YO  0   OY  1
 *  Cubie 2    YG  2   GY  3
 *  Cubie 3    YR  4   RY  5
 *  Cubie 4    YB  6   BY  7
 *  Cubie 5    OG  8   GO  9
 *  Cubie 6    GR 10   RG 11
 *  Cubie 7    RB 12   BR 13
 *  Cubie 8    BO 14   OB 15
 *  Cubie 9    WO 16   OW 17
 *  Cubie 10   WG 18   GW 19
 *  Cubie 11   WR 20   RW 21
 *  Cubie 12   WB 22   BW 23
 *  
 *  Yellow face is Up, Orange face is Front.
 *  Solved edges position = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22}
 *        ___________
 *       /|    2    /|
 *    1 / |      3 / |
 *     /__|_______/  |
 *    | 5 |  0   |   | 6
 *    |   |      |   |
 *  4 |   |______|_7_|
 *    |  /    10 |  /
 *    | / 9      | / 11
 *    |/_________|/
 *         8
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
#include "edatabase.h"

static uint8_t *database;
static uint8_t comb[NUM_EDGES];
static uint8_t temp[NUM_EDGES];
static unsigned depth;
static uint64_t hvalues[20];

static void breadth_first_search(void);
static void write_DB(void);

int main(void) {

  // Get memory for the database.
  if ((database=(uint8_t*)malloc(E_DB_SIZE)) == NULL) {
    perror("Not enough memory for database.\n");
    exit(1);
  }

  // Set first entry to 0 and all other states to 0xFF.
  database[0] = 0x0F;
  for (uint64_t i=1; i<E_DB_SIZE; i++)
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
    for (uint64_t i=0; i<E_DB_SIZE; i++) {

      if (database[i]>>4 == depth) {
        FIND_COMB(i*2, comb);
        breadth_first_search();
        hvalues[depth]++;
        done = 0;
      }
      if ((database[i]&0x0F) == depth) {
        FIND_COMB(i*2+1, comb);
        breadth_first_search();
        hvalues[depth]++;
        done = 0;
      }
    }
    depth++;
  }

  // Write database to a file.
  write_DB();

  printf("\rDatabase generation 100%%\nDone.\n");

  // Print table of heuristic values.
  for (unsigned i=0; i<depth-1; i++)
    printf("%2u move to solve:  %lu\n", i, hvalues[i]);
}

void breadth_first_search(void) {

  // Add NEW combinations to the end of the queue
  uint64_t index, add, pos;
  for (int i=0; i<18; i++) {

    // If turn affects edges cubes that we care about.
    if ((*movesE[i])(comb, temp)) {

      // If new combination hasn't been seen, add value of depth+1 to database.
      index = GET_INDEX(temp);
      add = index / 2;
      pos = index % 2;  // 0 = left 4 bits  1 = right 4 bits
      if ((pos ? database[add] & 0x0F : database[add] >> 4) == 15) {

        // Add depth+1 to database.
        if (pos)
          database[add] = database[add] & ((depth+1) | 0xF0);
        else
          database[add] = database[add] & (((depth+1) << 4) | 0x0F);

        // Increase fill amount.
        fill_amount++;
        if ((double)fill_amount / (E_DB_SIZE * 2) >= fill_percent + .01)
          update_percent();
      }
    }
  }
}

void write_DB(void) {

  // Write database to a file.
  int fd;
  if ((fd=creat("pattern_databases/edges"FILENAME"_"TRACKED_NAME".patdb", 0644)) == -1) {
    perror("\nUnable to create file\n");
    exit(1);
  }

  int i=0;
  int64_t amount = 0, remain = E_DB_SIZE;
  while ((amount=write(fd, database + E_DB_SIZE - remain, (remain>SSIZE_MAX) ? SSIZE_MAX : remain)) != remain) {
    if (amount == -1) {
      perror("Problem writing to file.\n");
      exit(1);
    }
    remain -= amount;
    i++;
  }

  if (close(fd) == -1) {
    perror("\nThere was a problem closing the file.\n");
    exit(1);
  }
}
