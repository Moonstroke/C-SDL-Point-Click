
/*
 * File:   inventory.h
 * Author: joachim
 *
 * Created on 29 septembre 2017, 15:08
 */

#ifndef INVENTORY_H
#define INVENTORY_H

/**
 * \struct Inventory
 *
 * \brief This structure represents the player's inventory where gathered items
 *        are stored for later use.
 */
typedef struct inventory *Inventory;
typedef const struct inventory *CInventory;

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
Inventory newinventory(Rect geometry, size_t size, Texture background);

/**
 * \brief Destroys and frees memory of the game inventory.
 */
void freeinventory(Inventory self);


/**
 * \brief Graphically updates the inventory:
 *        Updates it and its elements on screen.
 *
 * \param inventory
 */
void updateinventory(CInventory self, Window window);


/**
 * \brief Returns the number of elements in the inventory.
 *
 * \return The size of the game inventory, i.e. the number of items it holds.
 */
size_t inventorysize(CInventory self);

/**
 * \brief Returnes the \c index'th element of the inventory.
 *
 * \return An element of the inventory, iddentified by its position.
 */
Sprite getinventorysprite(CInventory self, ssize_t index);

/**
 * \brief Adds an item to the inventory.
 *
 * \return The index of the added element, or \c -1 if an error occurred.
 */
size_t addinventorysprite(Inventory self, Sprite sprite);

/**
 * \brief Removes an element of the inventory.
 *
 * \return \c TRUE if the item was successfully removed.
 */
bool removeinventorysprite(Inventory self, CSprite sprite);


#endif /* INVENTORY_H */
