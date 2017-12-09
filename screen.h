/**
 * \file "screen.h"
 * \author joH1
 *
 * This file defines a screen, that is the content of the window shown
 * during the common parts of the , where the scene is displayed and the
 * player can interact with items.
 *
 * \sa Scene
 */

#ifndef SCREEN_H
#define SCREEN_H

/**
 * \extends Screen
 *
 * \brief
 */
typedef struct screen Screen;


#include "inventory.h"
#include "scene.h"
#include "screen.h"
#include "types.h"



/**
 * \brief Constructs a new screen.
 *
 * \param[in] name The name of the screen
 */
Screen *newscreen(cstr name);

/**
 * \brief Deallocates a screen.
 *
 * \param[in,out] self The screen to free
 */
void freescreen(Screen *self);


/**
 * \brief Retrieves the name of the screen.
 *
 * \param[in] self The screen
 */
cstr getscreenname(const Screen *self);

/**
 * \brief Updates the name of the screen.
 *
 * \param[in,out] self The screen
 * \param[in]  name The new name to give to the screen
 */
void setscreenname(Screen *self, cstr name);


/**
 * \brief Retrieves the inventory associated with this screen.
 *
 * \param[in] self The screen
 *
 * \sa Inventory
 */
Inventory *getscreeninventory(const Screen *self);

/**
 * \brief Updates the inventory of the screen.
 *
 * \param[in,out] self  The screen
 * \param[in] inventory The new inventory of the screen
 */
void setscreeninventory(Screen *self, Inventory *inventory);


/**
 * \brief Retrieves the scene of the screen.
 *
 * \param[in] self The screen
 *
 * \sa Scene
 */
Scene *getscreenscene(const Screen *self);

/**
 * \brief Updates the scene associated with this screen.
 *
 * \param[in,out] self The screen
 * \param[in]  scene The new scene
 */
void setscreenscene(Screen *self, Scene *scene);


void updatescreen(Screen *self, Window *window);

#endif /* SCREEN_H */
