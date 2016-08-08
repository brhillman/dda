/*
 * the redirect() function is meant to redirect labels pointing to a
 * particle with one neighbor that is to be walked using the walk 
 * function. No checking is done to be sure that the site passed actually
 * has one and only one neighbor, so be sure to check this before calling
 * redirect().
 */

#include <stdio.h>

#include "globals.h"

extern int proper(int label);

void 
redirect(int i, int j)
{
	int n;
	int neighbor;
	int label;
	int size;

	/* find a neighbor to redirect labels to */
	neighbor = 0;
	if(grid[IMINUS][j] > 0) {
		neighbor = grid[IMINUS][j];
	} else if(grid[IPLUS][j] > 0) {
		neighbor = grid[IPLUS][j];
	} else if(grid[i][JMINUS] > 0) {
		neighbor = grid[i][JMINUS];
	} else if(grid[i][JPLUS] > 0) {
		neighbor = grid[i][JPLUS];
	}

	/* point old proper label to neighbor */
	label = proper(neighbor);
	size = point[label].clus - 1;
	point[label].clus = -neighbor;

	/* give neighbor the proper label */
	point[neighbor].clus = size;

	/* redirect labels pointing to grid[i][j] */
	for(n = 0; n <= drop_count; n++){
		if(point[n].clus == -grid[i][j]) point[n].clus = -neighbor;
	}

	/* treat grid[i][j] as a monomer until checked */
	point[grid[i][j]].clus = 1;

	/* grid[i][j] is a walker, so "neighbor" has one less neighbor */
	point[neighbor].neigh = point[neighbor].neigh - 1;
}
