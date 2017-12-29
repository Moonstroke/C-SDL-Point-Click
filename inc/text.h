/**
 * \file "text.h"
 * \author joH1
 *
 * \version 0.1
 *
 * \brief Functions handling the rendering of a text.
 *
 * This file contains functions that construct textures from a string, in the
 * given font, drawn in given color (over optional background of given color)
 * for the given window.
 *
 * The encoding used is UTF-8, so any ASCII string also works.
 *
 * Each function relates to a txt rendering type of the SDL module \c SDL_ttf,
 * which are:
 * - \e solid, The text is rendered without transparency or smoothing
 *   (fast, this is related to \c rendertext_fast)
 * - \e shaded, the text is rendered with antialiasing, but over an opaque
 *   background (slower, this relates to\c rendertext_bg)
 * - \e blended, the text is antialiased and blended with the underlying texture
 *   (slowest, related to \c rendertext_hq)
 *
 * \sa Texture
 */

#ifndef TEXT_H
#define TEXT_H


#include <SDL2/SDL_ttf.h>

#include "colors.h"
#include "texture.h"
#include "types.h"
#include "window.h"



/** A redefinition of the font type. */
typedef TTF_Font Font;


typedef enum {
	TEXTRENDER_FAST,
	TEXTRENDER_OPAQUEBG,
	TEXTRENDER_SMOOTH
} TextRenderType;


/**
 * \brief The structure holding the data for a text to render.
 */
typedef struct text Text;


/**
 * \brief Instantiates a new text for rendering.
 *
 * \param[in] string     The string data of the text
 * \param[in] font       The font to render the text in
 * \param[in] text_color The color of the text
 *
 * \return A text for rendering, of given textual value, to be rendered in given
 *         font and color
 */
Text *newtext(str string, Font *font, Color text_color, TextRenderType type);

/**
 * \brief Deallocates the memory used by a text.
 *
 * \param[in,out] self The text to free
 */
void freetext(Text *self);


/**
 * \brief Updates the string value of the Text.
 *
 * \param[in,out] self   The text
 * \param[in]     string The string value to set
 */
void settextstring(Text *self, str string);

/**
 * \brief Updates the text color of the Text.
 *
 * \param[in,out] self  The text
 * \param[in]     color The text color
 */
void settextcolor(Text *self, Color color);


/**
 * \brief Updates the background color of the Text.
 *
 * \param[in,out] self     The text
 * \param[in]     bg_color The color to set
 *
 * \note The background color is only used when rendering with an opaque
 *       background.
 *
 */
void settextbgcolor(Text *self, Color bg_color);


/**
 * \brief Determines whether the text needs to be refreshed.
 *
 * \param[in] self The text
 *
 * \return \c true iff the text needs to be re-rendered on the screen
 */
bool textneedsupdate(const Text *self);


/**
 * \brief Draws a text on screen fastly, without smoothing.
 *
 * \param[in,out] self   The text to render
 * \param[in]     window The window to render the text to
 *
 * \return \c true iff the text was drawn (and rendered, if needed) without
 *         error
 */
bool drawtext(Text *self, Window *window, Point pos);


#endif // TEXT_H
