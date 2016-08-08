#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "globals.h"

extern void seed(void);
extern void initialize(int array[L][L]);
extern void header(void);
extern void grow(double *t, double *cov, double cov_stop);
extern void write_morph(double t, double coverage);
extern void write_sizes(void);

int grid[L][L];		/* grid on which islands grow */
int drop_count;		/* total number of monomers deposited onto grid */
grid_point point[L*L];

void init_globals(void);

int main(void)
{
	time_t t1;	/* program start time from system time */
	time_t t2;	/* program end time from system time */
	double c;	/* coverages at which we output data */
	double t;	/* time variable */
	double cov;	/* total grid coverage */

	/* get program start time */
	(void) time(&t1);

	if(DO_WRITE_DEN) header();	/* output parameters to stdout */
	seed();		               /* seed random number generator */
	init_globals();	         /* initialize our global variables */

	/*
	 * Here we deposit monomers and grow the islands. We output the 
	 * island sizes (and optionally the grid morphology) at intervals 
	 * defined by COV_STEP.
	 */
	t = 0.0;
	cov = 0.0;
	for(c = COV_STEP; cov < MAX_COV; c += COV_STEP) {
		grow(&t,&cov,c);
		if(DO_WRITE_SIZES == 1) write_sizes();
		if(DO_WRITE_MORPH == 1) write_morph(t,cov);
	}

	/* get program end time and display run time */
	(void) time(&t2);
	printf("# run time: %d seconds\n", (int) (t2-t1));

	exit(0);
}

void 
init_globals(void)
{
	int n;

	initialize(grid);
	drop_count = 0;
	for(n=0; n<L*L; n++) {
		point[n].clus = 0;
		point[n].neigh = 0;
		point[n].x = 0;
		point[n].y = 0;
	}
}
