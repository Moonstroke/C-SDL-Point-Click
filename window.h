/**
 * \file window.h
 * \author joH1
 *
 * This file contains the definition of the game window as a C structure.
*/

#ifndef WINDOW_H
#define WINDOW_H


#include <SDL2/SDL_render.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

#include "types.h"


/**
 * \brief The structure used to represent a window on the screen.
 *
 */
typedef struct window Window;

#include "screen.h"

/**
 * \defgroup "window_flags"
 * \brief Some constant values for the window flags.
 * \{
 */
/**
 * \brief Flags to display the window as a \a splash window.
 *
 * A splash window is a borderless window showing on application startup, to
 * indicate that it is launching.
 */
#define SPLASH_WINDOW (SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP)

/** \brief Starts the window and gives it focus. */
#define FOCUSED_WIN_FLAGS (SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS)

/** \brief Starts the window and activates fullscreen mode. */
#define FULLSCREEN_WIN_FLAGS (SDL_WINDOW_FULLSCREEN_DESKTOP)

/**
 * \brief The default flags for window initializing.
 *
 * This is the value used when using newwin()
 */
#define DEFAULT_WIN_FLAGS (SDL_WINDOW_SHOWN | FOCUSED_WIN_FLAGS)
/** \} */

/**
 * \brief The default renderer flags.
 *
 * This is the value used when initializing the window with newwin()
 */
#define DEFAULT_REN_FLAGS (SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED)


/**
 * \brief Instantiates a new window.
 *
 * \param[in] title    The title of the window (visible on the title bar)
 * \param[in] geometry The dimensions and position of the window
 * \param[in] winflags The flags to instantiate the SDL window with
 * \param[in] renflags The flags to instantiate the SDL renderer with
 *
 * \sa SDL_Window
 * \sa SDL_Renderer
 */
Window *newwindow(cstr title, Rect geometry, WinFlags winflags, RenderFlags renflags);

/**
 * \brief Instantiates a new window, using the default flags.
 *
 * \param[in] title    The title of the window (visible on the title bar)
 * \param[in] geometry The dimensions and position of the window
 *
 * \return newwindow(title, geometry, DEFAULT_WIN_FLAGS, DEFAULT_REN_FLAGS)
 *
 * \sa newwindow
 */
inline Window *newwin(cstr title, Rect geometry) {
	return newwindow(title, geometry, DEFAULT_WIN_FLAGS, DEFAULT_REN_FLAGS);
}

/**
 * \brief Deallocates the memory used by a Window.
 */
void freewindow(Window *self);


/**
 * \brief Sets the rendering color for drawings.
 *
 * \param[in] self  The window to set the drawing color of
 * \param[in] color The color to draw
 *
 * \return 1 on success, 0 on error
 */
bool setwindowdrawcolor(Window *self, Color color);

/**
 * \brief Retrieves the title of the window
 *
 * \param[in] self The window to get the title from
 *
 * \return The title of the window, as seen on the title bar on the desktop
 */
cstr getwindowtitle(const Window *self);

/**
 * \brief Updates the title of the window
 *
 * \param[in] self  The window to set the title to
 * \param[in] title The title to give to the window
 */
void setwindowtitle(Window *self, cstr title);

/**
 * \brief Gets the renderer associated to this window
 *
 * \param[in] self The window to get the renderer from
 *
 * \note There is no getter function for the renderer, as it should not be
 *       changedafter the window is initialized
 *
 * \sa SDL_Renderer
 */
Renderer *getwindowrenderer(const Window *self);

/**
 * \brief Returns the width of the window, in pixels
 *
 * \param[in] self The window to get the width from
 *
 * \note This parameter can not be modified, and the window can not be resized
 */
size_t getwindoww(const Window *self);

/**
 * \brief Returns the height of the window, in pixels
 *
 * \param[in] self The window to get the height from
 *
 * \note This parameter can not be modified, and the window can not be resized
 */
size_t getwindowh(const Window *self);


/**
 * \brief Adds a screen to the window.
 *
 * \param[in,out] self   The window
 * \param[in]     screen The screen to add
 *
 * \return The position of the screen in the window, or \c -1 if an error
 *         occurred
 */
ssize_t addwindowscreen(Window *self, Screen *screen);

/**
 * \brief Sets the current screen of the window.
 *
 * \param[in,out] self The window
 * \param[in] name The name of the screen to set
 *
 * \return \c true iff the name could be associated with a screen, which in turn
 *         could be set as the current screen
 */
bool setwindowcurrentscreen(Window *self, cstr name);

/**
 * \brief Updates the window and its content (scene and sprites).
 * NOTE: This method does not render the window. Call renderwindow after
 * this
 *
 * \param[in] self The window to update
 *
 * \return 1 on success, 0 on error
 *
 * \sa renderwindow
 */
void updatewindow(Window *self);

/**
 * \brief Renders The window on screen.
 *
 * \param[in] self the window to render
 */
void renderwindow(Window *self);

/**
 * \brief Clears the window and fills it with color specified in
 *        setwindowdrawcolor().
 *
 * \param[in] self The window to clear
 *
 * \return 1 on success, 0 on error
 *
 * \sa setwindowdrawcolor
 */
bool clearwindow(Window *self);


#endif /* WINDOW_H */
