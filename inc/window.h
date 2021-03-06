/**
 * \file window.h
 * \author joH1
 *
 * \version 0.1
 *
 * \brief The window, main structure that contains all the displayed elements.
 *
 * This file contains the definition of the game window as a C structure.
*/

#ifndef WINDOW_H
#define WINDOW_H


#include <SDL2/SDL_render.h> /* for SDL_Renderer, SDL_WindowFlags and SDL_RendererFlags */
#include <stdbool.h>

#include "colors.h" /* for Color type */


/**
 * \brief The structure used to represent a window on the screen.
 *
 */
typedef struct window Window;

#include "screen.h"

/**
 * \defgroup window_flags Window flags
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
 * \param[in] winFlags The flags to instantiate the SDL window with
 * \param[in] renFlags The flags to instantiate the SDL renderer with
 *
 * \return A new window of given title, geometry and initalization parameters
 *         for it and the associated renderer
 *
 * \sa SDL_Window
 * \sa SDL_Renderer
 */
Window *newWindow(str title, const Rect *geometry, SDL_WindowFlags winFlags, SDL_RendererFlags renFlags);

/**
 * \brief Instantiates a new window, using the default flags.
 *
 * \param[in] title    The title of the window (visible on the title bar)
 * \param[in] geometry The dimensions and position of the window
 *
 * \return newWindow(title, geometry, DEFAULT_WIN_FLAGS, DEFAULT_REN_FLAGS)
 *
 * \sa newWindow
 */
inline Window *newWin(const str title, const Rect *const geometry) {
	return newWindow(title, geometry, DEFAULT_WIN_FLAGS, DEFAULT_REN_FLAGS);
}

/**
 * \brief Deallocates the memory used by a Window.
 *
 * \param[in,out] self The window to free
 */
void freeWindow(Window *self);


/**
 * \brief Sets the rendering color for drawings.
 *
 * \param[in] self  The window to set the drawing color of
 * \param[in] color The color to draw
 *
 * \return \c true on success, \c false on error
 */
bool setWindowDrawColor(Window *self, Color color);

/**
 * \brief Retrieves the title of the window
 *
 * \param[in] self The window to get the title from
 *
 * \return The title of the window, as seen on the title bar on the desktop
 */
str getWindowTitle(const Window *self);

/**
 * \brief Updates the title of the window
 *
 * \param[in] self  The window to set the title to
 * \param[in] title The title to give to the window
 */
void setWindowTitle(Window *self, str title);

/**
 * \brief Gets the renderer associated to this window
 *
 * \note There is no getter function for the renderer, as it should not be
 *       changed after the window is initialized
 *
 * \param[in] self The window to get the renderer from
 *
 * \return The \a Renderer associated with the window
 *
 * \sa SDL_Renderer
 */
SDL_Renderer *getWindowRenderer(const Window *self);

/**
 * \brief Returns the width of the window, in pixels
 *
 * \note This parameter can not be modified, and the window can not be resized
 *
 * \param[in] self The window to get the width from
 *
 * \return The width of the window, in pixels
 */
unsigned int getWindowWidth(const Window *self);

/**
 * \brief Returns the height of the window, in pixels
 *
 * \note This parameter can not be modified, and the window can not be resized
 *
 * \param[in] self The window to get the height from
 *
 * \return The height oof the window, in pixels
 */
unsigned int getWindowHeight(const Window *self);


/**
 * \brief Adds a screen to the window.
 *
 * \note If this is the first screen of the window, it is automatically set as
 *       the current screen.
 *
 * \param[in,out] self   The window
 * \param[in]     screen The screen to add
 *
 * \return The position of the screen in the window, or \c -1 if an error
 *         occurred
 */
int addWindowScreen(Window *self, Screen *screen);


/**
 * \brief Retrieves the screen currently displayed in the window.
 *
 * \param[in] self The window
 *
 * \return The current screen of the window
 */
Screen *getWindowCurrentScreen(Window *const self);

/**
 * \brief Sets the current screen of the window.
 *
 * \param[in,out] self The window
 * \param[in] name The name of the screen to set
 *
 * \return \c true iff the name could be associated with a screen, which in turn
 *         could be set as the current screen
 */
bool setWindowCurrentScreen(Window *self, str name);


/**
 * \brief Retrieves a Sprite from the window at given position.
 *
 * \param[in] self The window
 * \param[in] pos  The position to look at
 *
 * \return The Sprite at position \a pos, or \c NULL if none was found.
 */
Sprite *getWindowSpriteAt(const Window *self, Point pos);


/**
 * \brief Updates the window and its content (scene and sprites).
 * NOTE: This method does not render the window. Call renderwindow after
 * this
 *
 * \param[in] self The window to update
 *
 * \sa renderwindow
 */
void updateWindow(Window *self);

/**
 * \brief Renders The window on screen.
 *
 * \param[in] self the window to render
 */
void renderWindow(Window *self);

/**
 * \brief Clears the window and fills it with color specified in
 *        setwindowdrawcolor().
 *
 * \param[in] self The window to clear
 *
 * \return \c true on success, \c false on error
 *
 * \sa setwindowdrawcolor
 */
bool clearWindow(Window *self);


/**
 * \brief Specify the function to be run as the main game loop.
 *
 * The main loop is the function in which the game is actually orchestrated.
 * It manages time, handles events, and respond to player interaction.
 *
 * \param[in,out] self The window
 * \param[in]     gameLoop The game function
 */
void setWindowGameLoop(Window *self, void (*gameLoop)(void));

/**
 * \brief Runs the game.
 *
 * Executes the function given as game loop.
 *
 * \param[in] self The window
 *
 * \sa setWindowGameLoop
 */
void windowRun(const Window *self);


#endif /* WINDOW_H */
