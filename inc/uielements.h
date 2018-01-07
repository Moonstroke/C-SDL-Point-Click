#ifndef UIELEMENTS_H
#define UIELEMENTS_H


#include "font.h"
#include "geom.h"
#include "sprite.h"



/**
 * \defgroup uistyle_funcs "UI Style functions"
 * \{
 */

/**
 * \brief Sets the font for the text of the user interface elements.
 *
 * \param[in] font The font
 */
void setUIFont(Font *font);

/**
 * \brief Retrieves the global interface font.
 *
 * \return The font used by the user interface
 */
Font *getUIFont(void);

/**
 * \brief Sets the text color for the user interface elements.
 *
 * \param[in] textColor The color of the text of the UI elements
 */
void setUITextColor(const Color *textColor);

/**
 * \brief Retrieves the text color for interface elements.
 *
 * \return The color of the text of UI elements
 */
Color *getUITextColor(void);

/**
 * \brief Sets the background color to be used for the UI elements to display.
 *
 * \param[in] bgColor The background color
 */
void setUIBgColor(const Color *bgColor);

/**
 * \brief Retrieves the background color for interface elements.
 *
 * \return The color of the background of UI elements
 */
Color *getUIBgColor(void);

/** \} */


/**
 * \brief Constructs a non-interactible user interface element.
 *
 * \param[in] text   The text of the element
 * \param[in] pos    The position to put the element at
 * \param[in] window The application window
 *
 * \return A label of given text at given pos.
 */
Sprite *label(str text, Point pos, Window *window);

/**
 * \brief Constructs an interactible user interface element.
 *
 * \param[in] text   The text of the element
 * \param[in] pos    The position to put the element at
 * \param[in] action The action to perform when sollicited
 * \param[in] window The application window
 *
 * \return A button of given text at given pos, which executes given action when
 *         it is interacted with.
 */
Sprite *button(str text, Point pos, void (*action)(void), Window *window);


#endif /* UIELEMENTS_H */
