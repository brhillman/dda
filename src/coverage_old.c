/* 
 * This is the routine that does the actual growing of the clusters. Each time
 * through the loop, the probability of each elementary process is calculated
 * based on the process rates and the number of ways of the process occuring.
 * A process is then chosen randomly, weighted by these probabilities, and a 
 * particle is randomly selected to execute the process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "globals.h"

extern int monomers(int n);
extern int islands(void);
extern void dout(double coverage, double rho_m, double rho_i);
extern void deposit(void);
extern void walk(int n);

static double sum;		/* sum over processes */
static double p_drop;		/* probability of dropping a monomer */
static double p_diff;		/* probability of diffusing a monomer */
static double p_diff1;		/* prob of diff monomer with 1 neighbor */

void calc_prob(double rho, double rho1);
void choose_process(double cov, double rho, double rho1, int mon, int mon1);

double 
coverage(double cov_max, double *tp)
{
	int mon;		/* number of monomers */
	int mon1;		/* number of monomers with 1 neighbor */
	double cov;		/* coverage defined as Ft */
	double rho;		/* monomer density */
	double rho1;		/* density of monomers with one neighbor */
	double dt;		/* time step */

	cov = 1.0*F*(*tp);
        for(dt = 0; cov < 1.0*cov_max; (*tp) += dt) {
                cov = (1.0*F*(*tp));
		mon = monomers(0);
		mon1 = monomers(1); 
		rho = 1.0*mon/(L*L);
		rho1 = 1.0*mon1/(L*L);

		calc_prob(rho,rho1);
		choose_process(cov,rho,rho1,mon,mon1);

		dt = 1/sum;
        }
	return cov;
}

void
calc_prob(double rho, double rho1)
{
	double drop;		/* flux process (rate)(ways) */
	double diff;		/* diffusion process (rate)(ways) */
	double diff1;		/* 1 neighbor diffusion process (rate)(ways) */

	drop = F*(L*L);
	diff = D*(rho*L*L);
	diff1 = D1*(rho1*L*L);
	sum = drop + diff + diff1;

	p_drop = drop/sum;
	p_diff = diff/sum;
	p_diff1 = diff1/sum;
}

void
choose_process(double cov, double rho, double rho1, int mon, int mon1)
{
	double p;		/* random number to choose a process */

	p = drand48();
	if(p < p_drop) {
		dout(cov,rho,1.0*islands()/(L*L));
		deposit();
	} else if(p < (p_drop + p_diff)) {
		if(mon > 0) walk(0);
	} else {
		if(mon1 > 0) walk(1);
	}
}
