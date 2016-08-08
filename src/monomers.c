/* returns the number of monomers on the grid with n neighbors */

#include "globals.h"

int 
monomers(int n)
{
        int i;
        int mon;

        mon = 0;
	for(i = 1; i <= drop_count; i++) {
		if(point[i].neigh == n) mon = mon + 1;
	}

        return mon;
}
