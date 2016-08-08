/* 
 * deposit() selects a size of cluster to deposit and drops that cluster onto
 * the grid. The size is selected based on the probability distribution
 * function DEP_PROB(x), which is a macro defined in globals.h.
 */

double sum(int a, int b);

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

extern void new(int drop_size);

void 
deposit(void)
{
	int i;			/* loop index */
	double num;		/* random number */

	num = drand48();
	for(i = 1; ((num < sum(1,i-1)) || (num >= sum(1,i))); i++);
	new(i);
}


/*
 * sum() is a useful utility for summing the deposition probability
 * distribution DEP_PROB(x) over a range of x 
 */
double 
sum(int a, int b)
{
	int i;			/* loop index */
	double sum1;		/* intermediate sum */

	sum1 = 0.0;
	for(i = a; i <= b; i++) sum1 += DEP_PROB(i);

	return sum1;
}
