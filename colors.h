#ifndef COLORS_H
#define COLORS_H


#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_stdinc.h>


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
 * The last 8 bits are left empty.
 *
 * \sa SDL_PIXELFORMAT_RGBA8888
 */
//#define rgba(r, g, b, a) ((r) << 24 | (g) << 16 | (b) << 8 | a)
#define rgba(r, g, b, a) (SDL_FOURCC(a, b, g, r))
#define rgb(r, g, b) rgba(r, g, b, 255)

/**
 * \brief Wraps integer values in the structure provided by SDL
 */
#define icolor(color) ((SDL_Color){color >> 24, color >> 16, color >> 8, color})
#define color(r, g, b) colora(r, g, b, 0)
#define colora(r, g, b, a) ((SDL_Color){(r), (g), (b), (a)})

#endif /* COLORS_H */
