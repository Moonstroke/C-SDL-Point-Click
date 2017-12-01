/**
 * \file inventory.h
 * \author joH1
 *
 * This file contains the definition of the game inventory, used to store
 * the items collected while playing.
 */

#ifndef INVENTORY_H
#define INVENTORY_H

/**
 * \brief This structure represents the player's inventory where gathered items
 *        are stored for later use.
 */
typedef struct inventory Inventory;

#include "sprite.h"
#include "types.h"

/**
 * \brief This function constructs a new inventory for the game.
 *
 * \param[in] geometry   The dimensions and position to set to the inventory
 * \param[in] size       The initial number of elements in the inventory
 * \param[in] background The background texture of the inventory
 *
 * \remark Usually, there is only one inventory in game.
 */
Inventory *newinventory(Rect geometry, size_t size, Texture *background);

/**
 * \brief Destroys and frees memory of the game inventory.
 *
 * \param[in] self The inventory to deallocate
 */
void freeinventory(Inventory *self);


/**
 * \brief Graphically updates the inventory:
 *        Updates it and its elements on screen.
 *
 * \param[in] self   The inventory to update
 * \param[in] window The window to update the inventory to
 */
void updateinventory(const Inventory *self, Window *window);


/**
 * \brief Returns the number of elements in the inventory.
 *
 * \param[in] self The inventory to get the size of
 *
 * \return The size of the game inventory, i.e. the number of items it holds.
 */
size_t inventorysize(const Inventory *self);

/**
 * \brief Returnes the \c index'th element of the inventory.
 *
 * \param[in] self  The inventory to get the sprite from
 * \param[in] index The index at which get the sprite
 *
 * \return An element of the inventory, identified by its position.
 */
Sprite *getinventorysprite(const Inventory *self, ssize_t index);

/**
 * \brief Adds an item to the inventory.
 *
 * \param[in] self   The inventory to add a sprite to
 * \param[in] sprite The sprite to add to the inventory
 *
 * \return The index of the added element, or \c -1 if an error occurred.
 */
size_t addinventorysprite(Inventory *self, Sprite *sprite);

/**
 * \brief Removes an element of the inventory.
 *
 * \param[in] self   The inventory to alleviate from one element
 * \param[in] sprite The sprite to remove
 *
 * \return \c true if the item was successfully removed.
 */
bool removeinventorysprite(Inventory *self, const Sprite *sprite);


#endif /* INVENTORY_H */
