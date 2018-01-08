/**
 * \file "font.h"
 * \author joH1
 *
 * \version 0.1
 *
 * \brief Declaration of the font type.
 *
 */

#ifndef FONT_H
#define FONT_H


#include <SDL2/SDL_ttf.h> /* for TTF_Font and TT_OpenFont() */

#include "libmisc.h" /* for str */



/**
 * \brief A redefinition of the \e font type.
 */
typedef TTF_Font Font;


/**
 * \brief Opens the font of file with given basename.
 *
 * \note The font is located at \code data/fonts/<basename>.ttf \endcode.
 *
 * \param[in] basename The basename of the font file
 * \param[in] ptSize   The size of the font to open
 *
 * \return A \a Font of given basename, with given size
 */
Font *openFont(str basename, unsigned int ptSize);


#endif /* FONT_H */
