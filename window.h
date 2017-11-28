#ifndef WINDOW_H
#define WINDOW_H


#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>


typedef struct window Window;

#include "scene.h"
#include "inventory.h"
#include "types.h"



#define TITLE_MAX_LENGTH 16

#define SPLASH_WINDOW (SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP)
#define FOCUSED_WIN_FLAGS (SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS)
#define FULLSCREEN_WIN_FLAGS (SDL_WINDOW_FULLSCREEN_DESKTOP)
#define DEFAULT_WIN_FLAGS (SDL_WINDOW_SHOWN | FOCUSED_WIN_FLAGS)

#define DEFAULT_REN_FLAGS (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED)


Window *newwindow(cstr title, Rect geometry, WinFlags winflags, RenderFlags renflags);
inline Window *newwin(cstr title, Rect geometry) {
	return newwindow(title, geometry, DEFAULT_WIN_FLAGS, DEFAULT_REN_FLAGS);
}

void freewindow(Window *window);


/**
 * \brief Updates the window and its content (scene and sprites).
 * NOTE: This method does not render the window. Call renderwindow after
 * this
 *
 * \param window The window to update
 *
 * \return 1 on success, 0 on error
 *
 * \sa renderwindow(Window*)
 */
void updatewindow(Window *window);

/**
 * \brief Renders the window on screen.
 *
 * \param window the window to render
 */
void renderwindow(Window *window);

/**
 * \brief Clears the window and fills it with color specified in setwindowdrawcolor.
 *
 * \param window the window to clear
 *
 * \return 1 on success, 0 on error
 *
 * \sa setdrawcolor(Window*, Uint32)
 */
bool clearwindow(Window *window);

/**
 * \brief Sets the rendering color for drawings.
 *
 * @param window the window to
 * @param color  the color to draw
 *
 * \return 1 on success, 0 on error
 */
bool setwindowdrawcolor(Window *window, Color color);

cstr getwindowtitle(const Window *window);
void setwindowtitle(Window *window, cstr title);

Renderer *getwindowrenderer(const Window *window);

void setwindowscene(Window *window, Scene *scene);
Scene *getwindowscene(const Window *window);

void setwindowinventory(Window *w, Inventory *i);
Inventory *getwindowinventory(const Window *w);

/**
 * Geometry getters
 */
size_t getwindoww(const Window *window);
size_t getwindowh(const Window *window);


#endif /* WINDOW_H */
