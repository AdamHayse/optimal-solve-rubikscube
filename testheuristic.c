/*
 *  Copy and paste or type a scramble algorithm to
 *  see how many moves are required to solve the corners.
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

static uint8_t database[44089920];

int main() {

  // Load corners database.
  int fd = open("corners.patdb", O_RDONLY);
  read(fd, database, 44089920);
  close(fd);

  // Get scramble algorithm and execute it on solved combination.
  char scramble[256];
  while (1) {

    // Get scramble algorithm from user.
    fgets(scramble, 256, stdin);

    // Initialize corners as solved combination.
    int i;
    uint8_t comb[128][8];
    for (i=0; i<8; i++)
      comb[0][i] = 3*i;

    // Tokenize user input and perform moves.
    char* token = strtok(scramble, " \n()[]\t{}");
    i=0;
    while (token) {
      if (strcmp(token, "U") == 0) {
        C_turn_U(comb[i], comb[i+1]);}
      else if (strcmp(token, "U2") == 0) {
        C_turn_U2(comb[i], comb[i+1]);}
      else if (strcmp(token, "U'") == 0) {
        C_turn_Uprime(comb[i], comb[i+1]);}
      else if (strcmp(token, "F") == 0) {
        C_turn_F(comb[i], comb[i+1]);}
      else if (strcmp(token, "F2") == 0) {
        C_turn_F2(comb[i], comb[i+1]);}
      else if (strcmp(token, "F'") == 0) {
        C_turn_Fprime(comb[i], comb[i+1]);}
      else if (strcmp(token, "L") == 0) {
        C_turn_L(comb[i], comb[i+1]);}
      else if (strcmp(token, "L2") == 0) {
        C_turn_L2(comb[i], comb[i+1]);}
      else if (strcmp(token, "L'") == 0) {
        C_turn_Lprime(comb[i], comb[i+1]);}
      else if (strcmp(token, "B") == 0) {
        C_turn_B(comb[i], comb[i+1]);}
      else if (strcmp(token, "B2") == 0) {
        C_turn_B2(comb[i], comb[i+1]);}
      else if (strcmp(token, "B'") == 0) {
        C_turn_Bprime(comb[i], comb[i+1]);}
      else if (strcmp(token, "R") == 0) {
        C_turn_R(comb[i], comb[i+1]);}
      else if (strcmp(token, "R2") == 0) {
        C_turn_R2(comb[i], comb[i+1]);}
      else if (strcmp(token, "R'") == 0) {
        C_turn_Rprime(comb[i], comb[i+1]);}
      else if (strcmp(token, "D") == 0) {
        C_turn_D(comb[i], comb[i+1]);}
      else if (strcmp(token, "D2") == 0) {
        C_turn_D2(comb[i], comb[i+1]);}
      else if (strcmp(token, "D'") == 0) {
        C_turn_Dprime(comb[i], comb[i+1]);}
      i++;
      token = strtok(NULL, " \n()[]\t{}");
    }

    // Print resulting combination.
    /*
    int k;
    for (k=0; k<8; k++)
      printf("%u, ", comb[i][k]);
    */

    // Lookup minimum moves from loaded pattern database.
    printf("%u moves to solve corners.\n", C_path_length(comb[i], database));
  }
}






