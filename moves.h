#ifndef MOVES_H
#define MOVES_H

#include <stdint.h>


// Functions for all moves that can be performed.
void C_turn_U(uint8_t *comb, uint8_t *next);
void C_turn_U2(uint8_t *comb, uint8_t *next);
void C_turn_Uprime(uint8_t *comb, uint8_t *next);
void C_turn_F(uint8_t *comb, uint8_t *next);
void C_turn_F2(uint8_t *comb, uint8_t *next);
void C_turn_Fprime(uint8_t *comb, uint8_t *next);
void C_turn_L(uint8_t *comb, uint8_t *next);
void C_turn_L2(uint8_t *comb, uint8_t *next);
void C_turn_Lprime(uint8_t *comb, uint8_t *next);
void C_turn_B(uint8_t *comb, uint8_t *next);
void C_turn_B2(uint8_t *comb, uint8_t *next);
void C_turn_Bprime(uint8_t *comb, uint8_t *next);
void C_turn_R(uint8_t *comb, uint8_t *next);
void C_turn_R2(uint8_t *comb, uint8_t *next);
void C_turn_Rprime(uint8_t *comb, uint8_t *next);
void C_turn_D(uint8_t *comb, uint8_t *next);
void C_turn_D2(uint8_t *comb, uint8_t *next);
void C_turn_Dprime(uint8_t *comb, uint8_t *next);
unsigned E_turn_U(uint8_t *comb, uint8_t *next);
unsigned E_turn_U2(uint8_t *comb, uint8_t *next);
unsigned E_turn_Uprime(uint8_t *comb, uint8_t *next);
unsigned E_turn_F(uint8_t *comb, uint8_t *next);
unsigned E_turn_F2(uint8_t *comb, uint8_t *next);
unsigned E_turn_Fprime(uint8_t *comb, uint8_t *next);
unsigned E_turn_L(uint8_t *comb, uint8_t *next);
unsigned E_turn_L2(uint8_t *comb, uint8_t *next);
unsigned E_turn_Lprime(uint8_t *comb, uint8_t *next);
unsigned E_turn_B(uint8_t *comb, uint8_t *next);
unsigned E_turn_B2(uint8_t *comb, uint8_t *next);
unsigned E_turn_Bprime(uint8_t *comb, uint8_t *next);
unsigned E_turn_R(uint8_t *comb, uint8_t *next);
unsigned E_turn_R2(uint8_t *comb, uint8_t *next);
unsigned E_turn_Rprime(uint8_t *comb, uint8_t *next);
unsigned E_turn_D(uint8_t *comb, uint8_t *next);
unsigned E_turn_D2(uint8_t *comb, uint8_t *next);
unsigned E_turn_Dprime(uint8_t *comb, uint8_t *next);

// Assign pointers to all functions to static array moves.
void initialize_turns(void);

extern void (*movesC[18])(uint8_t*, uint8_t*);
extern unsigned (*movesE[18])(uint8_t*, uint8_t*);

#endif
