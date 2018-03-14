#include "cdatabase.h"
#include "edatabase.h"

static unsigned fill_amount = 0;
static double fill_percent = 0.0;

void update_percent(void);
void display_percent(void);

void update_percent() {
  fill_percent += 0.01;
  printf("\rDatabase generation %-.0lf%%", fill_percent*100);
  fflush(stdout);
}

void display_percent() {
  printf("\rDatabase generation %-.0lf%%", fill_percent*100);
  fflush(stdout);
}
