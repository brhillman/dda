/* 
 * This is the routine that does the actual growing of the clusters. 
 * The algorithm is based on Pablo Jensen's paper. Each time
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
extern void dout(double t, double coverage, double rho_m, double rho_i);
extern void deposit(void);
extern void walk(int n);
extern void display(int grid[L][L]);

static double p_drop;		/* probability of dropping a monomer */
static double p_diff;		/* probability of diffusing a monomer */
static double p_diff1;		/* prob of diff monomer with 1 neighbor */

void calc_probs(double rho, double rho1, double *dt);
void execute_process(int mon, int mon1, int *process);
int proccess(int mon, int mon1);

void
grow(double *t, double *cov, double cov_stop)
{
	int mon;		/* number of monomers */
	int mon1;		/* number of monomers with 1 neighbor */
	double rho;		/* monomer density */
	double rho1;		/* density of monomers with one neighbor */
	double rhoi;		/* island density */
	double dt;		/* time step */
	int process;		/* process executed each iteration */

	/*
	 * We grow the islands until we reach the maximum coverage passed by
	 * the cov_stop variable. cov is the coverage at the current time
	 * step. dt is calculated at each iteration based upon which process
	 * is executed.
	 */
   for(dt = 0.0; (*cov) < cov_stop; (*t) += dt) {
      mon = monomers(0);	/* count monomers */
      mon1 = monomers(1); 	/* count monomers with 1 neighbor */
      rho = 1.0*mon/(L*L);	/* calculate monomer density */
      rho1 = 1.0*mon1/(L*L);	/* calculate 1-neighbor density */

      /* calculate process probabilities */
      calc_probs(rho,rho1,&dt);

       /* select and execute a process */
       execute_process(mon,mon1,&process);

       /* only count islands/output density when fluxing */
      if(process == DROP) {
         (*cov) = 1.0*drop_count/(L*L);
         rho = 1.0*monomers(0)/(L*L);
         rhoi = 1.0*islands()/(L*L);
         if(DO_WRITE_DEN) dout((*t) + dt,(*cov),rho,rhoi);
      }

      /* uncomment next line to write a movie to stdout */
      /* display(grid); */
   }
}

/*
 * calc_probs() calculates the probability of executing each process 
 * considered, in this case deposition, diffusion of monomers, and diffusion 
 * of monomers with 1 neighbor.
 */
void
calc_probs(double rho, double rho1, double *dt)
{
	double drop;		/* flux process (rate)(ways) */
	double diff;		/* diffusion process (rate)(ways) */
	double diff1;		/* 1 neighbor diffusion process (rate)(ways) */
	double sum;		/* sum over processes */

	drop = F*(L*L);	
	diff = D*(rho*L*L);
	diff1 = D1*(rho1*L*L);
	sum = drop + diff + diff1;

	p_drop = drop/sum;	/* probability of deposition */
	p_diff = diff/sum;	/* probability of monomer diffusion */
	p_diff1 = diff1/sum;	/* probability of 1-neighbor diffusion */

	*dt = 1.0/sum;		/* calculated time step */
}

/*
 * process() selects and executes a process based on the probabilities of
 * executing each process. A random number is thrown, and a process is
 * selected based on its value and the probabilities.
 */
void
execute_process(int mon, int mon1, int *process)
{
	double p;		/* random number to choose a process */

	p = drand48();
	if(p < p_drop) {
		deposit();
		*process = DROP;
	} else if((p < (p_drop + p_diff)) && (mon > 0)) {
		walk(0);
		*process = DIFF;
	} else if(mon1 > 0) {
		walk(1);
		*process = DIFF1;
	} else *process= 0; 
}
