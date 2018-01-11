/**
 * \file scene.h
 * \author joH1
 *
 * \version 0.1
 *
 * \brief The scene, the area of the screen where the main game view is located.
 *
 * This file contains the definition of the game scene.
*/

#ifndef SCENE_H
#define SCENE_H


#include <stdbool.h>

#include "libmisc.h" /* for str and padding() */
#include "geom.h" /* for Point and Rect */


/**
 * \brief This structure represents the game scene in the window.
 */
typedef struct scene Scene;


#include "sprite.h"
#include "texture.h"
#include "uielements.h"
#include "window.h"


/**
 * \brief Instantiates a game scene to contain \a numsprites \a Sprites.
 *
 * \note for increased performances, load the texture with
 *       \c SDL_TEXTUREACCESS_STATIC, if ever -- or \c SDL_TEXTUREACCESS_TARGET?
 *
 * \param[in] geom       The geometry of the scene
 * \param[in] background The background texture for the scene
 * \param[in] numSprites  The number of sprites the scene will contain
 * \param[in] name       The name of the scene
 *
 * \return A new scene of given geometry, background, number of sprites to
 *         include and name
 */
Scene *newGameScene(Rect geom, Texture *background, unsigned int numSprites, str name);

/**
 * \brief Instantiates a scene for user interface (menu).
 * \param[in] geom       The geometry of the scene
 * \param[in] background The background texture for the scene
 * \param[in] numUIElts  The number of UI elements the scene will contain
 * \param[in] name       The name of the scene
 *
 * \return A new scene of given geometry, background, number of sprites to
 *         include and name
 */
Scene *newUIScene(Rect geom, Texture *background, unsigned int numUIElts, str name);

/**
 * \brief Liberates the memory used by the scene, and its contained sprites
 *
 * \param[in] self The scene to free
 */
void freeScene(Scene *self);

/**
 * \brief Verifies whether the scene needs to be redrawn on screen.
 * > "Has it or any contained sprite changed?"
 *
 * \param[in] self The scene to check for updates
 *
 * \return \c true if the scene needs an update
 */
bool sceneNeedsUpdate(const Scene *self);

/**
 * \brief Updates the scene on screen.
 *
 * \param[in] self  The scene to update
 * \param[in] window The window to update the scene to
 */
void updateScene(Scene *self, Window *window);

/**
 * \brief Updates the elements of the scene.
 *
 * \param[in] self The scene
 * \param[in] window The window to update to
 */
void updateSceneElements(Scene *self, Window *window);


/**
 * \brief Retrieves the name of the scene.
 *
 * \param[in] self The scene to get the name from
 *
 * \return The name of the scene
 */
str getSceneName(const Scene *self);

/**
 * \brief Modifies the name of the scene.
 *
 * \note The string is assigned without any copy.
 *
 * \param[in] self The scene to update the name of
 * \param[in] name The name to give to the scene
 */
void setSceneName(Scene *self, str name);

/**
 * \brief Determines whether a scene is a scene with user interface (as opposed
 *        to a game scene).
 *
 * \param[in] self The scene
 *
 * \return \c true if the scene is a UI scene
 */
bool isSceneUI(const Scene *self);


/**
 * \brief Adds a Sprite to the game scene.
 *
 * \param[in] self   The scene to add a sprite to
 * \param[in] sprite The sprite to add to the scene
 *
 * \return The index of the sprite in the scene, or \c 0 if an error occurred:
 *         lazy array allocation failed, or the scene is a UI scene
 *
 *\sa Sprite
 */
unsigned int addGameSceneSprite(Scene *self, Sprite *sprite);

/**
 * \brief Adds a UI element to the scene.
 *
 * \param[in] self    The scene to add an element to
 * \param[in] element The UI element to add
 *
 * \return The index of the sprite in the scene, or \c 0 if an error occurred:
 *         lazy array allocation failed, or the scene is a game scene
 *
 *\sa UIElement
 */
unsigned int addUISceneElement(Scene *self, UIElement *element);

/**
 * \brief Retrieves a Sprite by its index in the scene.
 *
 * \param[in] self  The scene to get a sprite from
 * \param[in] index The index of the sprite to get
 *
 * \return The \c index-th Sprite of the scene, or \c NULL if the index is
 *         invalid
 *
 * \sa Sprite
 */
Sprite *getGameSceneSprite(const Scene *self, unsigned int index);

/**
 * \brief Retrieves a Sprite by its position on the game scene
 *
 * \param[in] self  The scene to get the sprite from
 * \param[in] point The point where to look for a Sprite
 *
 * \return A Sprite from the scene that contains the given position or \c NULL
 *         if none does
 */
Sprite *getGameSceneSpritePos(const Scene *self, Point point);

/**
 * \brief Retrieves a Sprite by its position on screen
 *
 * \param[in] self  The scene to get the sprite from
 * \param[in] point The point where to look for a Sprite
 *
 * \return An UI element from the scene at the given position or \c NULL if no
 *         element qualifies
 */
UIElement *getUISceneElementPos(const Scene *self, Point point);

/**
 * \brief Remove a sprite from the scene
 *
 * \param[in] self   The scene to remove a sprite from
 * \param[in] sprite The sprite to remove from the scene
 *
 * \return \c true if the scene contained the sprite and it has been successfully
 *         removed
 */
bool removeGameSceneSprite(Scene *self, const Sprite *sprite);


#endif /* SCENE_H */
