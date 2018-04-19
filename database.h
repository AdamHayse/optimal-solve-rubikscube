#ifndef DATABASE_H
#define DATABASE_H

#define SSIZE_MAX 1048576

// Update percent completion of database fill.
void update_percent(void);

extern unsigned fill_amount;
extern double fill_percent;

#endif
