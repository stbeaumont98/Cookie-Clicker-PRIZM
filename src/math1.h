#ifndef MATH1_H_
#define MATH1_H_

#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )

unsigned int random(void);
unsigned int srandom(int seed);

double exp(double x);
double powInt(double x, int n);
double lnFor0To2(double x);
double ln(double x);
double pow1(double x, double y);
long factorial(int n);
int64_t round2(double num);
float floor2(double x);
float ceil2(double x);
double ten_pow(int32_t n);

#endif