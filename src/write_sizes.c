/* write_sizes() outputs the sizes of each island on the grid. 
 * All it does is search
 * the one dimensional cluster array and output all the proper labels, which
 * hold the island size.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "globals.h"

extern void append_name(char filename[20], FILE *fp);

void 
write_sizes(void)
{
        int n;
	char filename[20];
	FILE *fp;

	strcpy(filename, "sizes.1.data");
	append_name(filename, fp);

        if((fp = fopen(filename, "w")) == NULL) {
                printf("Cannot open data file %s.\n", filename);
                exit(1);
        }
	/* fheader is commented out because my binner and scaling function
	 * routines cannot currently deal with non-integer characters in the
	 * file.
	 */
	/* fheader(fp,coverage); */

	for(n=0; n<L*L; n++) {
		if(point[n].clus > 0) fprintf(fp, "%d\n", point[n].clus);
	}
        fclose(fp);
}
