/**
 * \file "screen.h"
 * \author joH1
 *
 * \version 0.1
 *
 * \brief The screen, the contents of the window.
 *
 * This file defines a screen, that is the content of the window shown
 * during the common parts of the , where the scene is displayed and the
 * player can interact with items.
 *
 * \sa Scene
 */

#ifndef SCREEN_H
#define SCREEN_H


#include "types.h"



/**
 * \brief Represents a \b screen, i.e. the structure of all the displayed items
 *        at a given time.
 *
 * For example, the in-game display, the pause menu, and the options page are
 * different \e screens.
 */
typedef struct screen Screen;


#include "inventory.h"
#include "scene.h"



/**
 * \brief Constructs a new screen.
 *
 * \param[in] name The name of the screen
 *
 * \return A screen of given name
 */
Screen *newScreen(str name);

/**
 * \brief Deallocates a screen.
 *
 * \param[in,out] self The screen to free
 */
void freeScreen(Screen *self);


/**
 * \brief Retrieves the name of the screen.
 *
 * \param[in] self The screen
 *
 * \return The name of the screen
 */
str getScreenName(const Screen *self);

/**
 * \brief Updates the name of the screen.
 *
 * \param[in,out] self The screen
 * \param[in]  name The new name to give to the screen
 */
void setScreenName(Screen *self, str name);


/**
 * \brief Retrieves the inventory associated with this screen.
 *
 * \param[in] self The screen
 *
 * \return The \a Inventory associated with this screen, or \c NULL if there is
 *         no such inventory
 *
 * \sa Inventory
 */
Inventory *getScreenInventory(const Screen *self);

/**
 * \brief Updates the inventory of the screen.
 *
 * \param[in,out] self  The screen
 * \param[in] inventory The new inventory of the screen
 */
void setScreenInventory(Screen *self, Inventory *inventory);


/**
 * \brief Retrieves the scene of the screen.
 *
 * \param[in] self The screen
 *
 * \return The \a Scene associated with this screen
 *
 * \sa Scene
 */
Scene *getScreenScene(const Screen *self);

/**
 * \brief Changes the scene associated with this screen.
 *
 * \param[in,out] self The screen
 * \param[in]  scene The new scene
 */
void setScreenScene(Screen *self, Scene *scene);


/**
 * \brief Graphically updates the screen on given window.
 *
 * \param[in,out] self   The screen
 * \param[in,out] window The window
 */
void updateScreen(Screen *self, Window *window);

#endif // SCREEN_H
