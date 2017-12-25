#include "math.h"


#include <math.h>

extern Point point(int x, int y);

extern Rect rect(int x, int y, unsigned int w, unsigned int h);


double distance(const Point p1, const Point p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.x - p2.x, 2));
}
