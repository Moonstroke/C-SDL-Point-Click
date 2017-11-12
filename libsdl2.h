#ifndef LIBSDL2_H
#define LIBSDL2_H


#include <stdlib.h>
#include <SDL2/SDL.h>

#include "types.h"


/**
 * \brief Initializes the SDL.
 *
 * \param flags	the flags to specify which modes to initialize
 */
void initSDL(Uint32 flags);

/**
 * \brief Frees memory and properly quits the SDL.
 */
void clearSDL(void);

/**
 * \brief Logs info for the current video mode, if set by SDL_SetVideoMode(),
 *        or the *best* available one
 */
void logSDLRendererInfo(SDL_Renderer *renderer);


#endif /* LIBSDL2_H */
