#ifndef DATABASE_H
#define DATABASE_H

#include <stdatomic.h>

//#define SSIZE_MAX 1048576

#ifndef O_BINARY
  #define O_BINARY 0
#endif

// Update percent completion of database fill.
void update_percent(void);

extern atomic_ullong fill_amount;
extern double fill_percent;

#endif
