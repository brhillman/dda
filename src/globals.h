/* grid parameters */
#define L 	100			/* grid size */
#define MAX_COV	0.50			/* stopping coverage */

/* constants and growth parameters */
#define K	8.6173423E-5		/* Boltzmann constant [eV/K] */
#define T	300.0			/* temperature [K] */
#define E0	0.0			/* activiation for 0-neighbor */
#define E1	1.00			/* activation for 1-neighbor */
#define D_0	1.0			/* diffusion constant */
#define D	(D_0*exp(-E0/(K*T)))	/* diffusion rate constant */
#define D1	(D_0*exp(-E1/(K*T)))	/* 1-neighbor rate constant */
#define F	(1.0e-5)		/* flux rate constant */
#define R	(D/F)			/* diffusion to flux ratio */

/* logical flags (1 => do, 0 => do not) */
#define DO_WRITE_SIZES 0   /* 1 => output size distributions */
#define DO_WRITE_MORPH 0   /* 1 => output grid morphology */
#define DO_WRITE_DEN 0     /* 1 => output densities */

/* walk probability dependence on distance to nearest neighbor */
#define DEPEND 0			/* not used right now */

/* intervals at which to write data */
#define COV_STEP 0.10

/* deposition probability distribution function */
#define DEP_PROB(x)	((x == 1) ? 1.0 : 0.0)

/* periodic boundary conditions */
#define IMINUS 	(((i-1) >= 0) ? (i-1) : (L-1))
#define JMINUS 	(((j-1) >= 0) ? (j-1) : (L-1))
#define IPLUS  	(((i+1) < L) ? (i+1) : 0)
#define JPLUS  	(((j+1) < L) ? (j+1) : 0)

/* direction definitions for convenience */
#define LEFT 1
#define RIGHT 2
#define DOWN 3
#define UP 4

/* define process numbers for grow routine */
#define DROP 	1
#define DIFF 	2
#define DIFF1 	3

/* structures */
typedef struct grid_point grid_point;

struct grid_point {
	int x;
	int y;
	int neigh;
	int clus;
};

/* global variables */
extern int grid[L][L];		/* grid on which islands grow */
extern grid_point point[L*L];	/* information about points */
extern int drop_count;		/* total number of monomers on grid */
