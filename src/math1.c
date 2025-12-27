#include <stdint.h>
#include <stdlib.h>
#include "math1.h"

static unsigned int lastrandom = 0x12345678;

unsigned int random(void) {
    return srandom(0);
}

unsigned int srandom(int seed){
    if (seed) lastrandom = seed;
    lastrandom = (0x41C64E6D * lastrandom) + 0x3039;
    return (lastrandom >> 16);
}

// trunc() pulled from
// https://github.com/migueldeicaza/mono-wasm-libc/blob/master/src/math/trunc.c

double trunc(double x) {
    union {double f; uint64_t i;} u = {x};
    int e = (int) (u.i >> 52 & 0x7ff) - 0x3ff + 12;
    uint64_t m;

    if (e >= 52 + 12)
        return x;
    if (e < 12)
        e = 1;
    m = -1ULL >> e;
    if ((u.i & m) == 0)
        return x;

    u.i &= ~m;
    return u.f;
}

double pow_int(double x, int n) {
    if (n < 0) return 1. / pow_int(x, -n);
    double res = 1.;
    for (int i = 0; i < n; i++) res *= x;
    return res;
}

int64_t round2(double num) {
    return num < 0 ? (int64_t) (num - 0.5) : (int64_t) (num + 0.5);
}

double floor2(double x) {
    double r = trunc(x);
    return r - (r != x && x < 0);
}

double ceil2(double x) {
    double r = trunc(x);
    return r + (r != x && x > 0);
}

double ten_pow(int32_t n) {
    double x = 10.;
    double pow = 1.;

    for (int i = 0; i < abs(n); i++) {
        if (n < 0)
            pow /= x;
        else
            pow *= x;
    }

    return pow;
}