#include <stdio.h>
#include <stdlib.h>
#include "dihcodes.h"

int main(int argc, char *argv[])
{
    i_64 i;

    kdmask(argv, 1);
 
    for (i = 1; i < MASK; i++)
        if (unitary(i))
            printf("%s\n", binstr(i));

    return 0;
}
