#ifndef TIME_H_
#define TIME_H_

// essentially midnight
#define MAX_TICKS 11059200

// R*CNT definitions provided by gbl08ma's utilities

#define RYRCNT  (unsigned short*) 0xA413FECE
#define RMONCNT (unsigned char*) 0xA413FECC
#define RDAYCNT (unsigned char*) 0xA413FECA
 
#define RHRCNT  (unsigned char*) 0xA413FEC6
#define RMINCNT (unsigned char*) 0xA413FEC4
#define RSECCNT (unsigned char*) 0xA413FEC2

#define SECONDS_IN_DAY 86400.

extern const double days_in_month[12];

int32_t ticks(double seconds);
double secs(int32_t ticks);

uint32_t elapsed_ticks(int32_t *old_ticks);

double get_timestamp();

#endif