/* get proper cluster label of the particle with the passed grid label */

#include "globals.h"

int 
proper(int label)
{
	while(point[label].clus < 0) {
		label = -point[label].clus;
	}
	return label;
}
