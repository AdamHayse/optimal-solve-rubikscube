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
#include <fcntl.h>
#include <unistd.h>
#include "moves.h"
#include "cdatabase.h"

static uint8_t database[C_DB_SIZE];
static uint8_t queue[C_DB_SIZE*2][NUM_CORNERS];
static unsigned head;
static unsigned queuesize;
static unsigned depth;

void breadth_first_search(void);

int main() {

  // Set first entry to 0 and all other states to 0xFF.
  database[0] = 0x0F;
  int i;
  for (i=1; i<C_DB_SIZE; i++)
    database[i] = 0xFF;

  // Add first combination to the queue.
  for (i=0; i<NUM_CORNERS; i++)
    queue[0][i] = NUM_CFACES*i;

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
      queue[(head+queuesize)%(C_DB_SIZE*2)][0] = 0xFF;

      // Move head of queue past the depth change signal.
      head = (head+1)%(C_DB_SIZE*2);
    }
    else
      breadth_first_search();
  }

  // Write database to a file.
  int fd = creat("pattern_databases/corners.patdb", 0644);
  write(fd, database, C_DB_SIZE);
  close(fd);
  printf("\rDatabase generation 100%%\nDone.\n");

}

void breadth_first_search() {

  // Add NEW combinations to the end of the queue
  int i;
  unsigned index, add, pos;
  for (i=0; i<18; i++) {

    // Put candidate combination at end of queue.
    (*moves[i])(queue[head], queue[(head+queuesize)%(C_DB_SIZE*2)]);

    // If combination hasn't been seen, keep it in the queue.
    index = C_get_index(queue[(head+queuesize)%(C_DB_SIZE*2)]);
    add = index / 2;
    pos = index % 2;
    if ((pos ? database[add] & 0x0F : database[add] >> 4) == 15) {

      // Keep combination in the queue.
      queuesize++;

      // Add depth to database.
      if (pos)
        database[add] = database[add] & (depth | 0xF0);
      else
        database[add] = database[add] & ((depth << 4) | 0xF);

      // Increase fill amount.
      fill_amount++;
      if ((double)fill_amount / (C_DB_SIZE * 2) > fill_percent + .01)
        update_percent();
    }
  }

  // Manage queue.
  head = (head+1)%(C_DB_SIZE*2);  // Circular array.
  queuesize--;
}
