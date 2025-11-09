#include "fxcg\rtc.h"
#include "stdint.h"

#include "time.h"

// Convert seconds to ticks.
int32_t ticks(double seconds) {
    return (int32_t) (seconds * 128);
}

// Convert ticks to seconds.
double secs(int32_t ticks) {
    return (double) ticks / 128.;
}

// Returns the number of ticks that have elapsed since the provided timestamp.
uint32_t elapsed_ticks(int32_t *old_ticks) {
    int32_t ticks = RTC_GetTicks();
    uint32_t elapsed;
    
    // account for ticks resetting once a day
	if (ticks < *old_ticks)
		elapsed = (MAX_TICKS - *old_ticks) + ticks;
	else
		elapsed = ticks - *old_ticks;

	*old_ticks = ticks;

    return elapsed;
}