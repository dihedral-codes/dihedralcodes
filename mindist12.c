#include <stdio.h>
#include "dihcodes.h"

int K = 0;
int D = 0;
ull MASK = 0;

int main(int argc, char *argv[])
{
    int u, v, w, x, y;
    int cont = 1;
    
    kdmask(argv);
    ull d = binstr(argv[1]);

    for (u = 1; u <= K/2; u++){
        if (wt(d ^ rowi(d, u)) < 10){
            printf("D < 12: 0 %d\n", u);
            return 0;
        }
    }
    
    for (u = 1; u <= K/3; u++){
        for (v = 2 * u; K-v >= u; v++){
            if (wt(d ^ (rowi(d,u) ^ rowi(d,v))) < 9){
                printf("D < 12: 0 %d %d\n", u, v);
                return 0;
            }
        }
    }
    
    for (u = 1; u <= K/4; u++){
        for (v = 2 * u; K-v >= 2 * u; v++){
            for (w = v + u; K-w >= u; w++){
                if (wt(d ^ rowi(d, u) ^ rowi(d, v) ^ rowi(d, w)) < 8){
                    printf("D < 12: 0 %d %d %d\n", u, v, w);
                    return 0;
                }
            }
        }
    }

    if (cont) printf("D >= 12!\n");

    return 0;
    
}

