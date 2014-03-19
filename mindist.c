#include <stdio.h>
#include <stdlib.h>
#include "dihcodes.h"


int mindistD(i_64 d);
int re_mindistD(i_64 d, i_64 stem, int my1pos, int noones, int no0sused, int nosec0);
int check_comb(i_64 d, i_64 rowcomb);

int main(int argc, char *argv[])
{
    i_64 d = strbin(argv[1]);

    if (mindistD(d)) printf("Minimum distance is at least D.\n");
    else printf("Minimum distance is less than D.\n");

    return(0);
}

int mindistD(i_64 d)
{
    int posswt, psec1;
    
    for (psec1 = 1; psec1 < (K/2) + 1; psec1++)
        if (!check_comb(d, 1ULL | (1ULL << psec1)))
            return(0);

    for (posswt = 3; posswt < (K + 1); posswt++)
        for (psec1 = 1; psec1 < K - psec1-1 - ((posswt-2) * psec1)-1; psec1++)
            if (!re_mindistD(d, (1ULL | (1ULL<<psec1)), 3, posswt, psec1-1, psec1-1))
                return(0);

    return(1);

}

int re_mindistD(i_64 d, i_64 stem, int my1pos, int noones, int no0sused, int nosec0)
{

    int position;

    if (my1pos == noones) {
        for (position = no0sused + (my1pos - 1) + nosec0;
              position < K - nosec0 - 1;
              position++)
            if (!check_comb(d, (stem | (1ULL << position))))
                return(0);
    } else {
        for (position = no0sused + (my1pos - 1) + nosec0;
              position < K - nosec0 - ((noones - my1pos) * (nosec0 + 1)) - 1;
              position++)
            if (!re_mindistD(
                d,
                (stem | (1ULL << position)),
                (my1pos + 1),
                noones,
                (position - my1pos + 1),
                nosec0
            )) return(0);
    }

    return(1);
}

int check_comb(i_64 d, i_64 rowcomb)
{
    i_64 codeword = d;
    int i;

    for (i = 1; i < K; i++) 
        if (rowcomb & (1ULL << i))
            (codeword ^= rowi(d, i));

    if ((wt(codeword) + wt(rowcomb)) < D) return(0);
    else                          return(1);

}
