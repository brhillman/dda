/* returns the number of islands on the grid */

#include "globals.h"

int 
islands(void)
{
	int i;
	int isl;

	isl = 0;
	for(i = 0; i <= drop_count; i++) {
		if(point[i].clus > 1) isl = isl + 1;
	}
	return isl;
}
