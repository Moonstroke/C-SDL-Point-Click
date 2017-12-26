/**
 * \file events.h
 * \author joH1
 *
 * This file contains the definition and handling of events; mostly mouse events
 * (this is a point and click library, after all).
*/

#ifndef EVENTS_H
#define EVENTS_H


#include <stdbool.h>

#include "types.h"


// TODO add mouse click (move from main)

/**
 * \brief Retrieves the x and y coordinates of the mouse cursor.
 *
 * \return The position of the mouse cursor
 */
Point mousepos(void);


/* ## Mouse events handlers ## */

/**
 * \brief Convenience typedef that represents mouse event handlers.
 *
 * A mouse event handler is a procedure with a single argument, a 2D vector --
 * usually the mouse position on screen.
 */
typedef void (*mousehandler)(Point);

/**
 * \brief Defines the procedure to execute when a mouse button is pressed.
 *
 * \param[in] button  The button to watch
 * \param[in] handler The procedure to execute
 *
 * \return \c true if the handler could be set (ie. button is a valid value)
 *
 * \sa SDL_MouseButtonEvent
 */
bool set_onmousedown(uint8_t button, mousehandler handler);

/**
 * \brief Gets the handler for given mouse button pressed.
 *
 * \param[in] button The button to get the handler back
 *
 * \return The handler for given mouse button
 */
mousehandler onmousedown(uint8_t button);


/**
 * \brief Defines the procedure to execute when a mouse button is released.
 *
 * \param[in] button  The button to watch
 * \param[in] handler The procedure to execute
 *
 * \return \c true if the handler could be set (ie. \c button is a valid value)
 *
 * \sa SDL_MouseButtonEvent
 */
bool set_onmouseup(uint8_t button, mousehandler handler);

/**
 * \brief Gets the handler for given mouse button released.
 *
 * \param[in] button The button to get the handler back
 *
 * \return The handler for given mouse button
 */
mousehandler onmouseup(uint8_t button);

/**
 * \brief Sets the mouse motion handler
 *
 * \param[in] handler The mouse motion handler
 *
 * \return \c true if the mouse motion handler could be set
 */
bool set_onmousemove(mousehandler handler);

/**
 * \brief Gets the handler for mouse moved.
 *
 * \return The handler for given mouse button
 */
mousehandler onmousemove(void);


/* ## Keyboard events handlers ## */
/* not used for now
typedef void (*keyhandler)(const SDL_Keymod);


int set_onkeydown(const SDL_Keycode key, keyhandler handler);

keyhandler onkeydown(const SDL_Keycode key);


int set_onkeyup(const SDL_Keycode key, keyhandler handler);

keyhandler onkeyup(const SDL_Keycode key);
*/


#endif // EVENTS_H
