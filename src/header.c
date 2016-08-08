/* 
 * header() simply outputs a header to stdout which contains the parameters
 * of the simulation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "globals.h"

void 
header(void)
{
	int n;

        printf("# %-30s %d\n", "grid size L", L);
        printf("# %-30s %e\n", "temperature T", T);
        printf("# %-30s %e\n", "activation energy E0", E0);
        printf("# %-30s %e\n", "activation energy E1", E1);
        printf("# %-30s %e\n", "constant D_0", D_0);
        printf("# %-30s %e\n", "diffusion constant D", D);
        printf("# %-30s %e\n", "diffusion constant D1", D1);
        printf("# %-30s %e\n", "flux constant F", F);
        printf("# %-30s %e\n", "activation energy E1-E0", E1-E0);
        printf("# %-30s %e\n", "R = D/F", R);
        printf("# %-30s %d\n", "walk prob dependence", DEPEND);
        printf("# \n");
	printf("# NOTE: in the table that follows, cov is coverage,\n");
	printf("# rho is monomer density and rhoi is island density.\n");
	printf("# \n");
	printf("# ");
        printf("%-10s ", "F*t");
        printf("%-10s ", "cov");
        printf("%-10s ", "rho");
        printf("%-10s ", "rhoi");
	printf("\n");
	printf("# ");
	for(n = 0; n < 4*10; n++) printf("-");
	printf("\n");
}
