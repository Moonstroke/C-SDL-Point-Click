#include "libsdl2.h"


#include <clog.h>
#include <SDL2/SDL.h> /* for SDL_Init() and SDL_Quit() */
#include <SDL2/SDL_ttf.h> /* for TTF_Init() and TTF_Quit() */
#include <stdbool.h>
#include <stdlib.h> /* for atexit() and exit() */



static bool set_atexit;


void initSDL(const uint32_t flags) {
	int ok = SDL_Init(flags);
	if(ok) {
		error("Could not load SDL2: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	ok = TTF_Init();
	if(ok) {
		error("Could not load SDL_TTF: %s", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	atexit(SDL_Quit);
	atexit(TTF_Quit);
	set_atexit = true;
}

void clearSDL(void) {
	if(!set_atexit) {
		TTF_Quit();
		SDL_Quit();
	}
}

void logSDLRendererInfo(SDL_Renderer *const ren) {
	SDL_RendererInfo i;
	if(SDL_GetRendererInfo(ren, &i) < 0)
		return;
	info("\nRenderer infos");
	info("Renderer name: \"%s\"", i.name);
	info("Renderer flags: 0x%x", i.flags);
	const unsigned char n = i.num_texture_formats;
	info("%u available texture formats", n);
	for(unsigned char k = 0; k < n; ++k)
		info("Texture format #%u: 0x%x", k + 1, i.texture_formats[k]);
	info("Maximum texture dimension: (%u x %u)\n", i.max_texture_width,
	                                               i.max_texture_height);
}
