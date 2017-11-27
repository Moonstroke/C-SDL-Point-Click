#ifndef COLORS_H
#define COLORS_H


#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>

#include "types.h"


/**
 * \brief Standard colors in RGBA 32px format
 */
#define BLACK   0x000000ff
#define WHITE   0xffffffff
#define GRAY50  0x7f7f7fff

#define RED     0xff0000ff
#define YELLOW  0xffff00ff
#define GREEN   0x00ff00ff
#define CYAN    0x00ffffff
#define BLUE    0x0000ffff
#define MAGENTA 0xff00ffff


/**
 * \brief Shrinks three integer values to a single one in format RGBA 32px.
 *
 * \param[in] r The red value
 * \param[in] g The green value
 * \param[in] b The blue value
 * \param[in] a The alpha value (transparency)
 *
 * \sa SDL_PIXELFORMAT_RGBA8888
 */
inline uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	return SDL_FOURCC(a, b, g, r);
}
inline uint32_t rgb(uint8_t r, uint8_t g, uint8_t b) {
	return rgba(r, g, b, 255);
}

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
inline Color color(uint8_t r, uint8_t g, uint8_t b) {
	return colora(r, g, b, 255);
}


#endif /* COLORS_H */
