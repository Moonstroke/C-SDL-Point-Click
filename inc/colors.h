/**
 * \file colors.h
 * \author joH1
 *
 * This file contains several color constants, and functions used to translate
 * colors stored as integers to structures or vice-versa.
*/

#ifndef COLORS_H
#define COLORS_H


#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>

#include "types.h"



/**
 * \defgroup colors Colors
 * \brief Common colors in RGBA 32px format.
 * \{
 */
/** \brief This is a macro for the black color. */
#define BLACK   0x000000ff

/** \brief Macro for the white color. */
#define WHITE   0xffffffff
/** \brief The color gray 50%. */
#define GRAY50  0x7f7f7fff

/** \brief The color red. */
#define RED     0xff0000ff

/** \brief Macro for yellow. */
#define YELLOW  0xffff00ff

/** \brief The color green. */
#define GREEN   0x00ff00ff

/** \brief The color cyan. */
#define CYAN    0x00ffffff

/** \brief The color blue. */
#define BLUE    0x0000ffff

/** \brief The color magenta. */
#define MAGENTA 0xff00ffff
/** \} */


/** \brief The default value for the alpha channel in inline funcs ignoring it. */
#define ALPHA_DEFAULT 0xff


/**
 * \brief Shrinks four octets to a single integer in format RGBA 32px.
 *
 * \param[in] r The red value
 * \param[in] g The green value
 * \param[in] b The blue value
 * \param[in] a The alpha value (transparency)
 *
 *\return A 32-bits integers holding all four color channels values
 *
 * \sa SDL_PIXELFORMAT_RGBA8888
 */
inline uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return SDL_FOURCC(a, b, g, r);
}
/**
 * \brief Shrinks three octets to a single integer, ignoring alpha channel.
 *
 * \param[in] r The red value
 * \param[in] g The green value
 * \param[in] b The blue value
 *
 * \return rgba(r, g, b, ALPHA_DEFAULT)
 *
 * \sa rgba
 */
inline uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
	return rgba(r, g, b, ALPHA_DEFAULT);
}

/**
 * \brief Explodes a 32-bits integer into a color structure
 *
 * \param[in] color The integer to break down
 *
 * \return A structure holding four values for each diferent color channel
 */
inline Color icolor(uint32_t color) {
	return (Color){(uint8_t)(color >> 24), (uint8_t)(color >> 16),
	               (uint8_t)(color >> 8), (uint8_t)color};
}

/**
 * \brief Wraps four byte values in the color structure provided by the SDL
 *
 * \param[in] r The red value
 * \param[in] g The green value
 * \param[in] b The blue value
 * \param[in] a The alpha value (transparency)
 *
 * \sa SDL_Color
 * \sa color
 */
inline Color colora(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return (Color){r, g, b, a};
}
/**
 * \brief Wraps three bytes into the Color structure, with default value for
          the alpha channel
 *
 * \param[in] r The red value
 * \param[in] g The green value
 * \param[in] b The blue value
 *
 * \return colora(r, g, b, ALPHA_DEFAULT)
 *
 * \sa colora
 */
inline Color color(uint8_t r, uint8_t g, uint8_t b) {
	return colora(r, g, b, ALPHA_DEFAULT);
}


#endif // COLORS_H
