/**
 * \file layout.h
 * \author joH1
 *
 * This file contains constant values representing the spatial organization of
 * the game window, with the position of the scene and inventory, and their
 * behaviours.
*/

#ifndef LAYOUT_H
#define LAYOUT_H


#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "window.h"



/**
 * \enum LayoutValues
 *
 * \brief Constants that represent the layout of the game screen: position
          and/or presence of the inventory and game scene.
 */

/**
 * \var LayoutValues SCENE_ONLY
 *
 * The screen is a plain scene, no inventory:
 * +-------------------------------+
 * |                               |
 * |                               |
 * |                               |
 * |             SCENE             |
 * |                               |
 * |                               |
 * |                               |
 * +-------------------------------+
 */

/**
 * \var LayoutValues SCENE_INVENTORY_BELOW
 *
 * The inventory is below the scene:
 * +-------------------------------+
 * |                               |
 * |                               |
 * |             SCENE             |
 * |                               |
 * |                               |
 * +-------------------------------+
 * |           INVENTORY           |
 * +-------------------------------+
 */

/**
 * \var LayoutValues SCENE_INVENTORY_ABOVE
 *
 * The inventory is above the scene:
 * +-------------------------------+
 * |           INVENTORY           |
 * +-------------------------------+
 * |                               |
 * |                               |
 * |             SCENE             |
 * |                               |
 * |                               |
 * +-------------------------------+
 */

/**
 * \var LayoutValues SCENE_INVENTORY_ON_LEFT
 *
 * The inventory is on the left of the scene:
 * +---+---------------------------+
 * |   |                           |
 * |   |                           |
 * |INV|                           |
 * |ENT|           SCENE           |
 * |ORY|                           |
 * |   |                           |
 * |   |                           |
 * +---+---------------------------+
 */

/**
 * \var LayoutValues SCENE_INVENTORY_ON_RIGHT
 *
 * The inventory is on the right of the scene:
 * +---------------------------+---+
 * |                           |   |
 * |                           |   |
 * |                           |INV|
 * |           SCENE           |ENT|
 * |                           |ORY|
 * |                           |   |
 * |                           |   |
 * +---------------------------+---+
 */

/**
 * \var LayoutValues SCENE_HIDE_INVENTORY
 *
 * This is a special value that indicate that the inventory should wrap itself
 * when not in focus.
 *
 * \c OR it with any other value -- except \c SCENE_ONLY, obviously.
 */
typedef enum {
	SCENE_ONLY = 0,
	SCENE_INVENTORY_BELOW,
	SCENE_INVENTORY_ABOVE,
	SCENE_INVENTORY_ON_LEFT,
	SCENE_INVENTORY_ON_RIGHT,

	SCENE_HIDE_INVENTORY = 8
} LayoutValues;

/**
 * \brief Sets the layout of the window with a value, or a combination of values of the above \c enum
 *
 * \param window        The window to set layout of
 * \param layout        The layout value to set to the window
 * \param scenegeom     The geometry of the scene (width, height and position)
 * \param inventorygeom The geometry ofh the inventory
 * \param inventorywh   The dimension to set to the inventory:
 *                      width if layout is vertical, or height if horizontal
 */
bool setlayout(const Window *window, LayoutValues layout, Rect *scenegeom, Rect *inventorygeom, size_t inventorywh);

#endif /* LAYOUT_H */
