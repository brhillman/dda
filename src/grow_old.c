/* 
 * This routine exists to call coverage() to grow islands for certain
 * lengths of time and call morph() and sizes() to output morphology
 * and size data at the ends of these time periods.
 */

#include <stdio.h>

#include "globals.h"

extern double coverage(double cov_max, double *tp);
extern void morph(double coverage);
extern void sizes(double coverage);

void
grow(void)
{
	double cov;	/* defined as F*t but subject to change */
	double c;	/* coverages at which we output data */
	double t;	/* time variable */
	double *tp;	/* pointer to time variable */

	t = 0;
	tp = &t;

	cov = 0.0;
	for(c = 0.05; cov < 1.0*MAX_COV; c += 0.05) {
		cov = coverage(c,tp); 
		morph(cov); 
		sizes(cov); 
	}
}
