#include "cdatabase.h"
#include "edatabase.h"

static unsigned fill_amount = 0;
static double fill_percent = 0.0;

void update_percent(void);
void display_percent(void);
unsigned valid_comb(uint8_t *corners, uint8_t *edges);

void update_percent() {
  fill_percent += 0.01;
  printf("\rDatabase generation %-.0lf%%", fill_percent*100);
  fflush(stdout);
}

void display_percent() {
  printf("\rDatabase generation %-.0lf%%", fill_percent*100);
  fflush(stdout);
}

// Returns 1 if solvable, 0 if unsolvable.
unsigned valid_comb(uint8_t *corners, uint8_t *edges) {

  // Test 1: Check corner orientation.
  int8_t i, test1=0;
  for (i=0; i<NUM_CORNERS; i++)
    test1 += corners[i];
  if (test1 % 3)
    return 0;

  // Test 2: Check edge orientation.
  int test2=0;
  for (i=0; i<NUM_EDGES; i++)
    test2 += edges[i];
  if (test2 % 2)
    return 0;


  // Test 3: Check edge and corner permutation.
  int even_corners=0, even_edges=0, leftmost=0, pos=0, count=0;
  int16_t vis_edges = 0xF000;
  int8_t vis_corners = 0x00;

  // Count number of even corner cycles.
  while (vis_corners != -1) {

    // If unvisited, Set corner at pos as visited and get new pos.  Increment count.
    if (!(vis_corners & 1 << 7 - pos)) {
      vis_corners = vis_corners | 1 << 7 - pos;
      pos = corners[pos]/3;
      count++;
    }
    // If pos was visited, end of cycle.  see if count if even.  increment if it is. set count to 0 again.
    else {
      if (count%2 == 0)
        even_corners++;
      count = 0;
      // Increment leftmost until there is a pos that is unvisited.  Set new pos.
      for (i=vis_corners<<leftmost; i < 0; leftmost++)
        i = i << 1;
      pos = leftmost;
    }
  }
  // If the loop exited and count is positive and even.
  if (count>0 && count%2==0)
    even_corners++;

  // Reset values.
  count = leftmost = pos = 0;
  int16_t j;
  
  // Count number of even edge cycles.
  while (vis_edges != -1) {

    // If unvisited, Set edge at pos as visited and get new pos.  Increment count.
    if (!(vis_edges & 1 << 11 - pos)) {
      vis_edges = vis_edges | 1 << 11 - pos;
      pos = edges[pos]/2;
      count++;
    }
    // If pos was visited, end of cycle.  see if count if even.  increment if it is. set count to 0 again.
    else {
      if (count%2 == 0)
        even_edges++;
      count = 0;

      // Increment leftmost until there is a pos that is unvisited.  Set new pos.
      for (j=vis_edges<<4+leftmost; j < 0; leftmost++)
        j = j << 1;
      pos = leftmost;
    }
  }
  // If the loop exited and count is positive and even.
  if (count>0 && count%2==0)
    even_edges++;

  // Not solvable if number of even cycles is not equal.
  if (even_edges%2 != even_corners%2)
    return 0;
    
  // Passed all 3 tests.  Solvable.
  return 1;
}
