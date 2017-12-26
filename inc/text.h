#ifndef TEXT_H
#define TEXT_H


#include <SDL2/SDL_ttf.h>

#include "texture.h"
#include "window.h"


typedef TTF_Font Font;


Texture *rendertext_fast(str text, Font *font, Color text_color, const Window *window);

Texture *rendertext_bg(str text, Font *font, Color text_color, Color bg_color, const Window *window);

Texture *rendertext_hq(str text, Font *font, Color text_color, const Window *window);

#endif // TEXT_H