#ifndef MATH1_H_
#define MATH1_H_

#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )

unsigned int random(void);
unsigned int srandom(int seed);

double pow_int(double x, int n);
int64_t round2(double num);
double floor2(double x);
double ceil2(double x);
double ten_pow(int32_t n);

#endif