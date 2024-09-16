#include "fxcg\display.h"
#include "fxcg\keyboard.h"
#include "fxcg\rtc.h"
#include "fxcg\file.h"
#include "keyboard_syscalls.h"
#include "string.h"
#include "stdint.h"
#include "stdlib.h"
#include "ctype.h"
#include "math.h"
#include "CookieSprites.h"


#define PATH "\\\\fls0\\Cookies.sav"


#define abs1(x) (x < 0 ? -x : x)

#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )

#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )

#define M_PI 3.14159265358979323846264338327950288419716939932795502884

int round1(double number)
{
    return (number >= 0) ? (int)(number + 0.5) : (int)(number - 0.5);
}

static const float costbl[360]={1,0.99984769515639,0.9993908270191,0.99862953475457,0.99756405025982,0.99619469809175,0.99452189536827,0.99254615164132,0.99026806874157,0.98768834059514,0.98480775301221,0.98162718344766,0.97814760073381,0.97437006478524,0.970295726276,0.96592582628907,0.96126169593832,0.95630475596304,0.95105651629515,0.94551857559932,0.93969262078591,0.9335804264972,0.92718385456679,0.92050485345244,0.9135454576426,0.90630778703665,0.89879404629917,0.89100652418837,0.88294759285893,0.8746197071394,0.86602540378444,0.85716730070211,0.84804809615643,0.83867056794542,0.82903757255504,0.81915204428899,0.80901699437495,0.79863551004729,0.78801075360672,0.77714596145697,0.76604444311898,0.75470958022277,0.74314482547739,0.73135370161917,0.71933980033865,0.70710678118655,0.694658370459,0.6819983600625,0.66913060635886,0.65605902899051,0.64278760968654,0.62932039104984,0.61566147532566,0.60181502315205,0.58778525229247,0.57357643635105,0.55919290347075,0.54463903501503,0.5299192642332,0.51503807491005,0.5,0.48480962024634,0.46947156278589,0.45399049973955,0.43837114678908,0.4226182617407,0.4067366430758,0.39073112848927,0.37460659341591,0.3583679495453,0.34202014332567,0.32556815445716,0.30901699437495,0.29237170472274,0.275637355817,0.25881904510252,0.24192189559967,0.22495105434386,0.20791169081776,0.19080899537654,0.17364817766693,0.15643446504023,0.13917310096007,0.12186934340515,0.10452846326765,0.087155742747658,0.069756473744125,0.052335956242944,0.034899496702501,0.017452406437283,6.1230317691119e-17,-0.017452406437283,-0.034899496702501,-0.052335956242944,-0.069756473744125,-0.087155742747658,-0.10452846326765,-0.12186934340515,-0.13917310096007,-0.15643446504023,-0.17364817766693,-0.19080899537654,-0.20791169081776,-0.22495105434386,-0.24192189559967,-0.25881904510252,-0.275637355817,-0.29237170472274,-0.30901699437495,-0.32556815445716,-0.34202014332567,-0.3583679495453,-0.37460659341591,-0.39073112848927,-0.4067366430758,-0.4226182617407,-0.43837114678908,-0.45399049973955,-0.46947156278589,-0.48480962024634,-0.5,-0.51503807491005,-0.5299192642332,-0.54463903501503,-0.55919290347075,-0.57357643635105,-0.58778525229247,-0.60181502315205,-0.61566147532566,-0.62932039104984,-0.64278760968654,-0.65605902899051,-0.66913060635886,-0.6819983600625,-0.694658370459,-0.70710678118655,-0.71933980033865,-0.73135370161917,-0.74314482547739,-0.75470958022277,-0.76604444311898,-0.77714596145697,-0.78801075360672,-0.79863551004729,-0.80901699437495,-0.81915204428899,-0.82903757255504,-0.83867056794542,-0.84804809615643,-0.85716730070211,-0.86602540378444,-0.8746197071394,-0.88294759285893,-0.89100652418837,-0.89879404629917,-0.90630778703665,-0.9135454576426,-0.92050485345244,-0.92718385456679,-0.9335804264972,-0.93969262078591,-0.94551857559932,-0.95105651629515,-0.95630475596304,-0.96126169593832,-0.96592582628907,-0.970295726276,-0.97437006478524,-0.97814760073381,-0.98162718344766,-0.98480775301221,-0.98768834059514,-0.99026806874157,-0.99254615164132,-0.99452189536827,-0.99619469809175,-0.99756405025982,-0.99862953475457,-0.9993908270191,-0.99984769515639,-1,-0.99984769515639,-0.9993908270191,-0.99862953475457,-0.99756405025982,-0.99619469809175,-0.99452189536827,-0.99254615164132,-0.99026806874157,-0.98768834059514,-0.98480775301221,-0.98162718344766,-0.97814760073381,-0.97437006478524,-0.970295726276,-0.96592582628907,-0.96126169593832,-0.95630475596304,-0.95105651629515,-0.94551857559932,-0.93969262078591,-0.9335804264972,-0.92718385456679,-0.92050485345244,-0.9135454576426,-0.90630778703665,-0.89879404629917,-0.89100652418837,-0.88294759285893,-0.8746197071394,-0.86602540378444,-0.85716730070211,-0.84804809615643,-0.83867056794542,-0.82903757255504,-0.81915204428899,-0.80901699437495,-0.79863551004729,-0.78801075360672,-0.77714596145697,-0.76604444311898,-0.75470958022277,-0.74314482547739,-0.73135370161917,-0.71933980033865,-0.70710678118655,-0.694658370459,-0.6819983600625,-0.66913060635886,-0.65605902899051,-0.64278760968654,-0.62932039104984,-0.61566147532566,-0.60181502315205,-0.58778525229247,-0.57357643635105,-0.55919290347075,-0.54463903501503,-0.52991926423321,-0.51503807491005,-0.5,-0.48480962024634,-0.46947156278589,-0.45399049973955,-0.43837114678908,-0.4226182617407,-0.4067366430758,-0.39073112848927,-0.37460659341591,-0.3583679495453,-0.34202014332567,-0.32556815445716,-0.30901699437495,-0.29237170472274,-0.275637355817,-0.25881904510252,-0.24192189559967,-0.22495105434387,-0.20791169081776,-0.19080899537655,-0.17364817766693,-0.15643446504023,-0.13917310096006,-0.12186934340515,-0.10452846326765,-0.087155742747658,-0.069756473744126,-0.052335956242944,-0.034899496702502,-0.017452406437283,-1.8369095307336e-16,0.017452406437283,0.034899496702501,0.052335956242944,0.069756473744125,0.087155742747658,0.10452846326765,0.12186934340515,0.13917310096007,0.15643446504023,0.17364817766693,0.19080899537654,0.20791169081776,0.22495105434386,0.24192189559967,0.25881904510252,0.275637355817,0.29237170472274,0.30901699437495,0.32556815445716,0.34202014332567,0.3583679495453,0.37460659341591,0.39073112848927,0.4067366430758,0.4226182617407,0.43837114678908,0.45399049973955,0.46947156278589,0.48480962024634,0.5,0.51503807491005,0.5299192642332,0.54463903501503,0.55919290347075,0.57357643635105,0.58778525229247,0.60181502315205,0.61566147532566,0.62932039104984,0.64278760968654,0.65605902899051,0.66913060635886,0.6819983600625,0.694658370459,0.70710678118655,0.71933980033865,0.73135370161917,0.74314482547739,0.75470958022277,0.76604444311898,0.77714596145697,0.78801075360672,0.79863551004729,0.80901699437495,0.81915204428899,0.82903757255504,0.83867056794542,0.84804809615643,0.85716730070211,0.86602540378444,0.8746197071394,0.88294759285893,0.89100652418837,0.89879404629917,0.90630778703665,0.9135454576426,0.92050485345244,0.92718385456679,0.9335804264972,0.93969262078591,0.94551857559932,0.95105651629515,0.95630475596304,0.96126169593832,0.96592582628907,0.970295726276,0.97437006478524,0.97814760073381,0.98162718344766,0.98480775301221,0.98768834059514,0.99026806874157,0.99254615164132,0.99452189536827,0.99619469809175,0.99756405025982,0.99862953475457,0.9993908270191,0.99984769515639};
static const float sintbl[360]={0,0.017452406437284,0.034899496702501,0.052335956242944,0.069756473744125,0.087155742747658,0.10452846326765,0.12186934340515,0.13917310096007,0.15643446504023,0.17364817766693,0.19080899537654,0.20791169081776,0.22495105434387,0.24192189559967,0.25881904510252,0.275637355817,0.29237170472274,0.30901699437495,0.32556815445716,0.34202014332567,0.3583679495453,0.37460659341591,0.39073112848927,0.4067366430758,0.4226182617407,0.43837114678908,0.45399049973955,0.46947156278589,0.48480962024634,0.5,0.51503807491005,0.5299192642332,0.54463903501503,0.55919290347075,0.57357643635105,0.58778525229247,0.60181502315205,0.61566147532566,0.62932039104984,0.64278760968654,0.65605902899051,0.66913060635886,0.6819983600625,0.694658370459,0.70710678118655,0.71933980033865,0.73135370161917,0.74314482547739,0.75470958022277,0.76604444311898,0.77714596145697,0.78801075360672,0.79863551004729,0.80901699437495,0.81915204428899,0.82903757255504,0.83867056794542,0.84804809615643,0.85716730070211,0.86602540378444,0.8746197071394,0.88294759285893,0.89100652418837,0.89879404629917,0.90630778703665,0.9135454576426,0.92050485345244,0.92718385456679,0.9335804264972,0.93969262078591,0.94551857559932,0.95105651629515,0.95630475596304,0.96126169593832,0.96592582628907,0.970295726276,0.97437006478524,0.97814760073381,0.98162718344766,0.98480775301221,0.98768834059514,0.99026806874157,0.99254615164132,0.99452189536827,0.99619469809175,0.99756405025982,0.99862953475457,0.9993908270191,0.99984769515639,1,0.99984769515639,0.9993908270191,0.99862953475457,0.99756405025982,0.99619469809175,0.99452189536827,0.99254615164132,0.99026806874157,0.98768834059514,0.98480775301221,0.98162718344766,0.97814760073381,0.97437006478524,0.970295726276,0.96592582628907,0.96126169593832,0.95630475596304,0.95105651629515,0.94551857559932,0.93969262078591,0.9335804264972,0.92718385456679,0.92050485345244,0.9135454576426,0.90630778703665,0.89879404629917,0.89100652418837,0.88294759285893,0.8746197071394,0.86602540378444,0.85716730070211,0.84804809615643,0.83867056794542,0.82903757255504,0.81915204428899,0.80901699437495,0.79863551004729,0.78801075360672,0.77714596145697,0.76604444311898,0.75470958022277,0.74314482547739,0.73135370161917,0.71933980033865,0.70710678118655,0.694658370459,0.6819983600625,0.66913060635886,0.65605902899051,0.64278760968654,0.62932039104984,0.61566147532566,0.60181502315205,0.58778525229247,0.57357643635105,0.55919290347075,0.54463903501503,0.5299192642332,0.51503807491005,0.5,0.48480962024634,0.46947156278589,0.45399049973955,0.43837114678908,0.4226182617407,0.4067366430758,0.39073112848927,0.37460659341591,0.3583679495453,0.34202014332567,0.32556815445716,0.30901699437495,0.29237170472274,0.275637355817,0.25881904510252,0.24192189559967,0.22495105434386,0.20791169081776,0.19080899537654,0.17364817766693,0.15643446504023,0.13917310096007,0.12186934340515,0.10452846326765,0.087155742747659,0.069756473744126,0.052335956242944,0.034899496702501,0.017452406437283,1.2246063538224e-16,-0.017452406437283,-0.034899496702501,-0.052335956242944,-0.069756473744125,-0.087155742747658,-0.10452846326765,-0.12186934340515,-0.13917310096007,-0.15643446504023,-0.17364817766693,-0.19080899537654,-0.20791169081776,-0.22495105434386,-0.24192189559967,-0.25881904510252,-0.275637355817,-0.29237170472274,-0.30901699437495,-0.32556815445716,-0.34202014332567,-0.3583679495453,-0.37460659341591,-0.39073112848927,-0.4067366430758,-0.4226182617407,-0.43837114678908,-0.45399049973955,-0.46947156278589,-0.48480962024634,-0.5,-0.51503807491005,-0.5299192642332,-0.54463903501503,-0.55919290347075,-0.57357643635105,-0.58778525229247,-0.60181502315205,-0.61566147532566,-0.62932039104984,-0.64278760968654,-0.65605902899051,-0.66913060635886,-0.6819983600625,-0.694658370459,-0.70710678118655,-0.71933980033865,-0.73135370161917,-0.74314482547739,-0.75470958022277,-0.76604444311898,-0.77714596145697,-0.78801075360672,-0.79863551004729,-0.80901699437495,-0.81915204428899,-0.82903757255504,-0.83867056794542,-0.84804809615643,-0.85716730070211,-0.86602540378444,-0.8746197071394,-0.88294759285893,-0.89100652418837,-0.89879404629917,-0.90630778703665,-0.9135454576426,-0.92050485345244,-0.92718385456679,-0.9335804264972,-0.93969262078591,-0.94551857559932,-0.95105651629515,-0.95630475596304,-0.96126169593832,-0.96592582628907,-0.970295726276,-0.97437006478524,-0.97814760073381,-0.98162718344766,-0.98480775301221,-0.98768834059514,-0.99026806874157,-0.99254615164132,-0.99452189536827,-0.99619469809175,-0.99756405025982,-0.99862953475457,-0.9993908270191,-0.99984769515639,-1,-0.99984769515639,-0.9993908270191,-0.99862953475457,-0.99756405025982,-0.99619469809175,-0.99452189536827,-0.99254615164132,-0.99026806874157,-0.98768834059514,-0.98480775301221,-0.98162718344766,-0.97814760073381,-0.97437006478524,-0.970295726276,-0.96592582628907,-0.96126169593832,-0.95630475596304,-0.95105651629515,-0.94551857559932,-0.93969262078591,-0.9335804264972,-0.92718385456679,-0.92050485345244,-0.9135454576426,-0.90630778703665,-0.89879404629917,-0.89100652418837,-0.88294759285893,-0.8746197071394,-0.86602540378444,-0.85716730070211,-0.84804809615643,-0.83867056794542,-0.82903757255504,-0.81915204428899,-0.80901699437495,-0.79863551004729,-0.78801075360672,-0.77714596145697,-0.76604444311898,-0.75470958022277,-0.74314482547739,-0.73135370161917,-0.71933980033865,-0.70710678118655,-0.694658370459,-0.6819983600625,-0.66913060635886,-0.65605902899051,-0.64278760968654,-0.62932039104984,-0.61566147532566,-0.60181502315205,-0.58778525229247,-0.57357643635105,-0.55919290347075,-0.54463903501503,-0.52991926423321,-0.51503807491005,-0.5,-0.48480962024634,-0.46947156278589,-0.45399049973955,-0.43837114678908,-0.4226182617407,-0.4067366430758,-0.39073112848927,-0.37460659341591,-0.3583679495453,-0.34202014332567,-0.32556815445716,-0.30901699437495,-0.29237170472274,-0.275637355817,-0.25881904510252,-0.24192189559967,-0.22495105434387,-0.20791169081776,-0.19080899537654,-0.17364817766693,-0.15643446504023,-0.13917310096007,-0.12186934340515,-0.10452846326765,-0.087155742747658,-0.069756473744125,-0.052335956242944,-0.034899496702501,-0.017452406437284};

float angleCorrect(float angle)
{
  while(angle<0)
  {
    angle+=360.0;
  }
  return angle;
}

float cos1(float angle)
{
  angle=angleCorrect(angle);
  int ipart=(int)angle;
  float t1=costbl[ipart%360];
  float t2=costbl[(ipart+1)%360];
  angle=angle-(float)ipart;
  return (t2-t1)*angle+t1;
}

float sin1(float angle)
{
  angle=angleCorrect(angle);
  int ipart=(int)angle;
  float t1=sintbl[ipart%360];
  float t2=sintbl[(ipart+1)%360];
  angle=angle-(float)ipart;
  return (t2-t1)*angle+t1;
}

double sqrt1(double number)
{
const double ACCURACY=0.001;
double lower, upper, guess;

 if (number < 1)
 {
  lower = number;
  upper = 1;
 }
 else
 {
  lower = 1;
  upper = number;
 }

 while ((upper-lower) > ACCURACY)
 {
  guess = (lower + upper)/2;
  if(guess*guess > number)
   upper =guess;
  else
   lower = guess;
 }
 return (lower + upper)/2;

}

unsigned int random(void);
unsigned int srandom(int seed);

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

const double EULER=exp(1); 

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
   if (0<x && x<=2) return lnFor0To2(x); 
   else return 1+lnFor0To2(x/EULER); 
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

unsigned short getpixel(int x, int y) { 
    unsigned short *VRAM = (unsigned short *)0xA8000000; 
    return *(VRAM + (y * LCD_WIDTH_PX) + x); 
}

void plot(int x0, int y0, int color){
   char* VRAM = (char*)0xA8000000;
   VRAM += 2*(y0*LCD_WIDTH_PX + x0);
   *(VRAM++) = (color&0x0000FF00)>>8;
   *(VRAM++) = (color&0x000000FF);
   return;
}

void fillArea(int x, int y, int width, int height, int color) {
   //only use lower two bytes of color
   char* VRAM = (char*)0xA8000000;
   VRAM += 2*(LCD_WIDTH_PX*y + x);
   for(int j=y; j<y+height; j++) {
      for(int i=x; i<x+width;  i++) {
         *(VRAM++) = (color&0x0000FF00)>>8;
         *(VRAM++) = (color&0x000000FF);
      }
      VRAM += 2*(LCD_WIDTH_PX-width);
   }
}

int PRGM_GetKey(){
  unsigned char buffer[12];
  PRGM_GetKey_OS( buffer );
  return ( buffer[1] & 0x0F ) * 10 + ( ( buffer[2] & 0xF0 ) >> 4 );
}

 const unsigned short* keyboard_register = (unsigned short*)0xA44B0000;
 unsigned short lastkey[8];
 unsigned short holdkey[8];

 void keyupdate(void) {
    memcpy(holdkey, lastkey, sizeof(unsigned short)*8);
    memcpy(lastkey, keyboard_register, sizeof(unsigned short)*8);
 }
 int keydownlast(int basic_keycode) {
    int row, col, word, bit;
    row = basic_keycode%10;
    col = basic_keycode/10-1;
    word = row>>1;
    bit = col + 8*(row&1);
    return (0 != (lastkey[word] & 1<<bit));
 }
 int keydownhold(int basic_keycode) {
    int row, col, word, bit;
    row = basic_keycode%10;
    col = basic_keycode/10-1;
    word = row>>1;
    bit = col + 8*(row&1);
    return (0 != (holdkey[word] & 1<<bit));
 }

 int keyPressed(int basic_keycode){ 
      const unsigned short* keyboard_register = (unsigned short*)0xA44B0000; 
      int row, col, word, bit; 
      row = basic_keycode%10; 
      col = basic_keycode/10-1; 
      word = row>>1; 
      bit = col + ((row&1)<<3); 
      return (0 != (keyboard_register[word] & 1<<bit)); 
} 
 
static const short empty[18] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int PrintMiniFix(int x, int y, char *Msg, const int flags, const short color, const short bcolor){
    int i = 0, dx;
    unsigned short width;
    void *p;

   while ( Msg[i] ){
      p = GetMiniGlyphPtr( Msg[i], &width );
      dx = ( 12 - width ) / 2;
      if ( dx > 0 ) {
         PrintMiniGlyph( x, y, (void*)empty, flags, dx, 0, 0, 0, 0, color, bcolor, 0 );
      }else dx = 0;
      PrintMiniGlyph( x+dx, y, p, flags, width, 0, 0, 0, 0, color, bcolor, 0 );
      if ( width+dx < 12 ){
         PrintMiniGlyph( x+width+dx, y, (void*)empty, flags, 12-width-dx, 0, 0, 0, 0, color, bcolor, 0 );
      }
      x += 12;
      i++;
   }
   return x;
}

int PrintMiniFixSquished(int x, int y, char *Msg, const int flags, const short color, const short bcolor){
    int i = 0, dx;
    unsigned short width;
    void *p;

   while ( Msg[i] ){
      p = GetMiniGlyphPtr( Msg[i], &width );
      dx = ( 12 - width ) / 2;
      if ( dx > 0 ) {
         PrintMiniGlyph( x, y, (void*)empty, flags, dx, 0, 0, 0, 0, color, bcolor, 0 );
      }else dx = 0;
      PrintMiniGlyph( x+dx, y, p, flags, width, 0, 0, 0, 0, color, bcolor, 0 );
      if ( width+dx < 12 ){
         PrintMiniGlyph( x+width+dx, y, (void*)empty, flags, 12-width-dx, 0, 0, 0, 0, color, bcolor, 0 );
      }
      x += 9;
      i++;
   }
   return x;
}

void CopySprite(const void* datar, int x, int y, int width, int height) {        color_t*data = (color_t*) datar;
   color_t* VRAM = (color_t*)0xA8000000;
   VRAM += LCD_WIDTH_PX*y + x;
   for(int j=y; j<y+height; j++) {
      for(int i=x; i<x+width; i++) {
        if(j < 216 && i < 384){
         *(VRAM++) = *(data++);
        } else { VRAM++; data++; }
     }
     VRAM += LCD_WIDTH_PX-width;
   }
}

void CopySpriteMasked(const void*datar, int x, int y, int width, int height, int maskcolor) { 
   color_t*data = (color_t*) datar; 
   color_t* VRAM = (color_t*)0xA8000000; 
   VRAM += LCD_WIDTH_PX*y + x; 
   for(int j=y; j<y+height; j++) { 
      for(int i=x; i<x+width;  i++) { 
         if (*(data) != maskcolor && i>=0 && i<=384 && j>=0 && j<=216) { 
            *(VRAM++) = *(data++); 
         } else { VRAM++; data++; } 
      } 
      VRAM += LCD_WIDTH_PX-width; 
   } 
}

int RGBColor(int r, int g, int b)
{
  return ((r / 8) << 11) | ((g / 4) << 5) | (b / 8);
}

int GetR(color_t color){
	return ((color & 0xF800) >> 8);
}

int GetG(color_t color){
	return ((color & 0x07E0) >> 3);
}

int GetB(color_t color){
	return ((color & 0x001F) << 3);
}

int alpha_transparency(float alpha, float value1, float value2)
{
    return alpha * value1 + (1 - alpha) * value2;
}

void CopySpriteMaskedAlpha1(const void*datar, int x, int y, int width, int height, int maskcolor, float alpha) { 
   color_t*data = (color_t*) datar; 
   color_t* VRAM = (color_t*)0xA8000000; 
   int red = 0, green = 0, blue = 0, vr = 0, vg = 0, vb = 0;
   VRAM += LCD_WIDTH_PX*y + x;
   for(int j=y; j<y+height; j++) { 
      for(int i=x; i<x+width;  i++) { 
		 red = GetR(*data);
		 green = GetG(*data);
		 blue = GetB(*data);
		 vr = GetR(*VRAM);
		 vg = GetG(*VRAM);
		 vb = GetB(*VRAM);
         if (*(data) != maskcolor) { 
         *(VRAM) = RGBColor(alpha_transparency(alpha, red, vr), alpha_transparency(alpha, green, vg), alpha_transparency(alpha, blue, vb));
           VRAM++; data++; 
         } else { VRAM++; data++; } 
      } 
      VRAM += LCD_WIDTH_PX-width; 
   }  
}

//ProgrammerNerds routine
void CopySpriteMaskedAlpha(unsigned *data,unsigned x,unsigned y,unsigned width,unsigned height,unsigned maskcolor,unsigned alpha){ 
   unsigned short*v=(unsigned short*)0xA8000000; 
   unsigned* VRAM,w,alphai; 
   width/=2; 
   v += 384*y + x; 
   VRAM=v; 
   alphai=32-alpha; 
   maskcolor|=maskcolor<<16;/*Note I have decided to do a minor tradeoff for speed. Make sure your alpha pixels are multiple of two*/ 
   while(height--){ 
      w=width; 
      while(w--){ 
         unsigned color1=*data++; 
         if(color1 != maskcolor){ 
            /*Note this is based on the source code of Fblend's function fblend_rect_trans_16*/ 
            unsigned rbg_source, grb_source,temp1; 
            /* Split up components to allow us to do operations on all of them at the same time */ 
            rbg_source = *VRAM & 0xF81F07E0, 
            grb_source = *VRAM & 0x07E0F81F; 

            /* Multiply the source by the factor */ 
            rbg_source = ((rbg_source >> 5) * alpha) & 0xF81F07E0; 
            grb_source = ((grb_source * alpha) >> 5) & 0x07E0F81F; 

            /* Split up RGB -> R-B and G */ 
            temp1 = color1 & 0x7E0F81F; 
            color1 &= 0xF81F07E0; 

            /* Multiply the source by the factor */ 
            color1 = ((((color1 >> 5) * alphai) & 0xF81F07E0) + rbg_source) & 0xF81F07E0; 
            temp1  = ((((temp1 * alphai) >> 5)  & 0x07E0F81F) + grb_source) & 0x07E0F81F; 

            color1 |= temp1; 
            *VRAM++=color1; 
         }else 
            ++VRAM; 
      } 
      VRAM += (384/2)-width; 
   } 
} 

void CopySpriteCustom1(const void*datar, int x, int y, int width, int height, int color, int maskcolor, float alpha) { 
   color_t*data = (color_t*) datar; 
   color_t* VRAM = (color_t*)0xA8000000; 
   int red = 0, green = 0, blue = 0, vr = 0, vg = 0, vb = 0;
   red = GetR(color);
   green = GetG(color);
   blue = GetB(color);
   VRAM += LCD_WIDTH_PX*y + x;
   for(int j=y; j<y+height; j++) { 
      for(int i=x; i<x+width;  i++) { 
		 vr = GetR(*VRAM);
		 vg = GetG(*VRAM);
		 vb = GetB(*VRAM);
         if (*(data) != maskcolor) { 
         *(VRAM) = RGBColor(alpha_transparency(alpha, red, vr), alpha_transparency(alpha, green, vg), alpha_transparency(alpha, blue, vb));
           VRAM++; data++; 
         } else { VRAM++; data++; } 
      } 
      VRAM += LCD_WIDTH_PX-width; 
   } 
}

void CopySpriteNbitMasked(const unsigned char* data, int x, int y, int width, int height, const color_t* palette, color_t maskColor, unsigned int bitwidth)  
 {
   color_t* VRAM = (color_t*)0xA8000000;
   VRAM += (LCD_WIDTH_PX*y + x);
   int offset = 0;
   unsigned char buf;
   for(int j=y; j<y+height; j++)  
   {
      int availbits = 0;
      for(int i=x; i<x+width;  i++)  
      {
         if (!availbits)  
         {
            buf = data[offset++];
            availbits = 8;
         }
         color_t this = ((color_t)buf>>(8-bitwidth));
         color_t color = palette[this];
         if(color != maskColor)
         {
            *VRAM = color;
         }
         VRAM++;
         buf<<=bitwidth;
         availbits-=bitwidth;
      }
      VRAM += (LCD_WIDTH_PX-width);
   }
}

void CopySpriteCustom2(const unsigned char* data, int x, int y, int width, int height, const color_t* palette, color_t maskColor, unsigned int bitwidth, int custcolor)  
 {
   color_t* VRAM = (color_t*)0xA8000000;
   VRAM += (LCD_WIDTH_PX*y + x);
   int offset = 0;
   unsigned char buf;
   for(int j=y; j<y+height; j++)  
   {
      int availbits = 0;
      for(int i=x; i<x+width;  i++)  
      {
         if (!availbits)  
         {
            buf = data[offset++];
            availbits = 8;
         }
         color_t this = ((color_t)buf>>(8-bitwidth));
         color_t color = palette[this];
         if(color != maskColor && i >= 0 && i <= 384 && j >= 0 && j <= 216)
         {
            *VRAM = custcolor;
         }
         VRAM++;
         buf<<=bitwidth;
         availbits-=bitwidth;
      }
      VRAM += (LCD_WIDTH_PX-width);
   }
}

void CopySpriteCustom(const void*datar, int x, int y, int width, int height, int color, int maskcolor, float alpha) { 
   color_t*data = (color_t*) datar; 
   color_t* VRAM = (color_t*)0xA8000000; 
   VRAM += LCD_WIDTH_PX*y + x; 
   for(int j=y; j<y+height; j++) { 
      for(int i=x; i<x+width;  i++) { 
         if (*(data) != maskcolor && i>=0 && i<=384 && j>=0 && j<=216) { 
            *(VRAM++) = color; 
			data++;
         } else { VRAM++; data++; } 
      } 
      VRAM += LCD_WIDTH_PX-width; 
   } 
}

void PrintCustomFont(int x, int y, char *Msg, short color, short mask, float alpha){
	int i, j, k = 0;
	char Upper[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char Lower[26] = "abcdefghijklmnopqrstuvwxyz";
	char Num[10] = "0123456789";
	char Sym[4] = ".:+!";
	for(j = 0; j < strlen(Msg); j++){
		for(i = 0; i < 26; i++){
			if(Msg[j] == Upper[i]){
				CopySpriteCustom2(UpFont[i], x + k * 12, y, 16, 16, font_palette, COLOR_RED, 1, color);
				k++;
			}
			if(Msg[j] == Lower[i]){
				CopySpriteCustom2(LowFont[i], x + k * 12, y, 16, 16, font_palette, COLOR_RED, 1, color);
				k++;
			}
		}
		for(i = 0; i < 10; i++){
			if(Msg[j] == Num[i]){
				CopySpriteCustom2(NumFont[i], x + k * 12, y, 16, 16, font_palette, COLOR_RED, 1, color);
				k++;
			}
		}
		for(i = 0; i < 4; i++){
			if(Msg[j] == Sym[i]){
				CopySpriteCustom2(SymFont[i], x + k * 12, y, 16, 16, font_palette, COLOR_RED, 1, color);
				k++;
			}
		}
		if(Msg[j] == ' '){
			k++;
		}
	}
}

void PrintCustomFontSquished(int x, int y, char *Msg, short color, short mask, float alpha){
	int i, j, k = 0;
	char Upper[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char Lower[26] = "abcdefghijklmnopqrstuvwxyz";
	char Num[10] = "0123456789";
	char Sym[4] = ".:+!";
	for(j = 0; j < strlen(Msg); j++){
		for(i = 0; i < 26; i++){
			if(Msg[j] == Upper[i]){
				CopySpriteCustom2(UpFont[i], x + k * 10, y, 16, 16, font_palette, COLOR_RED, 1, color);
				k++;
			}
			if(Msg[j] == Lower[i]){
				CopySpriteCustom2(LowFont[i], x + k * 10, y, 16, 16, font_palette, COLOR_RED, 1, color);
				k++;
			}
		}
		for(i = 0; i < 10; i++){
			if(Msg[j] == Num[i]){
				CopySpriteCustom2(NumFont[i], x + k * 10, y, 16, 16, font_palette, COLOR_RED, 1, color);
				k++;
			}
		}
		for(i = 0; i < 4; i++){
			if(Msg[j] == Sym[i]){
				CopySpriteCustom2(SymFont[i], x + k * 10, y, 16, 16, font_palette, COLOR_RED, 1, color);
				k++;
			}
		}
		if(Msg[j] == ' '){
			k++;
		}
	}
}

void RotatedSprite(color_t *data, int x0, int y0, int width, int height, int maskcolor, int angle){
	int x, y;
	int hwidth, hheight;
	int xt, yt;
	double sinma, cosma;
	int xs, ys;
	for(x = 0; x < width; x++) {
		for(y = 0; y < height; y++) {
			hwidth = width / 2;
			hheight = height / 2;
			
			xt = x - hwidth;
			yt = y - hheight;
			
			sinma = sin1(-angle);
			cosma = cos1(-angle);
			
			xs = (int)round1((cosma * xt - sinma * yt) + hwidth);
			ys = (int)round1((sinma * xt + cosma * yt) + hheight);

			if(xs >= 0 && xs < width && ys >= 0 && ys < height && data[ys * width + xs] != maskcolor)
				plot(x0 + x, y0 + y, data[ys * width + xs]); /* set target pixel (x,y) to color at (xs,ys) */
		}
	}
}

color_t *Scale(color_t *temp, const color_t *data,int w1,int h1,int w2,int h2) {
    if((w2 <= 0) || (h2 <= 0)){
        return 0;
    } else {
        int x_ratio = ((w1<<16)/w2)+1;
        int y_ratio = ((h1<<16)/h2)+1;
        int x2, y2;
        for(int i=0;i<h2;i++) {
            for(int j=0;j<w2;j++) {
                x2 = ((j*x_ratio)>>16);
                y2 = ((i*y_ratio)>>16);
                temp[(i*w2)+j] = data[(y2*w1)+x2];
            }
        }
    }
    return temp;
}

void Scale1(color_t *out, color_t *in, unsigned w1, unsigned h1, unsigned w2, unsigned h2){   
   unsigned x_ratio = ((w1<<16)/w2)+1;   
   unsigned y_ratio = ((h1<<16)/h2)+1;   
   unsigned x2,y2,i,j;   
   for (i=0;i<h2;++i){   
      for (j=0;j<w2;++j){   
        x2 = ((j*x_ratio)>>16);   
        y2 = ((i*y_ratio)>>16);   
        color_t p=in[(y2*w1)+x2];  
		if(i >= 0 && i <= 216 && j >= 0 && j <= 384 && p != COLOR_RED)
			*out++=p;   
		else
			out++;
      } 
   out+=384-w2; 
   } 
} 

void DrawCircle(int xs, int ys, int radius, int color)
{
  int f = 1 - radius;
  int ddF_x = 1;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;

  plot(xs, ys + radius, color);
  plot(xs, ys - radius, color);
  plot(xs + radius, ys, color);
  plot(xs - radius, ys, color);

  while(x < y)
  {
    // ddF_x == 2 * x + 1;
    // ddF_y == -2 * y;
    // f == x*x + y*y - radius*radius + 2*x - y + 1;
    if(f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
    plot(xs + x, ys + y, color);
    plot(xs - x, ys + y, color);
    plot(xs + x, ys - y, color);
    plot(xs - x, ys - y, color);
    plot(xs + y, ys + x, color);
    plot(xs - y, ys + x, color);
    plot(xs + y, ys - x, color);
    plot(xs - y, ys - x, color);
  }
}

void drawLine(int x1, int y1, int x2, int y2, int color, int thickness) {
    signed char ix;
    signed char iy;

    // if x1 == x2 or y1 == y2, then it does not matter what we set here
    int delta_x = (x2 > x1?(ix = 1, x2 - x1):(ix = -1, x1 - x2)) << 1;
    int delta_y = (y2 > y1?(iy = 1, y2 - y1):(iy = -1, y1 - y2)) << 1;

   DrawCircle(x1, y1, thickness, color);
    if (delta_x >= delta_y) {
        int error = delta_y - (delta_x >> 1);        // error may go below zero
        while (x1 != x2) {
            if (error >= 0) {
                if (error || (ix > 0)) {
                    y1 += iy;
                    error -= delta_x;
                }                           // else do nothing
         }                              // else do nothing
            x1 += ix;
            error += delta_y;
            DrawCircle(x1, y1, thickness, color);
        }
    } else {
        int error = delta_x - (delta_y >> 1);      // error may go below zero
        while (y1 != y2) {
            if (error >= 0) {
                if (error || (iy > 0)) {
                    x1 += ix;
                    error -= delta_y;
                }                           // else do nothing
            }                              // else do nothing
            y1 += iy;
            error += delta_x;
            DrawCircle(x1, y1, thickness, color);
        }
    }
}

void drawRect(int x, int y, int width, int height, int color, int thickness){
    drawLine(x, y, x+width, y, color, thickness);
    drawLine(x, y, x, y+height, color, thickness);
    drawLine(x+width, y, x+width, y+height, color, thickness);
    drawLine(x, y+height, x+width, y+height, color, thickness);
    return;
}

float floor2(float x) { 
    return ((int)x) - (x < 0); 
}

float ceil2(float x) { 
    return ((int)x) + (x < 0); 
}

typedef struct
{
	char *Type;
	long long price;
	long long priceBase;
	float BCpS;
	int Owned;
} Building;

int i, j, k;
int time, oldTime, frameTime, prevTime;
float cookies = 0;
float CpS = 0;
int Selected = 0;
int SelectOffset = 0;
int priceColor;
int cursorDist = 72, cursorAngle = 0, cursorAngleT = 0;
float goldAlpha = 1;
int goldTime, goldOldTime, goldOnScreen = 0, goldDying = 0, randX, randY;
int ScaleW = 121, ScaleH = 122;
int FBUTTONS[6] = {KEY_PRGM_F1, KEY_PRGM_F2, KEY_PRGM_F3, KEY_PRGM_F4, KEY_PRGM_F5, KEY_PRGM_F6};
int randGain;
int earned, msgDisplay, msgTime;
int frenzyCpS, frenzyLengthCpS, frenzyTimeCpS;
int frenzyClick, frenzyLengthClick, frenzyTimeClick;
char frenzyBuf[5];
char msg[50], msgT[50];
char CookieBuf[50];
char OwnedBuf[10];
char priceBuf[50];
char earnedBuf[50];
char RTCBuf[20];
char CpSBuf[20], CpSBuf1[20];
char Blab[24][32] = {
	"Cookie crumbliness x3", "for 60 seconds!",
	"Chocolatiness x7", "for 77 seconds!",
	"Dough elasticity halved", "for 66 seconds!",
	"Golden cookie shininess doubled", "for 3 seconds!",
	"World economy halved", "for 30 seconds!",
	"Grandma kisses 23% stingier", "for 45 seconds!",
	"Thanks for clicking!", "",
	"Fooled you!", "This one was just a test.",
	"Golden cookies clicked +1!", "",
	"Your click has been registered.", "Thank you for your cooperation.",
	"Thanks!", "That hit the spot!",
	"Your cookies are never gonna", "give you up!"
};
Building Buildings[11];
color_t scale[29524];
int *screen;

int GetNumSec(){
	return (int)(RTC_GetTicks() / 128);
}

void SaveGame(){
	char infoBuf[335];
	int i, j, time;
	unsigned short pFile[sizeof(PATH)*2];
	Bfile_StrToName_ncpy(pFile, (unsigned char*)PATH, sizeof(PATH));
	int hFile;
	hFile = Bfile_OpenFile_OS(pFile, 3, 0);
	if(hFile < 0){
		int size = 335;
		Bfile_CreateEntry_OS(pFile, 1, &size);
		hFile = Bfile_OpenFile_OS(pFile, 3, 0);
	}
	itoa(cookies, CookieBuf);
	for(i = 0; i < 15 - strlen(CookieBuf); i++){
		if(i == 0)
		strcpy(infoBuf, " ");
		else
		strcat(infoBuf, " ");
	}
	strcat(infoBuf, CookieBuf);
	strcat(infoBuf, ";");
	itoa((int)floor2(CpS), CpSBuf1);
	strcpy(CpSBuf, CpSBuf1);
	if((CpS - floor2(CpS)) * 10 > 0){
		strcat(CpSBuf, ".");
		itoa((int)((CpS - floor2(CpS)) * 10), CpSBuf1);
		strcat(CpSBuf, CpSBuf1);
	}
	strcat(infoBuf, CpSBuf);
	for(i = 0; i < 15 - strlen(CpSBuf); i++)
		strcat(infoBuf, " ");
	strcat(infoBuf, ";");
	for(i = 0; i < 9; i++){
		itoa(Buildings[i].Owned, OwnedBuf);
		for(j = 0; j < 15 - strlen(OwnedBuf); j++)
			strcat(infoBuf, " ");
		strcat(infoBuf, OwnedBuf);
		strcat(infoBuf, ";");
		itoa((int)Buildings[i].price, priceBuf);
		for(j = 0; j < 15 - strlen(priceBuf); j++)
			strcat(infoBuf, " ");
		strcat(infoBuf, priceBuf);
		strcat(infoBuf, ";");
	}
	time = GetNumSec();
	itoa(time, RTCBuf);
	for(i = 0; i < 15 - strlen(RTCBuf); i++)
		strcat(infoBuf, " ");
	strcat(infoBuf, RTCBuf);
	Bfile_WriteFile_OS(hFile, infoBuf, sizeof(infoBuf));
	Bfile_CloseFile_OS(hFile);
}

void LoadGame(){
	char infoBuf[15];
	int i, timePassed;
	unsigned short pFile[sizeof(PATH)*2];
	Bfile_StrToName_ncpy(pFile, (unsigned char*)PATH, sizeof(PATH));
	int hFile;
	hFile = Bfile_OpenFile_OS(pFile, 3, 0);
	if(hFile < 0)
		return;
	Bfile_ReadFile_OS(hFile, infoBuf, 15, 0);
	cookies = (int)strtol(infoBuf, NULL, 10);
	infoBuf[0] = 0;
	Bfile_ReadFile_OS(hFile, infoBuf, 15, 16);
	CpS = atof(infoBuf);
	infoBuf[0] = 0;
	for(i = 1; i < 21; i+=2){
		Bfile_ReadFile_OS(hFile, infoBuf, 15, (i + 2) * 16);
		Buildings[(i-1)/2].price = (int)strtol(infoBuf, NULL, 10);
	}
	infoBuf[0] = 0;
	for(i = 0; i < 20; i+=2){
		Bfile_ReadFile_OS(hFile, infoBuf, 15, (i + 2) * 16);
		Buildings[i/2].Owned = (int)strtol(infoBuf, NULL, 10);
	}
	infoBuf[0] = 0;
	//Bfile_ReadFile_OS(hFile, infoBuf, 15, 321);
	//prevTime = (int)strtol(infoBuf, NULL, 10);
	Bfile_CloseFile_OS(hFile);
	//timePassed = GetNumSec() - prevTime;
	//cookies = cookies + (timePassed * CpS);
}

void BuildingsReset(){
	Buildings[0].Type = "Cursor";
	Buildings[0].priceBase = 15;
	Buildings[0].BCpS = 0.1;
	Buildings[1].Type = "Grandma";
	Buildings[1].priceBase = 100;
	Buildings[1].BCpS = 0.5;
	Buildings[2].Type = "Farm";
	Buildings[2].priceBase = 500;
	Buildings[2].BCpS = 4;
	Buildings[3].Type = "Factory";
	Buildings[3].priceBase = 3000;
	Buildings[3].BCpS = 10;
	Buildings[4].Type = "Mine";
	Buildings[4].priceBase = 10000;
	Buildings[4].BCpS = 40;
	Buildings[5].Type = "Shipment";
	Buildings[5].priceBase = 40000;
	Buildings[5].BCpS = 100;
	Buildings[6].Type = "Alchemy Lab";
	Buildings[6].priceBase = 200000;
	Buildings[6].BCpS = 400;
	Buildings[7].Type = "Portal";
	Buildings[7].priceBase = 1666666;
	Buildings[7].BCpS = 6666;
	Buildings[8].Type = "Time Machine";
	Buildings[8].priceBase = 123456789;
	Buildings[8].BCpS = 98765;
	Buildings[9].Type = "Antimatter Con.";
	Buildings[9].priceBase = 3999999999;
	Buildings[9].BCpS = 999999;
	Buildings[10].Type = "Prism";
	Buildings[10].priceBase = 75000000000;
	Buildings[10].BCpS = 10000000;
	for(i = 0; i < 11; i++){
		Buildings[i].Owned = 0;
		Buildings[i].price = Buildings[i].priceBase;
	}
}

void addCpS(){
	oldTime = time;
	time = RTC_GetTicks() / 128;
	frameTime = time - oldTime;
	if(frameTime == 1){
		if(frenzyCpS)
			cookies += CpS * 7;
		else
			cookies += CpS;
	}
}

void randGold(){
	randX = random() % 6;
	randY = random() % 171;
}

void goldenCookie(){
	if(GetNumSec() == goldTime){
		goldOnScreen = 1;
		goldOldTime = GetNumSec() + 13;
	}
	if(goldAlpha <= 0 && goldOnScreen == 0){
		randGold();
	}
	if(goldOnScreen){
		CopySpriteMaskedAlpha1(goldCookie, 10 + randX * 64, randY, 46, 46, COLOR_RED, goldAlpha);
		if(GetNumSec() == goldOldTime && goldAlpha > 0){
			goldDying = 1;
		}
		if(keydownlast(FBUTTONS[randX]) && !keydownhold(FBUTTONS[randX])){
			randGain = random() % 100 + 1;
			msgDisplay = 1;
			if(randGain > 0 && randGain <= 48){
				earned = min(cookies * 0.1, CpS * 60 * 20) + 13;
				cookies = cookies + earned;
				strcpy(msgT, "Lucky!");
				strcpy(msg, "+");
				itoa(earned, earnedBuf);
				strcat(msg, earnedBuf);
				strcat(msg, " cookies!");
			}
			if(randGain > 48 && randGain <= 96){
				frenzyCpS = 1;
				frenzyLengthCpS = 77;
				strcpy(msgT, "Frenzy: ");
				strcpy(msg, "cookie production x7 for ");
				itoa(frenzyLengthCpS, frenzyBuf);
				strcat(msg, frenzyBuf);
				strcat(msg, " seconds!");
				frenzyTimeCpS = GetNumSec() + frenzyLengthCpS;
			}
			if(randGain > 96 && randGain <= 99){
				frenzyClick = 1;
				frenzyLengthClick = 13;
				strcpy(msgT, "Click frenzy!"); 
				strcpy(msg, "Clicking power x777 for ");
				itoa(frenzyLengthClick, frenzyBuf);
				strcat(msg, frenzyBuf);
				strcat(msg, " seconds!");
				frenzyTimeClick = GetNumSec() + frenzyLengthClick;
			}
			if(randGain == 100){
				strcpy(msgT, Blab[(int)((random() % 12) * 2)]);
				strcpy(msg, Blab[(int)((random() % 12) * 2) + 1]);
			}
			msgTime = GetNumSec() + 3;
			goldOnScreen = 0;
			goldAlpha = 0;
			goldDying = 0;
			randGold();
			goldTime =  GetNumSec() + 10;//(random() % 600 + 300);
		}	
		if(goldDying && goldAlpha >= 0)
			goldAlpha-=.1;
		else if(goldDying == 0 && goldAlpha < 1)
			goldAlpha+=.1;
		if(GetNumSec() >= goldOldTime && goldAlpha <= 0){
			goldOnScreen = 0;
			goldAlpha = 0;
			goldDying = 0;
			randGold();
			goldTime =  GetNumSec() + 10;//(random() % 600 + 300);
		}
	}
}

void displayMsg(char *Msg, char *MsgT){
	fillArea((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2, 169, max(strlen(Msg), strlen(MsgT)) * 10 + 5, 42, RGBColor(31, 31, 31));
	drawLine((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2, 168, ((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2) + (max(strlen(Msg), strlen(MsgT)) * 10 + 5), 168, RGBColor(100, 104, 58), 1);
	drawLine((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2, 167, ((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2) + (max(strlen(Msg), strlen(MsgT)) * 10 + 5), 167, RGBColor(169, 174, 96), 0);
	drawLine((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2 + 1, 169, (345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2 + 1, 210, RGBColor(70, 58, 25), 1);
	drawLine((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2, 169, ((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2), 210, RGBColor(138, 115, 48), 0);
	drawLine((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2 + 2, 211, ((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2) + (max(strlen(Msg), strlen(MsgT)) * 10 + 5) - 1, 211, RGBColor(113, 78, 49), 1);
	drawLine(((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2) + (max(strlen(Msg), strlen(MsgT)) * 10 + 5), 210, ((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2) + (max(strlen(Msg), strlen(MsgT)) * 10 + 5), 169, RGBColor(138, 115, 48), 1);
	
	PrintCustomFontSquished((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2 + 1, 170, MsgT, RGBColor(169, 169, 169), RGBColor(31, 31, 31), 1);
	drawLine((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2 + 6, 189, ((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2) + (max(strlen(Msg), strlen(MsgT)) * 10 + 5) - 6, 189, RGBColor(169, 169, 169), 0);
	PrintCustomFontSquished((345 - (max(strlen(Msg), strlen(MsgT)) * 9)) / 2 + 1, 191, Msg, RGBColor(169, 169, 169), RGBColor(31, 31, 31), 1);
}

void drawStore(){
		//PrintMiniFix(255, 8, "Store", 0x42, 0xffff, 0x0000);
		PrintCustomFontSquished(255, 8, "Store", 0xffff, 0x0000, 1);
		for(i = 0; i < 4; i++){
			CopySprite(storeTile, 186, 48 + i * 42, 198, 42);
			CopySpriteMasked(Icons[i + SelectOffset], 186, 48 + i * 42, 42, 42, COLOR_RED);
			CopySpriteMasked(money, 228, 69 + i * 42, 16, 16, COLOR_RED);
			itoa((int)Buildings[i+SelectOffset].price, priceBuf);
			if(floor2(cookies) >= Buildings[i + SelectOffset].price){
				priceColor = 0x67ec;
			} else {
				priceColor = COLOR_RED;
			}
			//PrintMiniFixSquished(244, 69 + i * 42, priceBuf, 0x42, priceColor, 0x0000);
			PrintCustomFontSquished(244, 69 + i * 42, priceBuf, priceColor, 0x0000, 1);
			itoa(Buildings[i+SelectOffset].Owned, OwnedBuf);
			//PrintMiniFix(380 - strlen(OwnedBuf) * 12, 61 + i * 42, OwnedBuf, 0x42, 0x0000, 0x0000);
			PrintCustomFont(380 - strlen(OwnedBuf) * 12, 61 + i * 42, OwnedBuf, 0x0000, 0x0000, 1);
			//PrintMiniFixSquished(228, 54 + i * 42, Buildings[i + SelectOffset].Type, 0x42, 0xffff, 0x0000);
			PrintCustomFontSquished(228, 54 + i * 42, Buildings[i + SelectOffset].Type, 0xffff, 0x0000, 1);
		}
		drawRect(187, 49 + Selected * 42, 195, 39, 0xff80, 1);
		if((keydownlast(KEY_PRGM_DOWN) && !keydownhold(KEY_PRGM_DOWN)) && Selected < 3){
			Selected++;
		} else if((keydownlast(KEY_PRGM_DOWN) && !keydownhold(KEY_PRGM_DOWN)) && Selected == 3 && SelectOffset < 5){
			SelectOffset++;
		}
		if((keydownlast(KEY_PRGM_UP) && !keydownhold(KEY_PRGM_UP)) && Selected > 0){
			Selected--;
		} else if((keydownlast(KEY_PRGM_UP) && !keydownhold(KEY_PRGM_UP)) && Selected == 0 && SelectOffset > 0){
			SelectOffset--;
		}
		if((keydownlast(KEY_PRGM_ALPHA) && !keydownhold(KEY_PRGM_ALPHA)) && (floor2(cookies) >= Buildings[Selected + SelectOffset].price)){
			cookies -= (int)Buildings[Selected + SelectOffset].price;
			Buildings[Selected + SelectOffset].Owned++;
			Buildings[Selected + SelectOffset].price = ceil2(Buildings[Selected + SelectOffset].price + Buildings[Selected + SelectOffset].price * .15);
			CpS += Buildings[Selected + SelectOffset].BCpS;
		}
}

void drawCookieData(){
		Scale1((color_t*)0xA8000000+((ScaleW < 121) ? 29 : 25)+(((ScaleH < 122) ? 83 : 79)*384), perfectCookie, 121, 122, ScaleW, ScaleH);
		//CopySpriteMasked(scale, ((ScaleW < 121) ? 29 : 25), ((ScaleH < 122) ? 83 : 79), ScaleW, ScaleH, COLOR_RED);
		fillArea(0, 15, 170, 54, 0x0000);
		itoa((int)floor2(cookies), CookieBuf);
		if(frenzyCpS)
			itoa((int)floor2(CpS * 7), CpSBuf1);
		else
			itoa((int)floor2(CpS), CpSBuf1);
		strcpy(CpSBuf, "CpS:");
		strcat(CpSBuf, CpSBuf1);
		if((CpS - floor2(CpS)) * 10 > 0){
			strcat(CpSBuf, ".");
			itoa((int)((CpS - floor2(CpS)) * 10), CpSBuf1);
			strcat(CpSBuf, CpSBuf1);
		}
		//PrintMiniFix(82 - strlen(CookieBuf) * 6, 17, CookieBuf, 0x42, 0xffff, 0x0000);
		PrintCustomFontSquished(84 - strlen(CookieBuf) * 5, 17, CookieBuf, 0xffff, 0x0000, 1);
		//PrintMiniFix(42, 34, "cookies", 0x42, 0xffff, 0x0000);
		PrintCustomFont(39, 34, "cookies", 0xffff, 0x0000, 1);
		//PrintMiniFix(82 - strlen(CpSBuf) * 6, 51, CpSBuf, 0x42, 0xffff, 0x0000);
		PrintCustomFontSquished(82 - strlen(CpSBuf) * 5, 51, CpSBuf, 0xffff, 0x0000, 1);
		/* cursorAngle = 360 / Buildings[0].Owned;
		for(i = 0; i < Buildings[0].Owned; i++){
			RotatedSprite(cursor, 69 + cos1(cursorAngleT) * cursorDist, 124 + sin1(cursorAngleT) * cursorDist, 32, 32, COLOR_RED, cursorAngleT);
			cursorAngleT = i * cursorAngle;
		} */
}

void drawBack(){
	int i, color;
	for(i = 0; i < 12; i++){
		if(i % 2 != 0){
			color = RGBColor(44, 108, 143);
		} else if(i % 2 == 0){
			color = RGBColor(35, 94, 128);
		}
		fillArea(i * 32, 0, 32, 216, color);
	}
	CopySprite(panelVertical, 170, 0, 16, 216);
	CopySprite(panelHorizontal, 186, 32, 198, 16);
}

void cookiePush(){
    int key = PRGM_GetKey();
	if(keydownlast(KEY_PRGM_SHIFT) && !keydownhold(KEY_PRGM_SHIFT)){
		ScaleW = 112;
		ScaleH = 113;
		if(frenzyClick)
			cookies += 777;
		else
			cookies++;
	}
	if(key == 0){
		ScaleW = 121;
		ScaleH = 122;
	}
}

int main()
{
    Bdisp_EnableColor(1);
	BuildingsReset();
	srandom(RTC_GetTicks());
	goldTime =  GetNumSec() + 10;//(random() % 600 + 300);
	LoadGame();
	while(1)
	{
        int key = PRGM_GetKey();
        if(key == KEY_PRGM_MENU){
			SaveGame();
			GetKey(&key); 
		}
		keyupdate();
		drawBack();
		drawStore();
		cookiePush();
		drawCookieData();
		if(msgDisplay){
			displayMsg(msg, msgT);
			if(GetNumSec() == msgTime)
				msgDisplay = 0;
		}
		goldenCookie();
		if(GetNumSec() == frenzyTimeCpS)
			frenzyCpS = 0;
		if(GetNumSec() == frenzyTimeClick)
			frenzyClick = 0;
		addCpS();
        Bdisp_PutDisp_DD();
		if(key == KEY_PRGM_7)
			GetKey(screen);
        Bdisp_AllClr_VRAM();
	}
	return 0;
}
