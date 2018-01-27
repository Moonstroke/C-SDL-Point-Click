/**
 * \file mouse.h
 * \author joH1
 *
 * \version 0.1
 *
 * \brief Mouse data and events module.
 *
 * This file contains the definition of mouse data functions, and handling of
 * mouse events (motion, click...).
*/

#ifndef MOUSE_H
#define MOUSE_H

#include <stdint.h> /* for uint8_t */
#include <SDL2/SDL_events.h> /* for SDL_Mouse*Event types */

#include "geom.h" /* for Point */



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
typedef void (MouseButtonHandler)(const SDL_MouseButtonEvent*);

/**
 * \brief This type represents handlers for an event constituted by a movement
 *        of the cursor.
 *
 * \sa SDL_MouseMotionEvent
 */
typedef void (MouseMotionHandler)(const SDL_MouseMotionEvent*);

/**
 * \brief Handler for a mouse wheel scroll (up, down, or sideways for mouse
 *        supporting lateral wheel).
 *
 * \sa SDL_MouseWheelEvent
 */
typedef void (MouseWheelHandler)(const SDL_MouseWheelEvent*);

/** \} */


/**
 * \brief Retrieves the \c x and \c y coordinates of the mouse cursor.
 *
 * \return The position of the mouse cursor
 */
Point mousePos(void);

/**
 * \brief Retrieves the variations of the mouse position since last event.
 *
 * \return The difference in the mouse position
 */
Point mousePosDelta(void);


typedef enum {
	MOUSE_BUTTON_NONE    = 0x0,
	MOUSE_BUTTON_LEFT    = SDL_BUTTON_LEFT,
	MOUSE_BUTTON_MIDDLE  = SDL_BUTTON_MIDDLE,
	MOUSE_BUTTON_RIGHT   = SDL_BUTTON_RIGHT,
	MOUSE_BUTTON_EXTRA_1 = SDL_BUTTON_X1,
	MOUSE_BUTTON_EXTRA_2 = SDL_BUTTON_X2,
} MouseButton;

MouseButton mouseUpdate(void);


/**
 * \brief Defines the procedure to execute when a mouse button is pressed.
 *
 * \param[in] button  The button to watch
 * \param[in] handler The procedure to execute
 *
 * \return \c true if and only if the handler could be set (\a button is valid,
 *         ie. its value is amongst the \c SDL_BUTTON_* values)
 */
bool onMouseDown(uint8_t button, MouseButtonHandler *handler);

/**
 * \brief Gets the handler for given mouse button pressed.
 *
 * \param[in] event The event to handle representing mouse pressed
 */
void mouseDown(const SDL_MouseButtonEvent *event);


/**
 * \brief Defines the procedure to execute when a mouse button is released.
 *
 * \param[in] button  The button to watch
 * \param[in] handler The procedure to execute
 *
 * \return \c true iff the handler could be set (ie. \a button is a valid value)
 */
bool onMouseUp(uint8_t button, MouseButtonHandler *handler);

/**
 * \brief Gets the handler for given mouse button released.
 *
 * \param[in] event The mouse release event to handle
 */
void mouseUp(const SDL_MouseButtonEvent *event);


/**
 * \brief Defines the procedure to execute when a mouse button is clicked.
 *
 * A mouse click correspond to a pressure and release immediately after, without
 * motion (or very few pixels, in case of involuntary offset)
 *
 * \param[in] button  The button to watch
 * \param[in] handler The procedure to execute
 *
 * \return \c true iff the handler could be set (ie. \a button is a valid value)
 */
bool onMouseClick(uint8_t button, MouseButtonHandler *handler);

/**
 * \brief Gets the handler for given mouse button released.
 *
 * \param[in] event The mouse button event
 */
void mouseClick(const SDL_MouseButtonEvent *event);


/**
 * \brief Sets the mouse motion handler
 *
 * \param[in] handler The mouse motion handler
 *
 * \return \c true if the mouse motion handler could be set
 */
void onMouseMove(MouseMotionHandler *handler);

/**
 * \brief Gets the handler for mouse moved.
 *
 * \param[in] event The mouse movement event
 */
void mouseMove(const SDL_MouseMotionEvent *event);


#endif /* MOUSE_H */
