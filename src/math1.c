#include <stdint.h>
#include "math1.h"

static unsigned int lastrandom=0x12345678;
unsigned int random(void) {
   return srandom(0);
}

unsigned int srandom(int seed){
    if (seed) lastrandom=seed;
    lastrandom = ( 0x41C64E6D*lastrandom ) + 0x3039;
    return ( lastrandom >> 16 );
}

double exp(double x) { 
   int i=2; 
   long long fact=2; 
   double resC=1, resP=0; 
   while (resC!=resP) { 
      resP=resC; 
      resC+=1./(double)fact; 
      fact*=++i; 
   } 
   return resC; 
}

double powInt(double x, int n) { 
   if (n<0) return 1./powInt(x,-n); 
   double res=1; 
   int i=0; 
   for (i=0;i<n;i++) res*=x; 
   return res; 
} 

double lnFor0To2(double x) { 
   double y=x-1; 
   int i=2; 
   double resC=y, resP=0; 
   while (resC!=resP) { 
      resP=resC; 
      resC+=(i%2?1:-1)*powInt(x,i)/i; 
   } 
   return resC; 
} 

double ln(double x) { 
   if (0 < x && x <= 2)
      return lnFor0To2(x); 
   else 
      return 1 + lnFor0To2(x / exp(1)); 
}

double pow1(double x, double y) { 
   return exp(y*ln(x)); 
}

long factorial(int n)
{
	int c;
	long result = 1;
	
	for (c = 1; c <= n; c++)
		result = result * c;
	
	return result;
}

int32_t round2(double num) {
   return num < 0 ? num - 0.5 : num + 0.5; 
} 

float floor2(double x) { 
   return ((int) x) - (x < 0); 
}

float ceil2(double x) { 
   return ((int) x) + (x < 0); 
}