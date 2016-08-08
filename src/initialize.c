/* initialize() sets all the elements of an array to zero. */

#include <stdio.h>

#include "globals.h"

void 
initialize(int array[L][L])
{
        int i;
        int j;
        for(i=0; i<L; i++) {
                for(j=0; j<L; j++) {
                        array[i][j] = 0;
                }
        }
}
