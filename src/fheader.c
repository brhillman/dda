/* 
 * fheader() simply outputs a header to fp which contains the parameters
 * of the simulation.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "globals.h"

void 
fheader(FILE *fp, double t, double coverage)
{
        fprintf(fp,"# %-30s %d\n", "grid size L", L);
        fprintf(fp,"# %-30s %e\n", "temperature T", T);
        fprintf(fp,"# %-30s %e\n", "activation energy E0", E0);
        fprintf(fp,"# %-30s %e\n", "activation energy E1", E1);
        fprintf(fp,"# %-30s %e\n", "constant D_0", D_0);
        fprintf(fp,"# %-30s %e\n", "diffusion constant D", D);
        fprintf(fp,"# %-30s %e\n", "diffusion constant D1", D1);
        fprintf(fp,"# %-30s %e\n", "flux constant F", F);
        fprintf(fp,"# %-30s %e\n", "activation energy E1-E0", E1-E0);
        fprintf(fp,"# %-30s %e\n", "R = D/F", R);
        fprintf(fp,"# %-30s %d\n", "walk prob dependence", DEPEND);
        fprintf(fp,"# %-30s %lf\n", "F*t", F*t);
        fprintf(fp,"# %-30s %lf\n", "coverage", coverage);
        fprintf(fp,"# \n");
}
