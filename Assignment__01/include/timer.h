#ifndef TIMER_H
#define TIMER_H

#include <time.h>

// Time structure
typedef struct {
    clock_t start;
    clock_t end;
} timer_t;

// Start Timer
void timer_start(timer_t *t);

// Stop Timer
void timer_stop(timer_t *t);

// Time Elapsed
double elapsed_ms(const timer_t *t);
double elapsed_seconds(const timer_t *t);

#endif
