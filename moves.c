/*
 * This file contains functions for performing moves on the cube.
 * It also assigns pointers to these functions to a static array
 * called moves so the search algorithm can easily iterate through them.
 */

#include "moves.h"
#include "edatabase.h"

void C_turn_U(uint8_t *comb, uint8_t *next) {
  next[0] = comb[3];
  next[1] = comb[0];
  next[2] = comb[1];
  next[3] = comb[2];
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[7];
}

void C_turn_U2(uint8_t *comb, uint8_t *next) {
  next[0] = comb[2];
  next[1] = comb[3];
  next[2] = comb[0];
  next[3] = comb[1];
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[7];
}

void C_turn_Uprime(uint8_t *comb, uint8_t *next) {
  next[0] = comb[1];
  next[1] = comb[2];
  next[2] = comb[3];
  next[3] = comb[0];
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[7];
}

void C_turn_F(uint8_t *comb, uint8_t *next) {
  next[0] = comb[4]%3 ? comb[4]-1 : comb[4]+2;
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = (comb[0]+1)%3 ? comb[0]+1 : comb[0]-2;
  next[4] = (comb[7]+1)%3 ? comb[7]+1 : comb[7]-2;
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[3]%3 ? comb[3]-1 : comb[3]+2;
}

void C_turn_F2(uint8_t *comb, uint8_t *next) {
  next[0] = comb[7];
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[4];
  next[4] = comb[3];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[0];
}

void C_turn_Fprime(uint8_t *comb, uint8_t *next) {
  next[0] = comb[3]%3 ? comb[3]-1 : comb[3]+2;
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = (comb[7]+1)%3 ? comb[7]+1 : comb[7]-2;
  next[4] = (comb[0]+1)%3 ? comb[0]+1 : comb[0]-2;
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[4]%3 ? comb[4]-1 : comb[4]+2;
}

void C_turn_L(uint8_t *comb, uint8_t *next) {
  next[0] = (comb[1]+1)%3 ? comb[1]+1 : comb[1]-2;
  next[1] = comb[5]%3 ? comb[5]-1 : comb[5]+2;
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[0]%3 ? comb[0]-1 : comb[0]+2;
  next[5] = (comb[4]+1)%3 ? comb[4]+1 : comb[4]-2;
  next[6] = comb[6];
  next[7] = comb[7];
}

void C_turn_L2(uint8_t *comb, uint8_t *next) {
  next[0] = comb[5];
  next[1] = comb[4];
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[1];
  next[5] = comb[0];
  next[6] = comb[6];
  next[7] = comb[7];
}

void C_turn_Lprime(uint8_t *comb, uint8_t *next) {
  next[0] = (comb[4]+1)%3 ? comb[4]+1 : comb[4]-2;
  next[1] = comb[0]%3 ? comb[0]-1 : comb[0]+2;
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[5]%3 ? comb[5]-1 : comb[5]+2;
  next[5] = (comb[1]+1)%3 ? comb[1]+1 : comb[1]-2;
  next[6] = comb[6];
  next[7] = comb[7];
}

void C_turn_B(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = (comb[2]+1)%3 ? comb[2]+1 : comb[2]-2;
  next[2] = comb[6]%3 ? comb[6]-1 : comb[6]+2;
  next[3] = comb[3];
  next[4] = comb[4];
  next[5] = comb[1]%3 ? comb[1]-1 : comb[1]+2;
  next[6] = (comb[5]+1)%3 ? comb[5]+1 : comb[5]-2;
  next[7] = comb[7];
}

void C_turn_B2(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[6];
  next[2] = comb[5];
  next[3] = comb[3];
  next[4] = comb[4];
  next[5] = comb[2];
  next[6] = comb[1];
  next[7] = comb[7];
}

void C_turn_Bprime(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = (comb[5]+1)%3 ? comb[5]+1 : comb[5]-2;
  next[2] = comb[1]%3 ? comb[1]-1 : comb[1]+2;
  next[3] = comb[3];
  next[4] = comb[4];
  next[5] = comb[6]%3 ? comb[6]-1 : comb[6]+2;
  next[6] = (comb[2]+1)%3 ? comb[2]+1 : comb[2]-2;
  next[7] = comb[7];
}

void C_turn_R(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = (comb[3]+1)%3 ? comb[3]+1 : comb[3]-2;
  next[3] = comb[7]%3 ? comb[7]-1 : comb[7]+2;
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[2]%3 ? comb[2]-1 : comb[2]+2;
  next[7] = (comb[6]+1)%3 ? comb[6]+1 : comb[6]-2;
}

void C_turn_R2(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[7];
  next[3] = comb[6];
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[3];
  next[7] = comb[2];
}

void C_turn_Rprime(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = (comb[6]+1)%3 ? comb[6]+1 : comb[6]-2;
  next[3] = comb[2]%3 ? comb[2]-1 : comb[2]+2;
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[7]%3 ? comb[7]-1 : comb[7]+2;
  next[7] = (comb[3]+1)%3 ? comb[3]+1 : comb[3]-2;
}

void C_turn_D(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[5];
  next[5] = comb[6];
  next[6] = comb[7];
  next[7] = comb[4];
}

void C_turn_D2(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[6];
  next[5] = comb[7];
  next[6] = comb[4];
  next[7] = comb[5];
}

void C_turn_Dprime(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[7];
  next[5] = comb[4];
  next[6] = comb[5];
  next[7] = comb[6];
}

unsigned E_turn_U(uint8_t *comb, uint8_t *next) {
  if (((next[0] = comb[3]) OP BOUND) & 
      ((next[1] = comb[0]) OP BOUND) &
      ((next[2] = comb[1]) OP BOUND) &
      ((next[3] = comb[2]) OP BOUND))
    return 0;
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[7];
  next[8] = comb[8];
  next[9] = comb[9];
  next[10] = comb[10];
  next[11] = comb[11];
  return 1;
}

unsigned E_turn_U2(uint8_t *comb, uint8_t *next) {
  if (((next[0] = comb[2]) OP BOUND) & 
      ((next[1] = comb[3]) OP BOUND) &
      ((next[2] = comb[0]) OP BOUND) &
      ((next[3] = comb[1]) OP BOUND))
    return 0;
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[7];
  next[8] = comb[8];
  next[9] = comb[9];
  next[10] = comb[10];
  next[11] = comb[11];
  return 1;
}

unsigned E_turn_Uprime(uint8_t *comb, uint8_t *next) {
  if (((next[0] = comb[1]) OP BOUND) & 
      ((next[1] = comb[2]) OP BOUND) &
      ((next[2] = comb[3]) OP BOUND) &
      ((next[3] = comb[0]) OP BOUND))
    return 0;
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[7];
  next[8] = comb[8];
  next[9] = comb[9];
  next[10] = comb[10];
  next[11] = comb[11];
  return 1;

}

unsigned E_turn_F(uint8_t *comb, uint8_t *next) {
  if (((next[7] = comb[0]) OP BOUND) &
      ((next[8] = comb[7]) OP BOUND) &
      ((next[0] = comb[4]%2 ? comb[4]-1 : comb[4]+1) OP BOUND) &
      ((next[4] = comb[8]%2 ? comb[8]-1 : comb[8]+1) OP BOUND))
    return 0;
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[3];
  next[5] = comb[5];
  next[6] = comb[6];
  next[9] = comb[9];
  next[10] = comb[10];
  next[11] = comb[11];
  return 1;
}

unsigned E_turn_F2(uint8_t *comb, uint8_t *next) {
  if (((next[0] = comb[8]) OP BOUND) &
      ((next[8] = comb[0]) OP BOUND) &
      ((next[4] = comb[7]%2 ? comb[7]-1 : comb[7]+1) OP BOUND) &
      ((next[7] = comb[4]%2 ? comb[4]-1 : comb[4]+1) OP BOUND))
    return 0;
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[3];
  next[5] = comb[5];
  next[6] = comb[6];
  next[9] = comb[9];
  next[10] = comb[10];
  next[11] = comb[11];
  return 1;
}

unsigned E_turn_Fprime(uint8_t *comb, uint8_t *next) {
  if (((next[0] = comb[7]) OP BOUND) &
      ((next[7] = comb[8]) OP BOUND) &
      ((next[4] = comb[0]%2 ? comb[0]-1 : comb[0]+1) OP BOUND) &
      ((next[8] = comb[4]%2 ? comb[4]-1 : comb[4]+1) OP BOUND))
    return 0;
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[3];
  next[5] = comb[5];
  next[6] = comb[6];
  next[9] = comb[9];
  next[10] = comb[10];
  next[11] = comb[11];
  return 1;
}

unsigned E_turn_L(uint8_t *comb, uint8_t *next) {
  if (((next[4] = comb[1]) OP BOUND) &
      ((next[9] = comb[4]) OP BOUND) &
      ((next[1] = comb[5]%2 ? comb[5]-1 : comb[5]+1) OP BOUND) &
      ((next[5] = comb[9]%2 ? comb[9]-1 : comb[9]+1) OP BOUND))
    return 0;
  next[0] = comb[0];
  next[2] = comb[2];
  next[3] = comb[3];
  next[6] = comb[6];
  next[7] = comb[7];
  next[8] = comb[8];
  next[10] = comb[10];
  next[11] = comb[11];
  return 1;
}

unsigned E_turn_L2(uint8_t *comb, uint8_t *next) {
  if (((next[1] = comb[9]) OP BOUND) &
      ((next[9] = comb[1]) OP BOUND) &
      ((next[4] = comb[5]%2 ? comb[5]-1 : comb[5]+1) OP BOUND) &
      ((next[5] = comb[4]%2 ? comb[4]-1 : comb[4]+1) OP BOUND))
    return 0;
  next[0] = comb[0];
  next[2] = comb[2];
  next[3] = comb[3];
  next[6] = comb[6];
  next[7] = comb[7];
  next[8] = comb[8];
  next[10] = comb[10];
  next[11] = comb[11];
  return 1;
}

unsigned E_turn_Lprime(uint8_t *comb, uint8_t *next) {
  if (((next[1] = comb[4]) OP BOUND) &
      ((next[4] = comb[9]) OP BOUND) &
      ((next[5] = comb[1]%2 ? comb[1]-1 : comb[1]+1) OP BOUND) &
      ((next[9] = comb[5]%2 ? comb[5]-1 : comb[5]+1) OP BOUND))
    return 0;
  next[0] = comb[0];
  next[2] = comb[2];
  next[3] = comb[3];
  next[6] = comb[6];
  next[7] = comb[7];
  next[8] = comb[8];
  next[10] = comb[10];
  next[11] = comb[11];
  return 1;
}

unsigned E_turn_B(uint8_t *comb, uint8_t *next) {
  if (((next[5] = comb[2]) OP BOUND) &
      ((next[10] = comb[5]) OP BOUND) &
      ((next[2] = comb[6]%2 ? comb[6]-1 : comb[6]+1) OP BOUND) &
      ((next[6] = comb[10]%2 ? comb[10]-1 : comb[10]+1) OP BOUND))
    return 0;
  next[0] = comb[0];
  next[1] = comb[1];
  next[3] = comb[3];
  next[4] = comb[4];
  next[7] = comb[7];
  next[8] = comb[8];
  next[9] = comb[9];
  next[11] = comb[11];
  return 1;
}

unsigned E_turn_B2(uint8_t *comb, uint8_t *next) {
  if (((next[2] = comb[10]) OP BOUND) &
      ((next[10] = comb[2]) OP BOUND) &
      ((next[5] = comb[6]%2 ? comb[6]-1 : comb[6]+1) OP BOUND) &
      ((next[6] = comb[5]%2 ? comb[5]-1 : comb[5]+1) OP BOUND))
    return 0;
  next[0] = comb[0];
  next[1] = comb[1];
  next[3] = comb[3];
  next[4] = comb[4];
  next[7] = comb[7];
  next[8] = comb[8];
  next[9] = comb[9];
  next[11] = comb[11];
  return 1;
}

unsigned E_turn_Bprime(uint8_t *comb, uint8_t *next) {
  if (((next[2] = comb[5]) OP BOUND) &
      ((next[5] = comb[10]) OP BOUND) &
      ((next[6] = comb[2]%2 ? comb[2]-1 : comb[2]+1) OP BOUND) &
      ((next[10] = comb[6]%2 ? comb[6]-1 : comb[6]+1) OP BOUND))
    return 0;
  next[0] = comb[0];
  next[1] = comb[1];
  next[3] = comb[3];
  next[4] = comb[4];
  next[7] = comb[7];
  next[8] = comb[8];
  next[9] = comb[9];
  next[11] = comb[11];
  return 1;
}

unsigned E_turn_R(uint8_t *comb, uint8_t *next) {
  if (((next[6] = comb[3]) OP BOUND) &
      ((next[11] = comb[6]) OP BOUND) &
      ((next[3] = comb[7]%2 ? comb[7]-1 : comb[7]+1) OP BOUND) &
      ((next[7] = comb[11]%2 ? comb[11]-1 : comb[11]+1) OP BOUND))
    return 0;
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[2];
  next[4] = comb[4];
  next[5] = comb[5];
  next[8] = comb[8];
  next[9] = comb[9];
  next[10] = comb[10];
  return 1;
}

unsigned E_turn_R2(uint8_t *comb, uint8_t *next) {
  if (((next[3] = comb[11]) OP BOUND) &
      ((next[11] = comb[3]) OP BOUND) &
      ((next[6] = comb[7]%2 ? comb[7]-1 : comb[7]+1) OP BOUND) &
      ((next[7] = comb[6]%2 ? comb[6]-1 : comb[6]+1) OP BOUND))
    return 0;
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[2];
  next[4] = comb[4];
  next[5] = comb[5];
  next[8] = comb[8];
  next[9] = comb[9];
  next[10] = comb[10];
  return 1;
}

unsigned E_turn_Rprime(uint8_t *comb, uint8_t *next) {
  if (((next[3] = comb[6]) OP BOUND) &
      ((next[6] = comb[11]) OP BOUND) &
      ((next[7] = comb[3]%2 ? comb[3]-1 : comb[3]+1) OP BOUND) &
      ((next[11] = comb[7]%2 ? comb[7]-1 : comb[7]+1) OP BOUND))
    return 0;
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[2];
  next[4] = comb[4];
  next[5] = comb[5];
  next[8] = comb[8];
  next[9] = comb[9];
  next[10] = comb[10];
  return 1;
}

unsigned E_turn_D(uint8_t *comb, uint8_t *next) {
  if (((next[8] = comb[9]) OP BOUND) &
      ((next[9] = comb[10]) OP BOUND) &
      ((next[10] = comb[11]) OP BOUND) &
      ((next[11] = comb[8]) OP BOUND))
    return 0;
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[7];
  return 1;
}

unsigned E_turn_D2(uint8_t *comb, uint8_t *next) {
  if (((next[8] = comb[10]) OP BOUND) &
      ((next[9] = comb[11]) OP BOUND) &
      ((next[10] = comb[8]) OP BOUND) &
      ((next[11] = comb[9]) OP BOUND))
    return 0;
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[7];
  return 1;
}

unsigned E_turn_Dprime(uint8_t *comb, uint8_t *next) {
  if (((next[8] = comb[11]) OP BOUND) &
      ((next[9] = comb[8]) OP BOUND) &
      ((next[10] = comb[9]) OP BOUND) &
      ((next[11] = comb[10]) OP BOUND))
    return 0;
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[7];
  return 1;
}

void initialize_turns(void) {
  movesC[0] = C_turn_U;
  movesC[1] = C_turn_U2;
  movesC[2] = C_turn_Uprime;
  movesC[3] = C_turn_F;
  movesC[4] = C_turn_F2;
  movesC[5] = C_turn_Fprime;
  movesC[6] = C_turn_L;
  movesC[7] = C_turn_L2;
  movesC[8] = C_turn_Lprime;
  movesC[9] = C_turn_B;
  movesC[10] = C_turn_B2;
  movesC[11] = C_turn_Bprime;
  movesC[12] = C_turn_R;
  movesC[13] = C_turn_R2;
  movesC[14] = C_turn_Rprime;
  movesC[15] = C_turn_D;
  movesC[16] = C_turn_D2;
  movesC[17] = C_turn_Dprime;
  movesE[0] = E_turn_U;
  movesE[1] = E_turn_U2;
  movesE[2] = E_turn_Uprime;
  movesE[3] = E_turn_F;
  movesE[4] = E_turn_F2;
  movesE[5] = E_turn_Fprime;
  movesE[6] = E_turn_L;
  movesE[7] = E_turn_L2;
  movesE[8] = E_turn_Lprime;
  movesE[9] = E_turn_B;
  movesE[10] = E_turn_B2;
  movesE[11] = E_turn_Bprime;
  movesE[12] = E_turn_R;
  movesE[13] = E_turn_R2;
  movesE[14] = E_turn_Rprime;
  movesE[15] = E_turn_D;
  movesE[16] = E_turn_D2;
  movesE[17] = E_turn_Dprime;
}

void (*movesC[18])(uint8_t*, uint8_t*);
unsigned (*movesE[18])(uint8_t*, uint8_t*);
