/* check for neighbors and deal with cluster labels */
/* point neighbors to new site, island size -> proper label */

#include <stdio.h>

#include "globals.h"

extern int proper(int label);

void check_neigh(int point_ind, int point_check);

void 
check_neighbors(int point_ind)
{
	int i;
	int j;

	i = point[point_ind].x;
	j = point[point_ind].y;

	check_neigh(point_ind,grid[IMINUS][j]);
	check_neigh(point_ind,grid[IPLUS][j]);
	check_neigh(point_ind,grid[i][JMINUS]);
	check_neigh(point_ind,grid[i][JPLUS]);
}

void 
check_neigh(int point_ind, int point_check)
{
	int label;

	if(point_check > 0) {
		point[point_ind].neigh = point[point_ind].neigh + 1;
		point[point_check].neigh = point[point_check].neigh + 1;
		label = proper(point_check);
		if(label != point_ind) {
			point[point_ind].clus \
			= point[point_ind].clus + point[label].clus;
			point[label].clus = -point_ind;
		}
	}
}
