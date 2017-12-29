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


#include <SDL2/SDL_rect.h>



typedef SDL_Point Point; /**< A geometric point, in cartesian coordinates */

typedef SDL_Rect Rect; /**< A geometric rectangle */


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
 * \param[in] x The abscissa of the rectangle
 * \param[in] y The ordinate of the rectangle
 * \param[in] w The width of the rectangle
 * \param[in] h The height of the rectangle
 *
 * \return A Rect structure object
 *
 * \sa Rect
 */
inline Rect rect(const int x, const int y, const unsigned int w, const unsigned int h) {
	return (Rect){.x = x, .y = y, .w = w, .h = h};
}
#endif // GEOM_H
