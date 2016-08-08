/* 
 * Move a particle with n neighbors one step in a random direction. If any
 * function could use optimizing, it is this one. The majority of the CPU
 * time is spent in this function, and I am confident this function is still
 * written inefficiently.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "globals.h"

extern void check_neighbors(int point_ind);
extern void redirect(int i, int j);
extern void display(int array[L][L]);

void find_walker(int n, int *i, int *j, int *point_ind);
void get_walk_probs(int i, int j);
int distance(int i, int j, int direction);
void get_direction(int i, int j, int *inew, int *jnew);

static double pleft;	/* probability of a walker moving left 1 grid point */
static double pright;	/* probability of a walker moving right 1 grid point */
static double pdown;	/* probability of a walker moving down 1 grid point */
static double pup;	/* probability of a walker moving up 1 grid point */

void 
walk(int n)
{
	int i;		/* i-coordinate of walker */
	int j;		/* j-coordinate of walker */
	int inew;	/* i-coordinate of point to walk to */
	int jnew;	/* j-coordinate of point to walk to */
	int point_ind;	/* index of selected walker on x,y arrays */

	find_walker(n,&i,&j,&point_ind);	/* select a monomer to walk */
	get_walk_probs(i,j);			/* direction probabilities */
	get_direction(i,j,&inew,&jnew);		/* walk the selected monomer */

	/*
	 * If we are walking a monomer with neighbors, we have to be carefull
	 * to deal with the cluster labels properly. First, we redirect any
	 * labels pointing to the walker to some adjacent monomer, to be
	 * determined by the redirect() routine. We subtract 1 from the
	 * neighbor counter for the selected walker, assuming that the walker
	 * completely leaves any neighbor it was attached to. We then check
	 * for neighbors, and relabel appropriately.
	 */
	if(n > 0) redirect(i,j);		/* redirect pointers */
	grid[inew][jnew] = grid[i][j];		/* move walker */
	grid[i][j] = 0;				/* vacate old position */
	point[point_ind].x = inew;
	point[point_ind].y = jnew;
	if(n > 0) point[point_ind].neigh--;	/* one neighbor less */
	check_neighbors(point_ind);		/* check for neighbors */
}

/*
 * find_walker() simply selects a monomer with the number of neighbors passed
 * by the parameter n. This is done by choosing random grid locations until
 * we find one occupied by a monomer with the desired number of neighbors.
 */
void
find_walker(int n, int *i, int *j, int *point_ind)
{
	do {
		*point_ind = (int) (1.0 + drop_count*drand48());
		*i = point[*point_ind].x;
		*j = point[*point_ind].y;
	} while(!grid[*i][*j] || point[*point_ind].neigh != n);
}

/*
 * distance() calculates the distance to the nearest neighbor in the direction
 * passed by the direction variable. This can be used in conjunction with the
 * get_walk_probs() function to weight the probability of walking in a 
 * particular direction based upon the distance to the nearest neighbor.
 */
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

/*
 * get_walk_probs() allows us to weight the probabilities of walking in a
 * particular direction. Setting pleft = pright = pdown = pup is case of
 * equal walk probabilities in all directions.
 */
void
get_walk_probs(int i, int j)
{
	double ptotal;

	/* weight probabilities */
	pleft = 0.25;
	pright = 0.25;
	pdown = 0.25;
	pup = 0.25;

	/* normalize probabilities */
	ptotal = pleft + pright + pdown + pup;
	pleft = pleft/ptotal;
	pright = pright/ptotal;
	pdown = pdown/ptotal;
	pup = pup/ptotal;
}

/*
 * get_direction() selects the monomer located at grid location (i,j), throws
 * a random number, and moves the monomer is a random direction based on the
 * value of the random number thrown.
 */
void
get_direction(int i, int j, int *inew, int *jnew)
{
	double num;	/* random number to determine walk direction */

	/*
	 * We try a direction to walk until we find an unoccupied grid
	 * location to walk the monomer to.
	 */
	do {
		*inew = i;
		*jnew = j;
		num = drand48();
		if(num < pleft) {
			*inew = IMINUS;
		} else if(num < pleft + pright) {
			*inew = IPLUS;
		} else if(num < pleft + pright + pdown) {
			*jnew = JMINUS;
		} else if(num < pleft + pright + pdown + pup) {
			*jnew = JPLUS;
		}
	} while(grid[*inew][*jnew] > 0);
}
