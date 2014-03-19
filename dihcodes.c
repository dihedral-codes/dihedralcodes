#include <stdio.h>
#include <stdlib.h>
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
void kdmask(char *argv[], int start)
{
    int i;

    K = (int) strtol(argv[start], NULL, 10);
    D = (int) strtol(argv[start+1], NULL, 10);
    MASK = 0;

    for (i = 0; i < K; i++){
        MASK |= 0x1ULL << i;
    }
}

// Returns an unsigned long long as a string with 1's and 0's.
char *binstr(unsigned long long d)
{
    char *s = malloc(sizeof(char) * 65);
    int i;

    for (i = 0; i < 64; i++)
        s[i] = (((d >> (63-i)) & 1ULL) ? '1' : '0');
    s[64] = '\0';

    return s;
}
