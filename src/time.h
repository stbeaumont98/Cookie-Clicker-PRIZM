#ifndef TIME_H_
#define TIME_H_

// essentially midnight
#define MAX_TICKS 11059200

int32_t ticks(double seconds);
double secs(int32_t ticks);

uint32_t elapsed_ticks(int32_t *old_ticks);

#endif