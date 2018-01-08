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


bool uielementNeedsUpdate(const UIElement *element);

void updateUIElement(UIElement *element, Window *window);

bool isPointInUIElement(const UIElement *element, Point pos);


void btnHover(UIElement *button);

void btnDown(UIElement *button);

void btnUp(UIElement *button);

void btnClick(const UIElement *button);

#endif /* UIELEMENTS_H */
