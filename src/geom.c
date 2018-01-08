#include "geom.h"

#include <math.h>



extern Point point(int, int);
extern Rect rect(unsigned int, unsigned int, int, int);

extern bool isPointInRect(const Point*, const Rect*);


double distance(const Point p1, const Point p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.x - p2.x, 2));
}
