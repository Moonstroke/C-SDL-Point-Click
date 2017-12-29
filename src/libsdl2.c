#include "libsdl2.h"


#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "log.h"
#include "events.h"



static bool set_atexit;


void initSDL(const uint32_t flags) {
	int ok = SDL_Init(flags);
	if(ok != 0) {
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
	SDL_RendererInfo reninfo;
	if(SDL_GetRendererInfo(ren, &reninfo) < 0) return;
	info("Renderer name:  \"%s\"\n", reninfo.name);
	info("Renderer flags: %x\n", reninfo.flags);
	const int n = reninfo.num_texture_formats;
	info("# of available texture formats: %d", n);
	int i;
	for(i = 0; i < n; ++i)
		info("Texture format #%2d:           %x", i, reninfo.texture_formats[i]);
	info("Maximum texture dimension:      (%d x %d)", reninfo.max_texture_width, reninfo.max_texture_height);
}
