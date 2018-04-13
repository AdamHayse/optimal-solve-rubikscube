/*
 * This file contains precomputed values for mathematical
 * functions within the basic operation of the search algorithm.
 */

#include "mymath.h"

// Power with O(1) time efficiency.
const unsigned two_to_the[9] = {1, 2, 4, 8, 16, 32, 64, 128, 256};
const unsigned three_to_the[8] = {1, 3, 9, 27, 81, 243, 729, 2187};

// Factorial with O(1) time efficiency.
const unsigned fact[13] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320,
                            362880, 3628800, 39916800, 479001600};
