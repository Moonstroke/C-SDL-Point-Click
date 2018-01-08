/**
 * \file inventory.h
 * \author joH1
 *
 * \version 0.1
 *
 * \brief The Inventory, area where are gathered items collected throughout the
 *        game.
 *
 * This file contains the definition of the game inventory, used to store
 * the items collected while playing.
 */

#ifndef INVENTORY_H
#define INVENTORY_H


#include "libmisc.h" /* for str and padding() */
#include "geom.h" /* for Rect and Point */



/**
 * \brief This structure represents the player's inventory where gathered items
 *        are stored for later use.
 */
typedef struct inventory Inventory;


#include "sprite.h"
#include "texture.h"



/**
 * \brief This function constructs a new inventory for the game.
 *
 * \param[in] geometry   The dimensions and position to set to the inventory
 * \param[in] size       The initial number of elements in the inventory
 * \param[in] background The background texture of the inventory
 *
 * \return A new inventory of set geometry, size and background
 *
 * \remark Usually, there is only one inventory in game.
 */
Inventory *newInventory(const Rect *geometry, size_t size, Texture *background);

/**
 * \brief Destroys and frees memory of the game inventory.
 *
 * \param[in] self The inventory to deallocate
 */
void freeInventory(Inventory *self);


/**
 * \brief Graphically updates the inventory:
 *        Updates it and its elements on screen.
 *
 * \param[in] self   The inventory to update
 * \param[in] window The window to update the inventory to
 */
void updateInventory(const Inventory *self, Window *window);


/**
 * \brief Returns the number of elements in the inventory.
 *
 * \param[in] self The inventory to get the size of
 *
 * \return The size of the game inventory, i.e. the number of items it holds.
 */
size_t inventorySize(const Inventory *self);

/**
 * \brief Returnes the \c index'th element of the inventory.
 *
 * \param[in] self  The inventory to get the sprite from
 * \param[in] index The index at which get the sprite
 *
 * \return An element of the inventory, identified by its position.
 */
Sprite *getInventorySprite(const Inventory *self, ssize_t index);

/**
 * \brief Adds an item to the inventory.
 *
 * \param[in] self   The inventory to add a sprite to
 * \param[in] sprite The sprite to add to the inventory
 *
 * \return The index of the added element, or \c -1 if an error occurred.
 */
size_t addInventorySprite(Inventory *self, Sprite *sprite);

/**
 * \brief Removes an element of the inventory.
 *
 * \param[in] self   The inventory to alleviate from one element
 * \param[in] sprite The sprite to remove
 *
 * \return \c true if the item was successfully removed.
 */
bool removeInventorySprite(Inventory *self, const Sprite *sprite);

/**
 * \brief Retrieve a Sprite from the inventory based on his position in the
 *        window.
 *
 * \param[in] self The inventory
 * \param[in] pos The position
 *
 * \return The sprite from the inventory at given position, or \c NULL if there
 *         is none or position is invalid.
 */
Sprite *getInventorySpritePos(const Inventory *self, Point pos);

#endif /* INVENTORY_H */
