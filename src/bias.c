#include <stdio.h>

#include "globals.h"

int
distance(int i, int j, int direction);

void
bias(int i, int j)
{
	double pleft;
	double pright;
	double pdown;
	double pup;
	double ptotal;

	/* find distance to neighbors */
	printf("distance to nearest neighbor left: %d\n", distance(i,j,LEFT));
	printf("distance to nearest neighbor right: %d\n", distance(i,j,RIGHT));
	printf("distance to nearest neighbor down: %d\n", distance(i,j,DOWN));
	printf("distance to nearest neighbor up: %d\n", distance(i,j,UP));

	/* probabilities */
	pleft = 0.25/distance(i,j,LEFT);
	pright = 0.25/distance(i,j,RIGHT);
	pdown = 0.25/distance(i,j,DOWN);
	pup = 0.25/distance(i,j,UP);
	ptotal = pleft + pright + pdown + pup;

	printf("pleft: %lf\n", pleft);
	printf("pright: %lf\n", pright);
	printf("pdown: %lf\n", pdown);
	printf("pup: %lf\n", pup);
	printf("ptotal: %lf\n", ptotal);
}

int
distance(int i, int j, int direction)
{
	int d;

	d = 0;
	do {
		if(direction == LEFT) {
			i = IMINUS;
		} else if(direction == RIGHT) {
			i = IPLUS;
		} else if(direction == DOWN) {
			j = JMINUS;
		} else if(direction == UP) {
			j = JPLUS;
		}
		d++;
	} while(grid[i][j] == 0);
	return d;
}
