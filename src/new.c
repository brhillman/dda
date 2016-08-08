/* drop a new particle of size given by drop_size */

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

extern void check_neighbors(int point_ind);

void drop_first(int i, int j);
void drop_more(int i, int j);

void 
new(int drop_size)
{
        int i;
        int j;
	int n;
	double num;

        i = (int) L*drand48();
        j = (int) L*drand48();

	drop_first(i,j);
	for(n=1; n<drop_size; n++) drop_more(i,j);

	num = drand48();
}

void 
drop_first(int i, int j)
{
	if(grid[i][j] == 0) {
		drop_count++;
		grid[i][j] = drop_count;
		point[drop_count].clus = 1;
		point[drop_count].x = i;
		point[drop_count].y = j;
		check_neighbors(drop_count);
	}
}

void 
drop_more(int i, int j)
{
	double num;		/* random number */

	num = drand48();
	if(num < 0.25) {
		i = IMINUS;
	} else if(num < 0.50) {
		i = IPLUS;
	} else if(num < 0.75) {
		j = JMINUS;
	} else if(num < 1.00) {
		j = JPLUS;
	}

	if(grid[i][j] == 0) {
		drop_count++;
		grid[i][j] = drop_count;
		point[drop_count].clus = 1;
		check_neighbors(drop_count);
	}
}
