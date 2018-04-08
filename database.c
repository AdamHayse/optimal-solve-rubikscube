#include <stdio.h>
#include "database.h"

unsigned fill_amount = 0;
double fill_percent = -0.01;

void update_percent() {
  fill_percent += 0.01;
  printf("\rDatabase generation %-.0lf%%", fill_percent*100);
  fflush(stdout);
}
