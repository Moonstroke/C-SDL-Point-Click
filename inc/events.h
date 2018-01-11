/**
 * \file events.h
 * \author joH1
 *
 * \version 0.1
 *
 * \brief Functions handling events (mouse motion, click, etc).
 *
 * This file contains the definition and handling of events; mostly mouse events
 * (this is a point and click library, after all).
*/

#ifndef EVENTS_H
#define EVENTS_H


#include <stdbool.h>
#include <stdint.h> /* for uint8_t */
#include <SDL2/SDL_events.h> /* for SDL_Mouse*Event types */

#include "geom.h" /* for Point */



/**
 * \brief Retrieves the \c x and \c y coordinates of the mouse cursor.
 *
 * \return The position of the mouse cursor
 */
Point mousePos(void);



/**
 * \defgroup event_handlers Event handlers typedefs
 * \brief Convenience typedefs that represent handlers functions for different
 *        types of events.
 *
 * \sa SDL_Event
 *
 * \{
 */

/**
 * \brief This type represents handlers for the update of the mouse buttons
 *        states (pressed, or released).
 *
 * \sa SDL_MouseButtonEvent
 */
typedef void (*MouseButtonHandler)(const SDL_MouseButtonEvent*);

/**
 * \brief This type represents handlers for an event constituted by a movement
 *        of the cursor.
 *
 * \sa SDL_MouseMotionEvent
 */
typedef void (*MouseMotionHandler)(const SDL_MouseMotionEvent*);

/**
 * \brief Handler for a mouse wheel scroll (up, down, or sideways for mouse
 *        supporting lateral wheel).
 *
 * \sa SDL_MouseWheelEvent
 */
typedef void (*MouseWheelHandler)(const SDL_MouseWheelEvent*);

/** \} */


/**
 * \brief Defines the procedure to execute when a mouse button is pressed.
 *
 * \param[in] button  The button to watch
 * \param[in] handler The procedure to execute
 *
 * \return \c true if and only if the handler could be set (\a button is valid,
 *         ie. its value is amongst the \c SDL_BUTTON_* values)
 */
bool set_OnMouseDown(uint8_t button, MouseButtonHandler handler);

/**
 * \brief Gets the handler for given mouse button pressed.
 *
 * \param[in] event The event to handle representing mouse pressed
 */
void onMouseDown(const SDL_MouseButtonEvent *event);


/**
 * \brief Defines the procedure to execute when a mouse button is released.
 *
 * \param[in] button  The button to watch
 * \param[in] handler The procedure to execute
 *
 * \return \c true iff the handler could be set (ie. \a button is a valid value)
 */
bool set_OnMouseUp(uint8_t button, MouseButtonHandler handler);

/**
 * \brief Gets the handler for given mouse button released.
 *
 * \param[in] event The mouse release event to handle
 */
void onMouseUp(const SDL_MouseButtonEvent *event);


/**
 * \brief Sets the mouse motion handler
 *
 * \param[in] handler The mouse motion handler
 *
 * \return \c true if the mouse motion handler could be set
 */
bool set_OnMouseMove(MouseMotionHandler handler);

/**
 * \brief Gets the handler for mouse moved.
 *
 * \param[in] event The mouse movement event
 */
void onMouseMove(const SDL_MouseMotionEvent *event);


#endif /* EVENTS_H */
