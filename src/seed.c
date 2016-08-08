/* seed() seeds the random number generator drand48() with the system time. */

#include <stdlib.h>
#include <time.h>

void 
seed(void)
{
	int stime;
	long ltime;

	ltime = time(NULL);
	stime = (unsigned) ltime/2;
	srand48(stime);
}
