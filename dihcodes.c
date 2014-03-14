#include <stdio.h>
#include "dihcodes.h"

/* 
 * These are functions to do with Dihedral Codes.
 * Dihedral codes are group ring codes where the group is a dihedral group.
 * The largest dihedral group that these functions can accomodate is that of
 * one hundred and twenty eight elements. This is due to the limitation of
 * sixty-four bit integers.
 *
*/

int K = 0;
int D = 0;
i_64 MASK = 0;

// Returns the row i of A, which is d left-cycled by i.
i_64 rowi(i_64 d, int i)
{
    return (d >> K-i | d << i) & MASK;
}

// Returns one if d is unitary, zero otherwis
int unitary(i_64 d)
{
    int i;

    // Check d is of odd weight.
    if (~(wt(d) & 1)) return 0;
    // Check combinations of d and rows 2 to K/2 incl. are of even weight.
    for (i = 1; i <= K/2; i++) 
        if (wt(d & rowi(d, i)) & 1) return 0;

    return 1;
}

// Assigns the global variables K, D and MASK from an argv.
void kdmask(char *argv[])
{
    int i;

    K = (int) strtol(argv[2], NULL, 10);
    D = (int) strtol(argv[3], NULL, 10);
    MASK = 0;

    for (i = 0; i < K; i++){
        MASK |= 0xFULL << 4 * i;
    }
}
