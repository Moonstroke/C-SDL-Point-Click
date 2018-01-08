/**
 * \file colors.h
 * \author joH1
 *
 * \version 0.1
 *
 * \brief Macros for common colors and functions handling the conversion to and
 *        from different types representing colors.
 *
 * This file contains several color constants, and functions used to translate
 * colors stored as integers to structures or vice-versa.
*/

#ifndef COLORS_H
#define COLORS_H


#include <SDL2/SDL_pixels.h> /* for SDL_Color */
#include <stdint.h> /* for uint8_t */


typedef SDL_Color Color; /**< A RGBA color structure */


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
	return ((uint32_t)r) << 24 | ((uint32_t)g) << 16
	     | ((uint32_t)b) <<  8 |  (uint32_t)a;
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
 * \return a Color structure containing the given bytes as color channels
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


/**
 * \brief Specifies the type of operation to perform when merging colors.
 *
 * \a MERGE_ADD, \a MERGE_MUL and \a MERGE_SUB are mutually exclusive, using
 * two or more of them is not allowed.
 * The value can be OR'ed with \a MERGE_BLEND_ALPHA to modify the behaviour
 * per the alpha channel.
 *
 * \sa mergeColors
 */
typedef enum {

	/**
	 * \brief Specifies an addition.
	 *
	 * \code resultRGBA = color1RGB + color2RGB \endcode
	 */
	MERGE_ADD = 0x1,

	/**
	 * \brief Specifies an multiplication.
	 *
	 * \code resultRGBA = color1RGB * color2RGB \endcode
	 */
	MERGE_MUL = 0x2,

	/**
	 * \brief Specifies an substraction.
	 *
	 * \code resultRGBA = color1RGB - color2RGB \endcode
	 */
	MERGE_SUB = 0x4,

	/**
	 * \brief Specifies whether to blend colors proportionnaly to their alpha
	 *        channels or not.
	 *
	 * This value is to be used in OR-combination with one of the above. It
	 * yields \code resultRGB = (color1RGB * (color1A / 255)) <op> (color2RGB *
	 * (color2A / 255))\endcode where \a <op> is the other MergeMode.
	 */
	MERGE_BLEND_ALPHA = 0x10,
} MergeMode;

/**
 * \brief Merges two colors (operates on the four channels according to the
 *        specified operation.
 *
 * \note If an invalid \a mode is given, the data pointed to by \a result will
 *       be filed with zeroes, so a resulting color of "fully transparent black"
 *       can indicate invalid program state.
 *
 * \param[in]  color1 The first color to merge
 * \param[in]  color2 The second color to merge
 * \param[in]  mode   The merging operation to perform
 *
 * \return A \a Color containing the result of the operation
 */
Color mergeColors(const Color *color1, const Color *color2, MergeMode mode);


#endif // COLORS_H
