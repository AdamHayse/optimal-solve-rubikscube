/*
 *  Copy and paste or type a scramble algorithm to
 *  see how many moves are required to solve the corners,
 *  edges 1-6, and edges 7-12.
 *
 *  Example: (R U R' U') (R' F R2 U') R' U' (R U R' F')
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "searchmoves.h"
#include "mymath.h"
#include "cdatabase.h"
#include "edatabase.h"
#include "IDAstar.h"
#include "testheuristic.h"

uint8_t *cdatabase;
uint8_t *e1database;
uint8_t *e2database;
static NODE solved;
static NODE scrambled;

void test_heuristic(void) {

  cdatabase = (uint8_t*)malloc(C_DB_SIZE);
  e1database = (uint8_t*)malloc(E_DB_SIZE);
  e2database = (uint8_t*)malloc(E_DB_SIZE);

  // Load databases.
  load_cdb(cdatabase);
  load_edbs(e1database, e2database);

  // Set up solved state node.
  for (int i=0; i<8; i++)
    solved.corners[i] = 3*i;
  for (int i=0; i<12; i++)
    solved.edges[i] = 2*i;

  // Get scramble algorithm and execute it on solved combination.
  char scramble[256];
  NODE states[64];  // Can enter 64 moves.
  states[0] = solved;
  while (1) {

    // Get scramble algorithm from user.
    if (fgets(scramble, 256, stdin) == NULL)
      exit(0);

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

    // Show graphical representation of the scramble.
    display_cube(scrambled.corners, scrambled.edges);

    // Verify that the scramble results in a valid cube state.
    if (valid_comb(scrambled.corners, scrambled.edges))
      printf("Valid cube state.\n");
    else {
      printf("***Invalid cube state.***\n");

    }

    // Show array representation of the scramble.
    display_scramble(scrambled.corners, scrambled.edges);

    // Check that bijectivity of edge encodes and decodes is preserved.
    int64_t difference;
    if ((difference=E1_bijective(scrambled.edges)) == 0)
      printf("E1 Encode/decode function is bijective for scramble.\n");
    else {
      printf("***E1 NOT BIJECTIVE***\n  difference = %ld\n", difference);
      // Get decode.
      int64_t index = E1_get_index(scrambled.edges);
      uint8_t temp[NUM_EDGES];
      E1_decode_index(index, temp);
      // Print decode.
      for (unsigned i=0; i<NUM_EDGES; i++)
        printf("%2u, ", temp[i]);
      putchar('\n');
    }
    if ((difference=E2_bijective(scrambled.edges)) == 0)
      printf("E2 Encode/decode function is bijective for scramble.\n");
    else {
      printf("***E2 NOT BIJECTIVE***\n  difference = %ld\n", difference);
      // Get decode.
      int64_t index = E2_get_index(scrambled.edges);
      uint8_t temp[NUM_EDGES];
      E2_decode_index(index, temp);
      // Print decode.
      for (unsigned i=0; i<NUM_EDGES; i++)
        printf("%2u, ", temp[i]);
      putchar('\n');
    }
    if ((difference=C_bijective(scrambled.corners)) == 0)
      printf("C Encode/decode function is bijective for scramble.\n");
    else {
      printf("***C NOT BIJECTIVE***\n  difference = %ld\n", difference);
      // Get decode.
      int64_t index = C_get_index(scrambled.corners);
      uint8_t temp[NUM_CORNERS];
      C_decode_index(index, temp);
      // Print decode.
      for (unsigned i=0; i<NUM_CORNERS; i++)
        printf("%2u, ", temp[i]);
      putchar('\n');
    }
  }
}

// Creates an ASCII representation of the cube in the CLI.
void display_cube(uint8_t *corners, uint8_t *edges) {

  // Set up cubies.
  char c[8][3][4] = { { "YOG", "GYO", "OGY" },
                      { "YGR", "RYG", "GRY" },
                      { "YRB", "BYR", "RBY" },
                      { "YBO", "OYB", "BOY" },
                      { "WGO", "OWG", "GOW" },
                      { "WRG", "GWR", "RGW" },
                      { "WBR", "RWB", "BRW" },
                      { "WOB", "BWO", "OBW" }
  };
  char e[12][2][3] = { { "YO", "OY" },
                       { "YG", "GY" },
                       { "YR", "RY" },
                       { "YB", "BY" },
                       { "OG", "GO" },
                       { "GR", "RG" },
                       { "RB", "BR" },
                       { "BO", "OB" },
                       { "WO", "OW" },
                       { "WG", "GW" },
                       { "WR", "RW" },
                       { "WB", "BW" }
  };

  // Assign faces.
  char face[48];
  int i, j;
  for (i=0; i<8; i++)
    for (j=0; j<3; j++) 
      face[3*i+j] = c[corners[i]/3][corners[i]%3][j];
  for (i=0; i<12; i++)
    for (j=0; j<2; j++) 
      face[24+2*i+j] = e[edges[i]/2][edges[i]%2][j];

  // Print cube.
  printf("\n               -----------\n");
  printf("              | %c | %c | %c |\n",face[3],face[28],face[6]);
  printf("               -----------\n");
  printf("              | %c | Y | %c |\n",face[26],face[30]);
  printf("               -----------\n");
  printf("              | %c | %c | %c |\n",face[0],face[24],face[9]);
  printf("  -----------  ===========  -----------  -----------\n");
  printf(" | %c | %c | %c || %c | %c | %c || %c | %c | %c || %c | %c | %c |\n",face[4],face[27],
  face[2],face[1],face[25],face[11],face[10],face[31],face[8],face[7],face[29],face[5]);
  printf("  -----------  -----------  -----------  -----------\n");
  printf(" | %c | G | %c || %c | O | %c || %c | B | %c || %c | R | %c |\n",
  face[34],face[33],face[32],face[39],face[38],face[37],face[36],face[35]);
  printf("  -----------  -----------  -----------  -----------\n");
  printf(" | %c | %c | %c || %c | %c | %c || %c | %c | %c || %c | %c | %c |\n",face[17],face[43],
  face[13],face[14],face[41],face[22],face[23],face[47],face[19],face[20],face[45],face[16]);
  printf("  -----------  ===========  -----------  -----------\n");
  printf("              | %c | %c | %c |\n",face[12],face[40],face[21]);
  printf("               -----------\n");
  printf("              | %c | W | %c |     ",face[42],face[46]);
  printf("%u moves to solve corners.\n",C_path_length(corners, cdatabase));
  printf("               -----------      ");
  printf("%u moves to solve edges 1-6.\n",E1_path_length(edges, e1database));
  printf("              | %c | %c | %c |     ",face[15],face[44],face[18]);
  printf("%u moves to solve edges 7-12.\n",E2_path_length(edges, e2database));
  printf("               -----------\n\n");
}

/* Checks to see if a given combination of the cube is
   a member of the subgraph that contains the solution state. */
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
  int16_t vis_edges = 0x0000;
  int8_t vis_corners = 0x00;

  // Count number of even corner cycles.
  while (vis_corners != -1) {

    // If unvisited, Set corner at pos as visited and get new pos.  Increment count.
    if (!(vis_corners & 1 << (7-pos))) {
      vis_corners = vis_corners | 1 << (7-pos);
      pos = corners[pos]/3;
      count++;
    }
    // If pos was visited, end of cycle.  see if count if even.  increment if it is. set count to 0 again.
    else {
      if (count%2 == 0)
        even_corners++;
      count = 0;
      // Increment leftmost until there is a pos that is unvisited.  Set new pos.
      for (i=vis_corners<<leftmost; i<0; leftmost++)
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
  while (vis_edges != 0XFFF) {

    // If unvisited, Set edge at pos as visited and get new pos.  Increment count.
    if (!(vis_edges & 1 << (11-pos))) {
      vis_edges = vis_edges | 1 << (11-pos);
      pos = edges[pos]/2;
      count++;
    }
    // If pos was visited, end of cycle.  see if count if even.  increment if it is. set count to 0 again.
    else {
      if (count%2 == 0)
        even_edges++;
      count = 0;

      // Increment leftmost until there is a pos that is unvisited.  Set new pos.
      for (j=vis_edges<<(4+leftmost); j < 0; leftmost++)
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

void display_scramble(uint8_t *corners, uint8_t *edges) {
  printf("Corners: {%2u, %2u, %2u, %2u, %2u, %2u, %2u, %2u}\n", corners[0], corners[1], corners[2], corners[3], corners[4], corners[5], corners[6], corners[7]);
  printf("Edges:   {%2u, %2u, %2u, %2u, %2u, %2u, %2u, %2u, %2u, %2u, %2u, %2u}\n", edges[0], edges[1], edges[2], edges[3], edges[4], edges[5], edges[6], edges[7], edges[8], edges[9], edges[10], edges[11]);
}

int64_t E1_bijective(uint8_t *edges) {
    // Encode
    int64_t index = E1_get_index(edges);

    // Decode
    uint8_t temp[NUM_EDGES];
    E1_decode_index(index, temp);

    // Encode again and return difference.
    return index - E1_get_index(temp);
}

int64_t E2_bijective(uint8_t *edges) {
    // Encode
    int64_t index = E2_get_index(edges);

    // Decode
    uint8_t temp[NUM_EDGES];
    E2_decode_index(index, temp);

    // Encode again and return difference.
    return index - E2_get_index(temp);
}

int64_t C_bijective(uint8_t *corners) {
  unsigned index = C_get_index(corners);
  printf("%u\n", index);
  uint8_t temp[NUM_CORNERS];
  C_decode_index(index, temp);

  for (int i=0; i<8; i++)
    printf("%u, ", corners[i]);

  putchar('\n');

  for (int i=0; i<8; i++)
    printf("%u, ", temp[i]);

  putchar('\n');

  return index - C_get_index(temp);
}
