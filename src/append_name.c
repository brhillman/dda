/* increment data filename */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void 
append_name(char filename[20], FILE *fp)
{
        int n;
        char num[10];
        
        for(n=1; (fp = fopen(filename, "r")) != NULL; n++) {
                sprintf(num, "%d", n);
                strtok(filename, ".");
                strcat(filename, ".");
		strcat(filename, num);
                strcat(filename, ".data");
		fclose(fp);
        }
}
