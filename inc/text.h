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

#include "texture.h"
#include "window.h"


/** A redefinition of the font type. */
typedef TTF_Font Font;


/**
 * \defgroup text_render_funcs Text rendering
 * \brief Functions that handle rendering text to the screen.
 * \{
 */

/**
 * \brief Renders a text fastly, without smoothing.
 *
 * \param[in] text       The text to render
 * \param[in] font       The font to render the text in
 * \param[in] text_color The color in which to render the text
 * \param[in] window     The window to render the text to
 *
 * \return The rendering of the text, as a \a Texture
 */
Texture *rendertext_fast(str text, Font *font, Color text_color, const Window *window);

/**
 * \brief Renders a text more nicely, but over an opaque background.
 *
 * \param[in] text       The text to render
 * \param[in] font       The font to render the text in
 * \param[in] text_color The color in which to render the text
 * \param[in] bg_color   The color for the background
 * \param[in] window     The window to render the text to
 *
 * \return The rendering of the text, as a \a Texture
 */
Texture *rendertext_bg(str text, Font *font, Color text_color, Color bg_color, const Window *window);

/**
 * \brief Renders a text nicely but slowly, antialiased and blended into the
 * background texture.
 *
 * \param[in] text       The text to render
 * \param[in] font       The font to render the text in
 * \param[in] text_color The color in which to render the text
 * \param[in] window     The window to render the text to
 *
 * \return The rendering of the text, as a \a Texture
 */
Texture *rendertext_hq(str text, Font *font, Color text_color, const Window *window);


/** \} */


#endif // TEXT_H
