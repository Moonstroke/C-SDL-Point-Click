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
 *
 * A mouse event handler is a procedure with a single argument, a 2D vector --
 * usually the mouse position on screen.
 */
typedef void (*mousehandler)(Point);

/**
 * \brief Defines the procedure to execute when a mouse button is pressed.
 *
 * \param[in] button  the button to watch
 * \param[in] handler the procedure to execute
 *
 * \return TRUE if the handler could be set (ie. button is a valid value)
 *
 * \sa SDL_MouseButtonEvent
 */
bool set_onmousedown(uint8_t button, mousehandler handler);

/**
 * \brief Gets the handler for given mouse button pressed.
 *
 * \param[in] button the button to get the handler back
 *
 * \return the handler for given mouse button
 */
mousehandler onmousedown(uint8_t button);


/**
 * \brief Defines the procedure to execute when a mouse button is released.
 *
 * \param[in] button  the button to watch
 * \param[in] handler the procedure to execute
 *
 * \return TRUE if the handler could be set (ie. \c button is a valid value)
 *
 * \sa SDL_MouseButtonEvent
 */
bool set_onmouseup(uint8_t button, mousehandler handler);

/**
 * \brief Gets the handler for given mouse button released.
 *
 * \param[in] button the button to get the handler back
 *
 * \return the handler for given mouse button
 */
mousehandler onmouseup(uint8_t button);

/**
 * \brief Sets the mouse motion handler
 *
 * \param[in] handler the mouse motion handler
 *
 * \return TRUE if the mouse motion handler could be set
 */
bool set_onmousemove(mousehandler handler);

/**
 * \brief Gets the handler for given mouse button released.
 *
 * \param[in] button the button to get the handler back
 *
 * \return the handler for given mouse button
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


#endif /* EVENTS_H */
