#include <stdio.h>
#include <stdlib.h>

#include "globals.h"

void display(int array[L][L])
{
        int i;
        int j;
	system("clear");
        printf("\n");
        for(j=L-1; j>=0; j--) {
                printf("%2d|", j);
                for(i=0; i<L; i++) {
                        if(array[i][j]) printf("%3d", array[i][j]);
                        else printf("%3s", " ");
                }
                printf("\n");
        }
        printf("%3s", " ");
        for(i=0; i<L; i++) {
                printf("%3s", "-");
        }
        printf("\n");
        printf("%3s", " ");
        for(i=0; i<L; i++) {
                printf("%3d", i);
        }
        printf("\n");
}
