/*
 * This file contains functions for performing moves on the cube.
 * It also assigns pointers to these functions to a static array
 * called moves so the search algorithm can easily iterate through them.
 */

#include "searchmoves.h"
#include "cdatabase.h"
#include "edatabase.h"
#include "IDAstar.h"

void turn_U(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[3];
  next->corners[1] = prev->corners[0];
  next->corners[2] = prev->corners[1];
  next->corners[3] = prev->corners[2];
  next->corners[4] = prev->corners[4];
  next->corners[5] = prev->corners[5];
  next->corners[6] = prev->corners[6];
  next->corners[7] = prev->corners[7];

  next->edges[0] = prev->edges[3];
  next->edges[1] = prev->edges[0];
  next->edges[2] = prev->edges[1];
  next->edges[3] = prev->edges[2];
  next->edges[4] = prev->edges[4];
  next->edges[5] = prev->edges[5];
  next->edges[6] = prev->edges[6];
  next->edges[7] = prev->edges[7];
  next->edges[8] = prev->edges[8];
  next->edges[9] = prev->edges[9];
  next->edges[10] = prev->edges[10];
  next->edges[11] = prev->edges[11];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_U2(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[2];
  next->corners[1] = prev->corners[3];
  next->corners[2] = prev->corners[0];
  next->corners[3] = prev->corners[1];
  next->corners[4] = prev->corners[4];
  next->corners[5] = prev->corners[5];
  next->corners[6] = prev->corners[6];
  next->corners[7] = prev->corners[7];

  next->edges[0] = prev->edges[2];
  next->edges[1] = prev->edges[3];
  next->edges[2] = prev->edges[0];
  next->edges[3] = prev->edges[1];
  next->edges[4] = prev->edges[4];
  next->edges[5] = prev->edges[5];
  next->edges[6] = prev->edges[6];
  next->edges[7] = prev->edges[7];
  next->edges[8] = prev->edges[8];
  next->edges[9] = prev->edges[9];
  next->edges[10] = prev->edges[10];
  next->edges[11] = prev->edges[11];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_Uprime(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[1];
  next->corners[1] = prev->corners[2];
  next->corners[2] = prev->corners[3];
  next->corners[3] = prev->corners[0];
  next->corners[4] = prev->corners[4];
  next->corners[5] = prev->corners[5];
  next->corners[6] = prev->corners[6];
  next->corners[7] = prev->corners[7];

  next->edges[0] = prev->edges[1];
  next->edges[1] = prev->edges[2];
  next->edges[2] = prev->edges[3];
  next->edges[3] = prev->edges[0];
  next->edges[4] = prev->edges[4];
  next->edges[5] = prev->edges[5];
  next->edges[6] = prev->edges[6];
  next->edges[7] = prev->edges[7];
  next->edges[8] = prev->edges[8];
  next->edges[9] = prev->edges[9];
  next->edges[10] = prev->edges[10];
  next->edges[11] = prev->edges[11];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_F(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[4]%3 ? prev->corners[4]-1 : prev->corners[4]+2;
  next->corners[1] = prev->corners[1];
  next->corners[2] = prev->corners[2];
  next->corners[3] = (prev->corners[0]+1)%3 ? prev->corners[0]+1 : prev->corners[0]-2;
  next->corners[4] = (prev->corners[7]+1)%3 ? prev->corners[7]+1 : prev->corners[7]-2;
  next->corners[5] = prev->corners[5];
  next->corners[6] = prev->corners[6];
  next->corners[7] = prev->corners[3]%3 ? prev->corners[3]-1 : prev->corners[3]+2;

  next->edges[0] = prev->edges[4]%2 ? prev->edges[4]-1 : prev->edges[4]+1;
  next->edges[1] = prev->edges[1];
  next->edges[2] = prev->edges[2];
  next->edges[3] = prev->edges[3];
  next->edges[4] = prev->edges[8]%2 ? prev->edges[8]-1 : prev->edges[8]+1;
  next->edges[5] = prev->edges[5];
  next->edges[6] = prev->edges[6];
  next->edges[7] = prev->edges[0];
  next->edges[8] = prev->edges[7];
  next->edges[9] = prev->edges[9];
  next->edges[10] = prev->edges[10];
  next->edges[11] = prev->edges[11];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_F2(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[7];
  next->corners[1] = prev->corners[1];
  next->corners[2] = prev->corners[2];
  next->corners[3] = prev->corners[4];
  next->corners[4] = prev->corners[3];
  next->corners[5] = prev->corners[5];
  next->corners[6] = prev->corners[6];
  next->corners[7] = prev->corners[0];

  next->edges[0] = prev->edges[8];
  next->edges[1] = prev->edges[1];
  next->edges[2] = prev->edges[2];
  next->edges[3] = prev->edges[3];
  next->edges[4] = prev->edges[7]%2 ? prev->edges[7]-1 : prev->edges[7]+1;
  next->edges[5] = prev->edges[5];
  next->edges[6] = prev->edges[6];
  next->edges[7] = prev->edges[4]%2 ? prev->edges[4]-1 : prev->edges[4]+1;
  next->edges[8] = prev->edges[0];
  next->edges[9] = prev->edges[9];
  next->edges[10] = prev->edges[10];
  next->edges[11] = prev->edges[11];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_Fprime(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[3]%3 ? prev->corners[3]-1 : prev->corners[3]+2;
  next->corners[1] = prev->corners[1];
  next->corners[2] = prev->corners[2];
  next->corners[3] = (prev->corners[7]+1)%3 ? prev->corners[7]+1 : prev->corners[7]-2;
  next->corners[4] = (prev->corners[0]+1)%3 ? prev->corners[0]+1 : prev->corners[0]-2;
  next->corners[5] = prev->corners[5];
  next->corners[6] = prev->corners[6];
  next->corners[7] = prev->corners[4]%3 ? prev->corners[4]-1 : prev->corners[4]+2;

  next->edges[0] = prev->edges[7];
  next->edges[1] = prev->edges[1];
  next->edges[2] = prev->edges[2];
  next->edges[3] = prev->edges[3];
  next->edges[4] = prev->edges[0]%2 ? prev->edges[0]-1 : prev->edges[0]+1;
  next->edges[5] = prev->edges[5];
  next->edges[6] = prev->edges[6];
  next->edges[7] = prev->edges[8];
  next->edges[8] = prev->edges[4]%2 ? prev->edges[4]-1 : prev->edges[4]+1;
  next->edges[9] = prev->edges[9];
  next->edges[10] = prev->edges[10];
  next->edges[11] = prev->edges[11];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_L(NODE *prev, NODE *next) {
  next->corners[0] = (prev->corners[1]+1)%3 ? prev->corners[1]+1 : prev->corners[1]-2;
  next->corners[1] = prev->corners[5]%3 ? prev->corners[5]-1 : prev->corners[5]+2;
  next->corners[2] = prev->corners[2];
  next->corners[3] = prev->corners[3];
  next->corners[4] = prev->corners[0]%3 ? prev->corners[0]-1 : prev->corners[0]+2;
  next->corners[5] = (prev->corners[4]+1)%3 ? prev->corners[4]+1 : prev->corners[4]-2;
  next->corners[6] = prev->corners[6];
  next->corners[7] = prev->corners[7];

  next->edges[0] = prev->edges[0];
  next->edges[1] = prev->edges[5]%2 ? prev->edges[5]-1 : prev->edges[5]+1;
  next->edges[2] = prev->edges[2];
  next->edges[3] = prev->edges[3];
  next->edges[4] = prev->edges[1];
  next->edges[5] = prev->edges[9]%2 ? prev->edges[9]-1 : prev->edges[9]+1;
  next->edges[6] = prev->edges[6];
  next->edges[7] = prev->edges[7];
  next->edges[8] = prev->edges[8];
  next->edges[9] = prev->edges[4];
  next->edges[10] = prev->edges[10];
  next->edges[11] = prev->edges[11];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_L2(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[5];
  next->corners[1] = prev->corners[4];
  next->corners[2] = prev->corners[2];
  next->corners[3] = prev->corners[3];
  next->corners[4] = prev->corners[1];
  next->corners[5] = prev->corners[0];
  next->corners[6] = prev->corners[6];
  next->corners[7] = prev->corners[7];

  next->edges[0] = prev->edges[0];
  next->edges[1] = prev->edges[9];
  next->edges[2] = prev->edges[2];
  next->edges[3] = prev->edges[3];
  next->edges[4] = prev->edges[5]%2 ? prev->edges[5]-1 : prev->edges[5]+1;
  next->edges[5] = prev->edges[4]%2 ? prev->edges[4]-1 : prev->edges[4]+1;
  next->edges[6] = prev->edges[6];
  next->edges[7] = prev->edges[7];
  next->edges[8] = prev->edges[8];
  next->edges[9] = prev->edges[1];
  next->edges[10] = prev->edges[10];
  next->edges[11] = prev->edges[11];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_Lprime(NODE *prev, NODE *next) {
  next->corners[0] = (prev->corners[4]+1)%3 ? prev->corners[4]+1 : prev->corners[4]-2;
  next->corners[1] = prev->corners[0]%3 ? prev->corners[0]-1 : prev->corners[0]+2;
  next->corners[2] = prev->corners[2];
  next->corners[3] = prev->corners[3];
  next->corners[4] = prev->corners[5]%3 ? prev->corners[5]-1 : prev->corners[5]+2;
  next->corners[5] = (prev->corners[1]+1)%3 ? prev->corners[1]+1 : prev->corners[1]-2;
  next->corners[6] = prev->corners[6];
  next->corners[7] = prev->corners[7];

  next->edges[0] = prev->edges[0];
  next->edges[1] = prev->edges[4];
  next->edges[2] = prev->edges[2];
  next->edges[3] = prev->edges[3];
  next->edges[4] = prev->edges[9];
  next->edges[5] = prev->edges[1]%2 ? prev->edges[1]-1 : prev->edges[1]+1;
  next->edges[6] = prev->edges[6];
  next->edges[7] = prev->edges[7];
  next->edges[8] = prev->edges[8];
  next->edges[9] = prev->edges[5]%2 ? prev->edges[5]-1 : prev->edges[5]+1;
  next->edges[10] = prev->edges[10];
  next->edges[11] = prev->edges[11];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_B(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[0];
  next->corners[1] = (prev->corners[2]+1)%3 ? prev->corners[2]+1 : prev->corners[2]-2;
  next->corners[2] = prev->corners[6]%3 ? prev->corners[6]-1 : prev->corners[6]+2;
  next->corners[3] = prev->corners[3];
  next->corners[4] = prev->corners[4];
  next->corners[5] = prev->corners[1]%3 ? prev->corners[1]-1 : prev->corners[1]+2;
  next->corners[6] = (prev->corners[5]+1)%3 ? prev->corners[5]+1 : prev->corners[5]-2;
  next->corners[7] = prev->corners[7];

  next->edges[0] = prev->edges[0];
  next->edges[1] = prev->edges[1];
  next->edges[2] = prev->edges[6]%2 ? prev->edges[6]-1 : prev->edges[6]+1;
  next->edges[3] = prev->edges[3];
  next->edges[4] = prev->edges[4];
  next->edges[5] = prev->edges[2];
  next->edges[6] = prev->edges[10]%2 ? prev->edges[10]-1 : prev->edges[10]+1;
  next->edges[7] = prev->edges[7];
  next->edges[8] = prev->edges[8];
  next->edges[9] = prev->edges[9];
  next->edges[10] = prev->edges[5];
  next->edges[11] = prev->edges[11];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_B2(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[0];
  next->corners[1] = prev->corners[6];
  next->corners[2] = prev->corners[5];
  next->corners[3] = prev->corners[3];
  next->corners[4] = prev->corners[4];
  next->corners[5] = prev->corners[2];
  next->corners[6] = prev->corners[1];
  next->corners[7] = prev->corners[7];

  next->edges[0] = prev->edges[0];
  next->edges[1] = prev->edges[1];
  next->edges[2] = prev->edges[10];
  next->edges[3] = prev->edges[3];
  next->edges[4] = prev->edges[4];
  next->edges[5] = prev->edges[6]%2 ? prev->edges[6]-1 : prev->edges[6]+1;
  next->edges[6] = prev->edges[5]%2 ? prev->edges[5]-1 : prev->edges[5]+1;
  next->edges[7] = prev->edges[7];
  next->edges[8] = prev->edges[8];
  next->edges[9] = prev->edges[9];
  next->edges[10] = prev->edges[2];
  next->edges[11] = prev->edges[11];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_Bprime(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[0];
  next->corners[1] = (prev->corners[5]+1)%3 ? prev->corners[5]+1 : prev->corners[5]-2;
  next->corners[2] = prev->corners[1]%3 ? prev->corners[1]-1 : prev->corners[1]+2;
  next->corners[3] = prev->corners[3];
  next->corners[4] = prev->corners[4];
  next->corners[5] = prev->corners[6]%3 ? prev->corners[6]-1 : prev->corners[6]+2;
  next->corners[6] = (prev->corners[2]+1)%3 ? prev->corners[2]+1 : prev->corners[2]-2;
  next->corners[7] = prev->corners[7];

  next->edges[0] = prev->edges[0];
  next->edges[1] = prev->edges[1];
  next->edges[2] = prev->edges[5];
  next->edges[3] = prev->edges[3];
  next->edges[4] = prev->edges[4];
  next->edges[5] = prev->edges[10];
  next->edges[6] = prev->edges[2]%2 ? prev->edges[2]-1 : prev->edges[2]+1;
  next->edges[7] = prev->edges[7];
  next->edges[8] = prev->edges[8];
  next->edges[9] = prev->edges[9];
  next->edges[10] = prev->edges[6]%2 ? prev->edges[6]-1 : prev->edges[6]+1;
  next->edges[11] = prev->edges[11];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_R(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[0];
  next->corners[1] = prev->corners[1];
  next->corners[2] = (prev->corners[3]+1)%3 ? prev->corners[3]+1 : prev->corners[3]-2;
  next->corners[3] = prev->corners[7]%3 ? prev->corners[7]-1 : prev->corners[7]+2;
  next->corners[4] = prev->corners[4];
  next->corners[5] = prev->corners[5];
  next->corners[6] = prev->corners[2]%3 ? prev->corners[2]-1 : prev->corners[2]+2;
  next->corners[7] = (prev->corners[6]+1)%3 ? prev->corners[6]+1 : prev->corners[6]-2;

  next->edges[0] = prev->edges[0];
  next->edges[1] = prev->edges[1];
  next->edges[2] = prev->edges[2];
  next->edges[3] = prev->edges[7]%2 ? prev->edges[7]-1 : prev->edges[7]+1;
  next->edges[4] = prev->edges[4];
  next->edges[5] = prev->edges[5];
  next->edges[6] = prev->edges[3];
  next->edges[7] = prev->edges[11]%2 ? prev->edges[11]-1 : prev->edges[11]+1;;
  next->edges[8] = prev->edges[8];
  next->edges[9] = prev->edges[9];
  next->edges[10] = prev->edges[10];
  next->edges[11] = prev->edges[6];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_R2(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[0];
  next->corners[1] = prev->corners[1];
  next->corners[2] = prev->corners[7];
  next->corners[3] = prev->corners[6];
  next->corners[4] = prev->corners[4];
  next->corners[5] = prev->corners[5];
  next->corners[6] = prev->corners[3];
  next->corners[7] = prev->corners[2];

  next->edges[0] = prev->edges[0];
  next->edges[1] = prev->edges[1];
  next->edges[2] = prev->edges[2];
  next->edges[3] = prev->edges[11];
  next->edges[4] = prev->edges[4];
  next->edges[5] = prev->edges[5];
  next->edges[6] = prev->edges[7]%2 ? prev->edges[7]-1 : prev->edges[7]+1;
  next->edges[7] = prev->edges[6]%2 ? prev->edges[6]-1 : prev->edges[6]+1;
  next->edges[8] = prev->edges[8];
  next->edges[9] = prev->edges[9];
  next->edges[10] = prev->edges[10];
  next->edges[11] = prev->edges[3];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_Rprime(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[0];
  next->corners[1] = prev->corners[1];
  next->corners[2] = (prev->corners[6]+1)%3 ? prev->corners[6]+1 : prev->corners[6]-2;
  next->corners[3] = prev->corners[2]%3 ? prev->corners[2]-1 : prev->corners[2]+2;
  next->corners[4] = prev->corners[4];
  next->corners[5] = prev->corners[5];
  next->corners[6] = prev->corners[7]%3 ? prev->corners[7]-1 : prev->corners[7]+2;
  next->corners[7] = (prev->corners[3]+1)%3 ? prev->corners[3]+1 : prev->corners[3]-2;

  next->edges[0] = prev->edges[0];
  next->edges[1] = prev->edges[1];
  next->edges[2] = prev->edges[2];
  next->edges[3] = prev->edges[6];
  next->edges[4] = prev->edges[4];
  next->edges[5] = prev->edges[5];
  next->edges[6] = prev->edges[11];
  next->edges[7] = prev->edges[3]%2 ? prev->edges[3]-1 : prev->edges[3]+1;
  next->edges[8] = prev->edges[8];
  next->edges[9] = prev->edges[9];
  next->edges[10] = prev->edges[10];
  next->edges[11] = prev->edges[7]%2 ? prev->edges[7]-1 : prev->edges[7]+1;

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_D(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[0];
  next->corners[1] = prev->corners[1];
  next->corners[2] = prev->corners[2];
  next->corners[3] = prev->corners[3];
  next->corners[4] = prev->corners[5];
  next->corners[5] = prev->corners[6];
  next->corners[6] = prev->corners[7];
  next->corners[7] = prev->corners[4];

  next->edges[0] = prev->edges[0];
  next->edges[1] = prev->edges[1];
  next->edges[2] = prev->edges[2];
  next->edges[3] = prev->edges[3];
  next->edges[4] = prev->edges[4];
  next->edges[5] = prev->edges[5];
  next->edges[6] = prev->edges[6];
  next->edges[7] = prev->edges[7];
  next->edges[8] = prev->edges[9];
  next->edges[9] = prev->edges[10];
  next->edges[10] = prev->edges[11];
  next->edges[11] = prev->edges[8];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_D2(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[0];
  next->corners[1] = prev->corners[1];
  next->corners[2] = prev->corners[2];
  next->corners[3] = prev->corners[3];
  next->corners[4] = prev->corners[6];
  next->corners[5] = prev->corners[7];
  next->corners[6] = prev->corners[4];
  next->corners[7] = prev->corners[5];

  next->edges[0] = prev->edges[0];
  next->edges[1] = prev->edges[1];
  next->edges[2] = prev->edges[2];
  next->edges[3] = prev->edges[3];
  next->edges[4] = prev->edges[4];
  next->edges[5] = prev->edges[5];
  next->edges[6] = prev->edges[6];
  next->edges[7] = prev->edges[7];
  next->edges[8] = prev->edges[10];
  next->edges[9] = prev->edges[11];
  next->edges[10] = prev->edges[8];
  next->edges[11] = prev->edges[9];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void turn_Dprime(NODE *prev, NODE *next) {
  next->corners[0] = prev->corners[0];
  next->corners[1] = prev->corners[1];
  next->corners[2] = prev->corners[2];
  next->corners[3] = prev->corners[3];
  next->corners[4] = prev->corners[7];
  next->corners[5] = prev->corners[4];
  next->corners[6] = prev->corners[5];
  next->corners[7] = prev->corners[6];

  next->edges[0] = prev->edges[0];
  next->edges[1] = prev->edges[1];
  next->edges[2] = prev->edges[2];
  next->edges[3] = prev->edges[3];
  next->edges[4] = prev->edges[4];
  next->edges[5] = prev->edges[5];
  next->edges[6] = prev->edges[6];
  next->edges[7] = prev->edges[7];
  next->edges[8] = prev->edges[11];
  next->edges[9] = prev->edges[8];
  next->edges[10] = prev->edges[9];
  next->edges[11] = prev->edges[10];

  next->h = maxh(C_path_length(next->corners, cdatabase),
                 E1_path_length(next->edges, e1database),
                 E2_path_length(next->edges, e2database));
}

void initialize_turns(void) {
  moves[0] = turn_U;
  moves[1] = turn_U2;
  moves[2] = turn_Uprime;
  moves[3] = turn_F;
  moves[4] = turn_F2;
  moves[5] = turn_Fprime;
  moves[6] = turn_L;
  moves[7] = turn_L2;
  moves[8] = turn_Lprime;
  moves[9] = turn_B;
  moves[10] = turn_B2;
  moves[11] = turn_Bprime;
  moves[12] = turn_R;
  moves[13] = turn_R2;
  moves[14] = turn_Rprime;
  moves[15] = turn_D;
  moves[16] = turn_D2;
  moves[17] = turn_Dprime;
}

void (*moves[18])(NODE*, NODE*);
