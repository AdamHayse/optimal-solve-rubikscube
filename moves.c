/*
 * This file contains functions for performing moves on the cube.
 * It also assigns pointers to these functions to a static array
 * called moves so the search algorithm can easily iterate through them.
 */

#include "moves.h"

unsigned C_turn_U(uint8_t *comb, uint8_t *next) {
  next[0] = comb[3];
  next[1] = comb[0];
  next[2] = comb[1];
  next[3] = comb[2];
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[7];
}

unsigned C_turn_U2(uint8_t *comb, uint8_t *next) {
  next[0] = comb[2];
  next[1] = comb[3];
  next[2] = comb[0];
  next[3] = comb[1];
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[7];
}

unsigned C_turn_Uprime(uint8_t *comb, uint8_t *next) {
  next[0] = comb[1];
  next[1] = comb[2];
  next[2] = comb[3];
  next[3] = comb[0];
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[7];
}

unsigned C_turn_F(uint8_t *comb, uint8_t *next) {
  next[0] = comb[4]%3 ? comb[4]-1 : comb[4]+2;
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = (comb[0]+1)%3 ? comb[0]+1 : comb[0]-2;
  next[4] = (comb[7]+1)%3 ? comb[7]+1 : comb[7]-2;
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[3]%3 ? comb[3]-1 : comb[3]+2;
}

unsigned C_turn_F2(uint8_t *comb, uint8_t *next) {
  next[0] = comb[7];
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[4];
  next[4] = comb[3];
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[0];
}

unsigned C_turn_Fprime(uint8_t *comb, uint8_t *next) {
  next[0] = comb[3]%3 ? comb[3]-1 : comb[3]+2;
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = (comb[7]+1)%3 ? comb[7]+1 : comb[7]-2;
  next[4] = (comb[0]+1)%3 ? comb[0]+1 : comb[0]-2;
  next[5] = comb[5];
  next[6] = comb[6];
  next[7] = comb[4]%3 ? comb[4]-1 : comb[4]+2;
}

unsigned C_turn_L(uint8_t *comb, uint8_t *next) {
  next[0] = (comb[1]+1)%3 ? comb[1]+1 : comb[1]-2;
  next[1] = comb[5]%3 ? comb[5]-1 : comb[5]+2;
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[0]%3 ? comb[0]-1 : comb[0]+2;
  next[5] = (comb[4]+1)%3 ? comb[4]+1 : comb[4]-2;
  next[6] = comb[6];
  next[7] = comb[7];
}

unsigned C_turn_L2(uint8_t *comb, uint8_t *next) {
  next[0] = comb[5];
  next[1] = comb[4];
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[1];
  next[5] = comb[0];
  next[6] = comb[6];
  next[7] = comb[7];
}

unsigned C_turn_Lprime(uint8_t *comb, uint8_t *next) {
  next[0] = (comb[4]+1)%3 ? comb[4]+1 : comb[4]-2;
  next[1] = comb[0]%3 ? comb[0]-1 : comb[0]+2;
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[5]%3 ? comb[5]-1 : comb[5]+2;
  next[5] = (comb[1]+1)%3 ? comb[1]+1 : comb[1]-2;
  next[6] = comb[6];
  next[7] = comb[7];
}

unsigned C_turn_B(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = (comb[2]+1)%3 ? comb[2]+1 : comb[2]-2;
  next[2] = comb[6]%3 ? comb[6]-1 : comb[6]+2;
  next[3] = comb[3];
  next[4] = comb[4];
  next[5] = comb[1]%3 ? comb[1]-1 : comb[1]+2;
  next[6] = (comb[5]+1)%3 ? comb[5]+1 : comb[5]-2;
  next[7] = comb[7];
}

unsigned C_turn_B2(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[6];
  next[2] = comb[5];
  next[3] = comb[3];
  next[4] = comb[4];
  next[5] = comb[2];
  next[6] = comb[1];
  next[7] = comb[7];
}

unsigned C_turn_Bprime(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = (comb[5]+1)%3 ? comb[5]+1 : comb[5]-2;
  next[2] = comb[1]%3 ? comb[1]-1 : comb[1]+2;
  next[3] = comb[3];
  next[4] = comb[4];
  next[5] = comb[6]%3 ? comb[6]-1 : comb[6]+2;
  next[6] = (comb[2]+1)%3 ? comb[2]+1 : comb[2]-2;
  next[7] = comb[7];
}

unsigned C_turn_R(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = (comb[3]+1)%3 ? comb[3]+1 : comb[3]-2;
  next[3] = comb[7]%3 ? comb[7]-1 : comb[7]+2;
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[2]%3 ? comb[2]-1 : comb[2]+2;
  next[7] = (comb[6]+1)%3 ? comb[6]+1 : comb[6]-2;
}

unsigned C_turn_R2(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[7];
  next[3] = comb[6];
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[3];
  next[7] = comb[2];
}

unsigned C_turn_Rprime(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = (comb[6]+1)%3 ? comb[6]+1 : comb[6]-2;
  next[3] = comb[2]%3 ? comb[2]-1 : comb[2]+2;
  next[4] = comb[4];
  next[5] = comb[5];
  next[6] = comb[7]%3 ? comb[7]-1 : comb[7]+2;
  next[7] = (comb[3]+1)%3 ? comb[3]+1 : comb[3]-2;
}

unsigned C_turn_D(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[5];
  next[5] = comb[6];
  next[6] = comb[7];
  next[7] = comb[4];
}

unsigned C_turn_D2(uint8_t *comb, uint8_t *next) {
  next[0] = comb[0];
  next[1] = comb[1];
  next[2] = comb[2];
  next[3] = comb[3];
  next[4] = comb[6];
  next[5] = comb[7];
  next[6] = comb[4];
  next[7] = comb[5];
}

unsigned C_turn_Dprime(uint8_t *comb, uint8_t *next) {
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
  if ((next[0] = comb[3]) > 11 && 
      (next[1] = comb[0]) > 11 &&
      (next[2] = comb[1]) > 11 &&
      (next[3] = comb[2]) > 11)
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
  if ((next[0] = comb[2]) > 11 && 
      (next[1] = comb[3]) > 11 &&
      (next[2] = comb[0]) > 11 &&
      (next[3] = comb[1]) > 11)
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
  if ((next[0] = comb[1]) > 11 && 
      (next[1] = comb[2]) > 11 &&
      (next[2] = comb[3]) > 11 &&
      (next[3] = comb[0]) > 11)
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
  if ((next[7] = comb[0]) > 11 &&
      (next[8] = comb[7]) > 11 &&
      (next[0] = comb[4]%2 ? comb[4]-1 : comb[4]+1) > 11 &&
      (next[4] = comb[8]%2 ? comb[8]-1 : comb[8]+1) > 11)
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
  if ((next[0] = comb[8]) > 11 &&
      (next[8] = comb[0]) > 11 &&
      (next[4] = comb[7]%2 ? comb[7]-1 : comb[7]+1) > 11 &&
      (next[7] = comb[4]%2 ? comb[4]-1 : comb[4]+1) > 11)
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
  if ((next[0] = comb[7]) > 11 &&
      (next[7] = comb[8]) > 11 &&
      (next[4] = comb[0]%2 ? comb[0]-1 : comb[0]+1) > 11 &&
      (next[8] = comb[4]%2 ? comb[4]-1 : comb[4]+1) > 11)
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
  if ((next[4] = comb[1]) > 11 &&
      (next[9] = comb[4]) > 11 &&
      (next[1] = comb[5]%2 ? comb[5]-1 : comb[5]+1) > 11 &&
      (next[5] = comb[9]%2 ? comb[9]-1 : comb[9]+1) > 11)
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
  if ((next[1] = comb[9]) > 11 &&
      (next[9] = comb[1]) > 11 &&
      (next[4] = comb[5]%2 ? comb[5]-1 : comb[5]+1) > 11 &&
      (next[5] = comb[4]%2 ? comb[4]-1 : comb[4]+1) > 11)
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
  if ((next[1] = comb[4]) > 11 &&
      (next[4] = comb[9]) > 11 &&
      (next[5] = comb[1]%2 ? comb[1]-1 : comb[1]+1) > 11 &&
      (next[9] = comb[5]%2 ? comb[5]-1 : comb[5]+1) > 11)
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
  if ((next[5] = comb[2]) > 11 &&
      (next[10] = comb[5]) > 11 &&
      (next[2] = comb[6]%2 ? comb[6]-1 : comb[6]+1) > 11 &&
      (next[6] = comb[10]%2 ? comb[10]-1 : comb[10]+1) > 11)
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
  if ((next[2] = comb[10]) > 11 &&
      (next[10] = comb[2]) > 11 &&
      (next[5] = comb[6]%2 ? comb[6]-1 : comb[6]+1) > 11 &&
      (next[6] = comb[5]%2 ? comb[5]-1 : comb[5]+1) > 11)
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
  if ((next[2] = comb[5]) > 11 &&
      (next[5] = comb[10]) > 11 &&
      (next[6] = comb[2]%2 ? comb[2]-1 : comb[2]+1) > 11 &&
      (next[10] = comb[6]%2 ? comb[6]-1 : comb[6]+1) > 11)
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
  if ((next[6] = comb[3]) > 11 &&
      (next[11] = comb[6]) > 11 &&
      (next[3] = comb[7]%2 ? comb[7]-1 : comb[7]+1) > 11 &&
      (next[7] = comb[11]%2 ? comb[11]-1 : comb[11]+1) > 11)
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
  if ((next[3] = comb[11]) > 11 &&
      (next[11] = comb[3]) > 11 &&
      (next[6] = comb[7]%2 ? comb[7]-1 : comb[7]+1) > 11 &&
      (next[7] = comb[6]%2 ? comb[6]-1 : comb[6]+1) > 11)
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
  if ((next[3] = comb[6]) > 11 &&
      (next[6] = comb[11]) > 11 &&
      (next[7] = comb[3]%2 ? comb[3]-1 : comb[3]+1) > 11 &&
      (next[11] = comb[7]%2 ? comb[7]-1 : comb[7]+1) > 11)
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
  if ((next[8] = comb[9]) > 11 &&
      (next[9] = comb[10]) > 11 &&
      (next[10] = comb[11]) > 11 &&
      (next[11] = comb[8]) > 11)
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
  if ((next[8] = comb[10]) > 11 &&
      (next[9] = comb[11]) > 11 &&
      (next[10] = comb[8]) > 11 &&
      (next[11] = comb[9]) > 11)
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
  if ((next[8] = comb[11]) > 11 &&
      (next[9] = comb[8]) > 11 &&
      (next[10] = comb[9]) > 11 &&
      (next[11] = comb[10]) > 11)
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
  moves[0] = C_turn_U;
  moves[1] = C_turn_U2;
  moves[2] = C_turn_Uprime;
  moves[3] = C_turn_F;
  moves[4] = C_turn_F2;
  moves[5] = C_turn_Fprime;
  moves[6] = C_turn_L;
  moves[7] = C_turn_L2;
  moves[8] = C_turn_Lprime;
  moves[9] = C_turn_B;
  moves[10] = C_turn_B2;
  moves[11] = C_turn_Bprime;
  moves[12] = C_turn_R;
  moves[13] = C_turn_R2;
  moves[14] = C_turn_Rprime;
  moves[15] = C_turn_D;
  moves[16] = C_turn_D2;
  moves[17] = C_turn_Dprime;
  moves[18] = E_turn_U;
  moves[19] = E_turn_U2;
  moves[20] = E_turn_Uprime;
  moves[21] = E_turn_F;
  moves[22] = E_turn_F2;
  moves[23] = E_turn_Fprime;
  moves[24] = E_turn_L;
  moves[25] = E_turn_L2;
  moves[26] = E_turn_Lprime;
  moves[27] = E_turn_B;
  moves[28] = E_turn_B2;
  moves[29] = E_turn_Bprime;
  moves[30] = E_turn_R;
  moves[31] = E_turn_R2;
  moves[32] = E_turn_Rprime;
  moves[33] = E_turn_D;
  moves[34] = E_turn_D2;
  moves[35] = E_turn_Dprime;
}

unsigned (*moves[36])(uint8_t*, uint8_t*);
