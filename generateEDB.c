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
#include "moves.h"
#include "edatabase.h"

#ifndef HALF
  #error "HALF must be defined as 1 or 2."
#elif HALF == 1 
  #define FILENAME "1"
  #define GET_INDEX(COMB) E1_get_index(COMB)
#elif HALF == 2
  #define FILENAME "2"
  #define GET_INDEX(COMB) E2_get_index(COMB)
#else
  #error "HALF can only be 1 or 2"
#endif

static uint8_t database[E_DB_SIZE];
static uint8_t queue[E_DB_SIZE*2][NUM_EDGES];
static unsigned head;
static unsigned queuesize;
static unsigned depth;

static void breadth_first_search(void);

int main(void) {

  // Set first entry to 0 and all other states to 0xFF.
  database[0] = 0x0F;
  for (int i=1; i<E_DB_SIZE; i++)
    database[i] = 0xFF;

  #if HALF == 2
  database[0] = 0xFF;
  database[21288928] = 0x0F;
  #endif

  // Add first combination to the queue.
  for (uint8_t i=0; i<NUM_EDGES; i++)
    queue[0][i] = NUM_EFACES*i;

  // Add 0xFF to signal increase in depth.
  queue[1][0] = 0xFF;

  // Finalize queue setup.
  queuesize = 2;
  depth = 1;
  head = 0;

  // Put all turn functions in a static array of functions called moves.
  initialize_turns();

  // Show progress tracker.
  update_percent();

  // Continue BFS until only element in queue is 0xFF.
  while (1) {

    // Check to see if there is a change in depth.
    if (queue[head][0] == 0xFF) {
      if (queuesize == 1)
        break;

      // Increment depth.
      depth++;

      // Place another 0xFF at end of queue to signal change in depth.
      queue[(head+queuesize)%(E_DB_SIZE*2)][0] = 0xFF;

      // Move head of queue past the depth change signal.
      head = (head+1)%(E_DB_SIZE*2);
    }
    else
      breadth_first_search();
  }

  // Write database to a file.
  int fd;
  if ((fd=creat("pattern_databases/edges"FILENAME".patdb", 0644)) == -1) {
    perror("\nUnable to create file\n");
    exit(1);
  }
  if (write(fd, database, E_DB_SIZE) == -1) {
    perror("\nThere was a problem writing to the file.\n");
    exit(1);
  }
  if (close(fd) == -1) {
    perror("\nThere was a problem closing the file.\n");
    exit(1);
  }
  printf("\rDatabase generation 100%%\nDone.\n");
}

void breadth_first_search(void) {

  // Add NEW combinations to the end of the queue
  int i;
  unsigned index, add, pos;
  for (i=18; i<35; i++) {

    // Put candidate combination at end of queue.
    (*moves[i])(queue[head], queue[(head+queuesize)%(E_DB_SIZE*2)]);

    // If combination hasn't been seen, keep it in the queue.
    index = GET_INDEX(queue[(head+queuesize)%(E_DB_SIZE*2)]);
    add = index / 2;
    pos = index % 2;
    if ((pos ? database[add] & 0x0F : database[add] >> 4) == 15) {

      // Keep combination in the queue.
      queuesize++;

      // Add depth to database.
      if (pos)
        database[add] = database[add] & depth + 0xF0;
      else
        database[add] = database[add] & (depth << 4) + 0xF;

      // Increase fill amount.
      fill_amount++;
      if ((double)fill_amount / (E_DB_SIZE * 2) > fill_percent + .01)
        update_percent();
    }
  }

  // Manage queue.
  head = (head+1)%(E_DB_SIZE*2);  // Circular array.
  queuesize--;
}
