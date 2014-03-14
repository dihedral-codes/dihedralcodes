#include <string.h>

#define i_64 unsigned long long  

extern int K;
extern int D;
extern i_64 MASK;

#define wt __builtin_popcountll
#define binstr(y) strtoull(y, NULL, 2)

i_64 rowi(i_64 d, int i);
int unitary(i_64 d);
