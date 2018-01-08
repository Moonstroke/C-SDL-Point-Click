/**
 * \file "uielements.h"
 * \author joH1
 *
 * \version 0.1
 *
 * \brief Defines user interface style and elements.
 *
 * This file implements UI elements, like labels and buttons (that's all for
 * now).
 * It also provides functionsto define a standard style (font and colors) used
 * by all the UI elements to give a homogeneous feel for the interface.
 */

#ifndef UIELEMENTS_H
#define UIELEMENTS_H


#include "colors.h" /*for Color */
#include "font.h"
#include "geom.h" /* for Rect and Point */


#include <stdbool.h>



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
 * \brief An element of the user interface.
 */
typedef struct uielement UIElement;


#include "window.h" /* for Window type and functions */



/**
 * \brief Constructs a non-interactible user interface element.
 *
 * \param[in] text   The text of the element
 * \param[in] pos    The position to put the element at
 *
 * \return A label of given text at given pos.
 */
UIElement *label(str text, Point pos);

/**
 * \brief Constructs an interactible user interface element.
 *
 * \param[in] text   The text of the element
 * \param[in] pos    The position to put the element at
 * \param[in] action The action to perform when sollicited
 *
 * \return A button of given text at given pos, which executes given action when
 *         it is interacted with.
 */
UIElement *button(str text, Point pos, void (*action)(void));

/**
 * \brief Deallocates an UI element.
 *
 * \param[in] element The element to free
 */
void freeUIElement(UIElement *element);


/**
 * \brief Checks whether the element needs to be redrawn on the screen.
 *
 * \param[in] element The element
 *
 * \return \c true iff the elements needs to be updated
 */
bool uielementNeedsUpdate(const UIElement *element);

/**
 * \brief Updates the element on display.
 *
 * \param[in,out] element The element
 * \param[in,out] window  The window to draw the element to
 */
void updateUIElement(UIElement *element, Window *window);

/**
 * \brief Calculates if the UI element contains a point, geometrically.
 *
 * \param[in] element The element
 * \param[in] point   The point
 *
 * \return \c true iff the point resides inside the bounds of a UI element
 */
bool isPointInUIElement(const UIElement *element, Point point);


/**
 * \brief Handles a mouse hover event over a button.
 *
 * \param[in,out] button The button
 */
void btnHover(UIElement *button);


/**
 * \brief Handles a mouse pression over a button.
 *
 * \param[in,out] button The button
 */
void btnDown(UIElement *button);


/**
 * \brief Handles a mouse release over a button.
 *
 * \param[in,out] button The button
 */
void btnUp(UIElement *button);


/**
 * \brief Handles a mouse click event on the given button.
 *
 * \param[in,out] button The button
 */
void btnClick(const UIElement *button);

#endif /* UIELEMENTS_H */
