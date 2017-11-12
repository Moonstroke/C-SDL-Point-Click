
/*
 * File:   inventory.h
 * Author: joachim
 *
 * Created on 29 septembre 2017, 15:08
 */

#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct inventory *Inventory;

#include "sprite.h"
#include "types.h"


Inventory newinventory(CRect geometry, const size_t size, Texture background);

void freeinventory(Inventory inventory);


void updateinventory(const Inventory inventory, const Window window);


size_t inventorysize(const Inventory inventory);

Sprite getinventorysprite(const Inventory inventory, const ssize_t index);

size_t addinventorysprite(Inventory inventory, Sprite sprite);

bool removeinventorysprite(Inventory inventory, const Sprite sprite);


#endif /* INVENTORY_H */
