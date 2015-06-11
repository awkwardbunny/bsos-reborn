#ifndef TIMER_H
#define TIMER_H

void timer_install();
void timer_phase(unsigned int hz);
void timer_wait(unsigned int ticks);

#endif