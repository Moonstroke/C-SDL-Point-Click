#include "math.h"

#include <math.h>


double distance(CPoint p1, CPoint p2) {
	return sqrt(pow(p1->x - p2->x, 2) + pow(p1->x - p2->x, 2));
}
