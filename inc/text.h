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


#include "colors.h"
#include "font.h"
#include "texture.h"
#include "libmisc.h"
#include "uielements.h"
#include "window.h"



/**
 * \brief This enum defines the different types of rendering for the text.
 */
typedef enum {
	/**
	 * \brief The text is rendered without smoothing or alpha blending.
	 *
	 * This rendering is the fastest, but not necessarily the most eye-pleasing.
	 */
	TEXTRENDER_FAST,

	/**
	 * \brief The text is rendered smoothly, but the background is opaque and no
	 *        blending is made with the scene behind.
	 *
	 * The rendering is slower than \a TEXTRENDER_FAST, but the clipping on the
	 * scene should be as fast.
	 */
	TEXTRENDER_OPAQUEBG,

	/**
	 * \brief This rendering mode is the slowest, but also the nicest. The text
	 *        is rendered smoothly and blended into the background scene.
	 *
	 * The rendering is as fast as \a TEXTRENDER_OPAQUEBG, but clipping on the
	 * scene can be longer. This mode should be used only if high quality is
	 * needed and the text will not change frequently.
	 */
	TEXTRENDER_SMOOTH
} TextRenderType;


/**
 * \brief The structure holding the data for a text to render.
 */
typedef struct text Text;


/**
 * \brief Instantiates a new text for rendering.
 *
 * \param[in] string    The string data of the text
 * \param[in] font      The font to render the text in
 * \param[in] textColor The color of the text
 * \param[in] type      The type of rendering to set for the text
 *
 * \return A text for rendering, of given textual value, to be rendered in given
 *         font and color
 */
Text *newText(str string, Font *font, const Color *textColor, TextRenderType type);

/**
 * \brief Constructs a text with the global UI style.
 *
 * \param[in] string The textual data
 * \param[in] type The type of rendering to set for the text
 *
 * \return A new text with UI style font and color(s)
 */
Text *newUIText(str string, TextRenderType type);

/**
 * \brief Deallocates the memory used by a text.
 *
 * \param[in,out] self The text to free
 */
void freeText(Text *self);


/**
 * \brief Updates the string value of the Text.
 *
 * \param[in,out] self   The text
 * \param[in]     string The string value to set
 */
void setTextString(Text *self, str string);

/**
 * \brief Updates the text color of the Text.
 *
 * \param[in,out] self  The text
 * \param[in]     color The text color
 */
void setTextColor(Text *self, const Color *color);


/**
 * \brief Updates the background color of the Text.
 *
 * \note The background color is only used when rendering with an opaque
 *       background.
 *
 * \param[in,out] self    The text
 * \param[in]     bgColor The color to set
 */
void setTextBgColor(Text *self, const Color *bgColor);


/**
 * \brief Determines whether the text needs to be refreshed.
 *
 * \param[in] self The text
 *
 * \return \c true iff the text needs to be re-rendered on the screen
 */
bool textNeedsUpdate(const Text *self);


/**
 * \brief Renders the text in the form of a \a Texture.
 *
 * \param[in,out] self   The text to render
 * \param[in]     window The window to which to render
 *
 * \return A static flattened texture of the text (static here in the sense of
 *         <i>"no longer modifiable"</i>)
 */
Texture *renderText(Text *self, Window *window);

/**
 * \brief Draws a text on screen fastly, without smoothing.
 *
 * \param[in,out] self   The text to render
 * \param[in]     window The window to render the text to
 * \param[in]     pos    The position where to clip the text in the window
 *                       (left-up corner)
 *
 * \return \c true iff the text was drawn (and rendered, if needed) without
 *         error
 */
bool drawText(Text *self, Window *window, Point pos);


/**
 * \brief Retrieve the width and height of the text.
 *
 * \param[in]  self The text
 * \param[out] w    The width of the text
 * \param[out] h    The height of the text
 *
 * \return \c true iff the text has already been rendered, and the retrieval of
 *         the geometry values happened correctly
 */
bool getTextGeom(const Text *self, unsigned int *w, unsigned int *h);


#endif // TEXT_H
