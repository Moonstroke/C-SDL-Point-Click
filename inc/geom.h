/**
 * \file geom.h
 * \author joH1
 *
 * \version 0.1
 *
 * \brief Functions about mathematical and geometrical calculations or related.
 *
 * This file contains every function used in the project that involves
 * mathematical calculations.
*/

#ifndef GEOM_H
#define GEOM_H


#include <stdbool.h>


/**
 * \brief A geometric point, in cartesian coordinates
 */
typedef struct point {
	int x, /**< The abcsissa of the point */
	    y; /**< The ordinate of the point */
} Point;

/**
 * \brief A geometric rectangle.
 */
typedef struct rect {
	unsigned int w, /**< The width of the rectangle */
	             h; /**< The height of the rectangle */
	Point pos;      /**< The position of the rectangle */
} Rect;


/**
 \brief The maximum distance at which a mouseup following a mousedown is
 *      considered a mouse click.
 */
#define MAX_CLICK_DISTANCE 0.1

/**
 * \brief Calculates the distance between two geometric points.
 *
 * \param[in] p1 A -- valid -- point in the plane
 * \param[in] p2 Another point in the plane
 *
 * \return The quadratic distance between the two points
 */
double distance(Point p1, Point p2);

/**
 * \brief Constructs a geometric point, in cartesian coordinates.
 *
 * \param[in] x The abscissa of the point
 * \param[in] y The ordinate of the point
 *
 * \return A Point structure element
 *
 * \sa Point
 */
inline Point point(const int x, const int y) {
	return (Point){.x = x, .y = y};
}

/**
 * \brief Constructs a geometric rectangle.
 *
 * \param[in] w The width of the rectangle
 * \param[in] h The height of the rectangle
 * \param[in] x The abscissa of the rectangle
 * \param[in] y The ordinate of the rectangle
 *
 * \return A Rect structure object
 *
 * \sa Rect
 */
inline Rect rect(const unsigned int w, const unsigned int h, const int x, const int y) {
	return (Rect){ .w = w, .h = h, .pos = point(x, y)};
}

/**
 * \brief Determines whether a point belongs inside the bounds of a rectangle.
 *
 * \param[in] pt The point
 * \param[in] rct  The rectangle
 *
 * \return \c true iff the point coordinates are within the bounds of the
 *         rectangle's coordinates
 */
inline bool isPointInRect(const Point pt, const Rect *const rct) {
	return (rct->pos.x <= pt.x && pt.x <= (rct->pos.x + (signed)rct->w)) &&
	       (rct->pos.y <= pt.y && pt.y <= (rct->pos.y + (signed)rct->h));
}

#endif /* GEOM_H */
