/* write_morph() outputs all the points that correspond to occupied grid sites.
 * Plotting the resulting datafile then shows the island morphology.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"

extern void fheader(FILE *fp, double t, double coverage);
extern void append_name(char filename[20], FILE *fp);

void 
write_morph(double t, double coverage)
{
        int i;
        int j;
	char filename[20];
	FILE *fp;

	strcpy(filename, "morph.1.data");
	append_name(filename, fp);
        if((fp = fopen(filename, "w")) == NULL) {
                printf("Cannot open data file %s.\n", filename);
                exit(1);
        }
        fheader(fp,t,coverage);
        fprintf(fp, "# i, j\n");

        for(i=0; i<L; i++) {
                for(j=0; j<L; j++) {
                        if(grid[i][j] != 0) fprintf(fp, "  %d, %d\n", i, j);
                }
        }
        fclose(fp);
}
