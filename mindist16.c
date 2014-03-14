#include <stdio.h>
#include "dihcodes.h"

int main(int argc, char *argv[])
{
    int u, v, w, x, y;
    int cont = 1;
    
    kdmask(argv);
    i_64 d = binstr(argv[1]);

    printf("%llx\n", d);

    for (u = 1; u <= K/2; u++){
        if (wt(d ^ rowi(d, u)) < 14){
            printf("D < 16: 0 %d\n", u);
            return 0;
        }
    }
    
    for (u = 1; u <= K/3; u++){
        for (v = 2 * u; K-v >= u; v++){
            if (wt(d ^ (rowi(d,u) ^ rowi(d,v))) < 13){
                printf("D < 16: 0 %d %d\n", u, v);
                return 0;
            }
        }
    }
    
    for (u = 1; u <= K/4; u++){
        for (v = 2 * u; K-v >= 2 * u; v++){
            for (w = v + u; K-w >= u; w++){
                if (wt(d ^ rowi(d, u) ^ rowi(d, v) ^ rowi(d, w)) < 12){
                    printf("D < 16: 0 %d %d %d\n", u, v, w);
                    return 0;
                }
            }
        }
    }

    for (u = 1; u <= K/5; u++){
        for (v = 2 * u; K-v >= 3 * u; v++){
            for (w = v + u; K-w >= 2 * u; w++){
                for (x = w + u; K-x >= u; x++){
                    if (wt(d ^ rowi(d, u) ^ rowi(d, v) ^ rowi(d, w) ^ rowi(d, x)) < 11){
                        printf("D<16: 0 %d %d %d %d\n", u, v, w, x);
                        return 0;
                    }    
                }
            }
        }
    }

    for (u = 1; u <= K/6; u++){
        for (v = 2 * u; K-v >= 4 * u; v++){
            for (w = v + u; K-w >= 3 * u; w++){
                for (x = w + u; K-x >= 2 * u; x++){
                    for (y = x + u; K-y >= u; y++){
                        if (wt(d ^ rowi(d, u) ^ rowi(d, v) ^ rowi(d, w) ^ rowi(d, x) ^ rowi(d,y)) < 10){
                            printf("D<16: 0 %d %d %d %d %d\n", u, v, w, x, y);
                            return 0;
                        }    
                    }
                }
            }
        }
    }
    
    if (cont) printf("D >= 16!\n");

    return 0;
    
}

