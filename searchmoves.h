#ifndef SEARCHMOVES_H
#define SEARCHMOVES_H

#include "IDAstar.h"

// Functions for all moves that can be performed.
void turn_U(NODE *prev, NODE *next);
void turn_U2(NODE *prev, NODE *next);
void turn_Uprime(NODE *prev, NODE *next);
void turn_F(NODE *prev, NODE *next);
void turn_F2(NODE *prev, NODE *next);
void turn_Fprime(NODE *prev, NODE *next);
void turn_L(NODE *prev, NODE *next);
void turn_L2(NODE *prev, NODE *next);
void turn_Lprime(NODE *prev, NODE *next);
void turn_B(NODE *prev, NODE *next);
void turn_B2(NODE *prev, NODE *next);
void turn_Bprime(NODE *prev, NODE *next);
void turn_R(NODE *prev, NODE *next);
void turn_R2(NODE *prev, NODE *next);
void turn_Rprime(NODE *prev, NODE *next);
void turn_D(NODE *prev, NODE *next);
void turn_D2(NODE *prev, NODE *next);
void turn_Dprime(NODE *prev, NODE *next);

// Assign pointers to all functions to static array moves.
void initialize_turns(void);

extern void (*moves[18])(NODE*, NODE*);

#endif
