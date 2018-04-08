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
#include "moves.h"
#include "mymath.h"
#include "cdatabase.h"
#include "edatabase.h"
#include "testheuristic.h"

static uint8_t cdatabase[C_DB_SIZE];
static uint8_t e1database[E_DB_SIZE];
static uint8_t e2database[E_DB_SIZE];

int main() {

  // Load databases.
  int fd;
  if ((fd = open("corners.patdb", O_RDONLY)) == -1) {
    perror("Could not open corners.patdb");
    exit(1);
  }
  read(fd, cdatabase, C_DB_SIZE);
  close(fd);
  
  if ((fd = open("edges1.patdb", O_RDONLY)) == -1) {
    perror("Could not open edges1.patdb");
    exit(1);
  }
  read(fd, e1database, E_DB_SIZE);
  close(fd);

  if ((fd = open("edges2.patdb", O_RDONLY)) == -1) {
    perror("Could not open edges2.patdb");
    exit(1);
  }
  read(fd, e2database, E_DB_SIZE);
  close(fd);

  // Get scramble algorithm and execute it on solved combination.
  char scramble[256];
  while (1) {

    // Get scramble algorithm from user.
    fgets(scramble, 256, stdin);

    // Initialize cube as solved.
    int i;
    uint8_t corners[128][8];
    for (i=0; i<8; i++)
      corners[0][i] = 3*i;

    uint8_t edges[128][12];
    for (i=0; i<12; i++)
      edges[0][i] = 2*i;

    // Tokenize user input and perform moves.
    char* token = strtok(scramble, " \n()[]\t{}");
    i=0;
    while (token) {
      if (strcmp(token, "U") == 0) {
        C_turn_U(corners[i], corners[i+1]);
        E_turn_U(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "U2") == 0) {
        C_turn_U2(corners[i], corners[i+1]);
        E_turn_U2(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "U'") == 0) {
        C_turn_Uprime(corners[i], corners[i+1]);
        E_turn_Uprime(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "F") == 0) {
        C_turn_F(corners[i], corners[i+1]);
        E_turn_F(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "F2") == 0) {
        C_turn_F2(corners[i], corners[i+1]);
        E_turn_F2(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "F'") == 0) {
        C_turn_Fprime(corners[i], corners[i+1]);
        E_turn_Fprime(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "L") == 0) {
        C_turn_L(corners[i], corners[i+1]);
        E_turn_L(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "L2") == 0) {
        C_turn_L2(corners[i], corners[i+1]);
        E_turn_L2(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "L'") == 0) {
        C_turn_Lprime(corners[i], corners[i+1]);
        E_turn_Lprime(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "B") == 0) {
        C_turn_B(corners[i], corners[i+1]);
        E_turn_B(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "B2") == 0) {
        C_turn_B2(corners[i], corners[i+1]);
        E_turn_B2(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "B'") == 0) {
        C_turn_Bprime(corners[i], corners[i+1]);
        E_turn_Bprime(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "R") == 0) {
        C_turn_R(corners[i], corners[i+1]);
        E_turn_R(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "R2") == 0) {
        C_turn_R2(corners[i], corners[i+1]);
        E_turn_R2(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "R'") == 0) {
        C_turn_Rprime(corners[i], corners[i+1]);
        E_turn_Rprime(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "D") == 0) {
        C_turn_D(corners[i], corners[i+1]);
        E_turn_D(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "D2") == 0) {
        C_turn_D2(corners[i], corners[i+1]);
        E_turn_D2(edges[i], edges[i+1]);
        i++;
      }
      else if (strcmp(token, "D'") == 0) {
        C_turn_Dprime(corners[i], corners[i+1]);
        E_turn_Dprime(edges[i], edges[i+1]);
        i++;
      }
      token = strtok(NULL, " \n()[]\t{}");
    }

    // Print resulting combination and database results.
    display_cube(corners[i], edges[i]);
    printf("%u\n", valid_comb(corners[i], edges[i]));
  }
}

// Creates an ASCII representation of the cube in the CLI.
void display_cube(uint8_t *corners, uint8_t *edges) {

  // Set up cubies.
  char c[8][3][4] = {"YOG", "GYO", "OGY",
                     "YGR", "RYG", "GRY",
                     "YRB", "BYR", "RBY",
                     "YBO", "OYB", "BOY",
                     "WGO", "OWG", "GOW",
                     "WRG", "GWR", "RGW",
                     "WBR", "RWB", "BRW",
                     "WOB", "BWO", "OBW"};
  char e[12][2][3] = {"YO", "OY",
                      "YG", "GY",
                      "YR", "RY",
                      "YB", "BY",
                      "OG", "GO",
                      "GR", "RG",
                      "RB", "BR",
                      "BO", "OB",
                      "WO", "OW",
                      "WG", "GW",
                      "WR", "RW",
                      "WB", "BW"};

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
