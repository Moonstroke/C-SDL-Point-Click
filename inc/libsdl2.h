/**
 * \file libsdl2.h
 * \author joH1
 *
 * \version 0.1
 *
 * \brief SDL-related functions that manage actions like start and quit.
 *
 * This file contains the definition of several functions related to the SDL v2
 * and interfacing with it.
*/

#ifndef LIBSDL2_H
#define LIBSDL2_H


#include <stdint.h>
#include <SDL2/SDL_render.h>


/**
 * \brief Initializes the SDL.
 *
 * \param[in] flags The flags to specify which modes to initialize
 */
void initSDL(uint32_t flags);

/**
 * \brief Frees memory and properly quits the SDL.
 */
void clearSDL(void);

/**
 * \brief Logs info for the current video mode, if set by SDL_SetVideoMode(),
 *        or the *best* available one
 *
 * \param[in] renderer The renderer from which to log info
 */
void logSDLRendererInfo(SDL_Renderer *renderer);

#endif // LIBSDL2_H
