#include "fxcg\rtc.h"
#include "stdint.h"

#include "time.h"

const double days_in_month[12] = {31., 28., 31., 30., 31., 30., 31., 31., 30., 31., 30., 31.};

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

// bcd_to_2digit and get_current_* functions provided by gbl08ma's utilities

unsigned int bcd_to_2digit(unsigned char* bcd) {
    return ((((*(bcd))&0xf0)>>4)*10) + ((*(bcd))&0x0f);
}

int get_current_year() {
    return ((*RYRCNT >> 12) & 0b1111)*1000 + ((*RYRCNT >> 8) & 0b1111)*100 +
        ((*RYRCNT >> 4) & 0b1111)*10 + (*RYRCNT & 0b1111);
}
int get_current_month() {
    return ((*RMONCNT & 0b10000)>>4)*10 + (*RMONCNT & 0b1111);
}
int get_current_day() {
    return ((*RDAYCNT >> 4) & 0b11)*10 + (*RDAYCNT & 0b1111);
}
int get_current_hour() {
    return bcd_to_2digit(RHRCNT); 
}
int get_current_minute() {
    return bcd_to_2digit(RMINCNT);
}
int get_current_second() {
    return bcd_to_2digit(RSECCNT);
}

double date_to_seconds(int year, int month, int day, int hour, int min, int sec) {
    double total = (double) year * 31536000.;
    for (int i = 0; i < month - 1; i++) {
        if (i == 1 && (year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0)) {
            total += (29. * SECONDS_IN_DAY);
        } else
            total += (days_in_month[i] * SECONDS_IN_DAY);
    }
    total += ((double) (day - 1) * SECONDS_IN_DAY);
    total += (double) hour * 3600.;
    total += (double) min * 60.;
    total += (double) sec;

    return total;
}

double get_timestamp() {
    return date_to_seconds(get_current_year(), get_current_month(), get_current_day(), get_current_hour(), get_current_minute(), get_current_second());
}