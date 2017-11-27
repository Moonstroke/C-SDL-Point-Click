#ifndef LIBSDL2_H
#define LIBSDL2_H


#include <stdlib.h>
#include <SDL2/SDL.h>

#include "types.h"


/**
 * \brief Initializes the SDL.
 *
 * \param flags The flags to specify which modes to initialize
 */
void initSDL(uint32_t flags);

/**
 * \brief Frees memory and properly quits the SDL.
 */
void clearSDL(void);

/**
 * \brief Logs info for the current video mode, if set by SDL_SetVideoMode(),
 *        or the *best* available one
 */
void logSDLRendererInfo(Renderer *renderer);


#endif /* LIBSDL2_H */
