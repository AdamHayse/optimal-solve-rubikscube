#include <stdio.h>
#include "database.h"

atomic_ullong fill_amount = 0;
double fill_percent = -.00001;

void update_percent(void) {
  fill_percent += .00001;
  printf("\rDatabase generation %-.3lf%%", fill_percent*100);
  fflush(stdout);
}
