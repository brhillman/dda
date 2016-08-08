/* output coverage and densities to standard out */

#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

void 
dout(double t, double coverage, double rho_m, double rho_i)
{
        printf("  %-10lf ", F*t);
        printf("%-10lf ", coverage);
	printf("%-10lf ", rho_m);
	printf("%-10lf ", rho_i);
	printf("\n");
}
