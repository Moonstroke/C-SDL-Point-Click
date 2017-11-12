#ifndef EVENTS_H
#define EVENTS_H


#include <SDL2/SDL_events.h>
#include <stdbool.h>

#include "types.h"



/**
 * \brief Retrieves the x and y coordinates of the mouse cursor.
 */
Point mousepos(void);


/* ## Mouse events handlers ## */

/**
 * \brief Convenience typedef that represents mouse event handlers.
 * A mouse event handler is a procedure with a single argument, a 2D vector --
 * usually the mouse position on screen.
 */
typedef void (*mousehandler)(CPoint);

/**
 * \brief Defines the procedure to execute when a mouse button is pressed.
 *
 * \param button  the button to watch
 * \param handler the procedure to execute
 *
 * \return TRUE if the handler could be set (button is a valid value)
 *
 * \sa SDL_MouseButtonEvent
 */
bool set_onmousedown(Uint8 button, mousehandler handler);

/**
 * \brief Gets the handler for given mouse button pressed.
 *
 * \param button the button to get the handler back
 *
 * \return the handler for given mouse button
 */
mousehandler onmousedown(Uint8 button);


/**
 * \brief Defines the procedure to execute when a mouse button is released.
 *
 * \param button  the button to watch
 * \param handler the procedure to execute
 *
 * \return TRUE if the handler could be set (button is a valid value)
 *
 * \sa SDL_MouseButtonEvent
 */
bool set_onmouseup(Uint8 button, mousehandler handler);

/**
 * \brief Gets the handler for given mouse button released.
 *
 * \param button the button to get the handler back
 *
 * \return the handler for given mouse button
 */
mousehandler onmouseup(Uint8 button);


bool set_onmousemove(mousehandler handler);

mousehandler onmousemove(void);


/* ## Keyboard events handlers ## */
/* not used for now
typedef void (*keyhandler)(const SDL_Keymod);


int set_onkeydown(const SDL_Keycode key, keyhandler handler);

keyhandler onkeydown(const SDL_Keycode key);


int set_onkeyup(const SDL_Keycode key, keyhandler handler);

keyhandler onkeyup(const SDL_Keycode key);
*/


#endif /* EVENTS_H */
