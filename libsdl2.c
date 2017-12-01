#include "libsdl2.h"


#include <stdbool.h>

#include "log.h"
#include "events.h"



static bool set_atexit;


void initSDL(const uint32_t flags) {
	int ok = SDL_Init(flags);
	if(ok != 0) {
		error("Could not load SDL2: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	atexit(SDL_Quit);
	set_atexit = true;
}

void clearSDL(void) {
	if(!set_atexit)
		SDL_Quit();
}

void logSDLRendererInfo(Renderer *const ren) {
	SDL_RendererInfo info;
	if(SDL_GetRendererInfo(ren, &info) < 0) return;
	info("Renderer name:  \"%s\"\n", info.name);
	info("Renderer flags: %x\n", info.flags);
	const int n = info.num_texture_formats;
	info("# of available texture formats: %d", n);
	int i;
	for(i = 0; i < n; ++i)
		info("Texture format #%2d:           %x", i, info.texture_formats[i]);
	info("Maximum texture dimension:      (%d x %d)", info.max_texture_width, info.max_texture_height);
}
