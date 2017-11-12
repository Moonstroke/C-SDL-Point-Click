#ifndef LAYOUT_H
#define LAYOUT_H


#include <stdbool.h>
#include <SDL2/SDL_rect.h>


#include "window.h"


/* Layout constants */
typedef enum {

	/**
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
	SCENE_ONLY = 0,

	/**
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
	SCENE_ABOVE_INVENTORY,

	/**
	 * +---+---------------------------+
	 * |   |                           |
	 * |   |                           |
	 * |INV|                           |
	 * |ENT|         SCENE             |
	 * |ORY|                           |
	 * |   |                           |
	 * |   |                           |
	 * +---+---------------------------+
	 */
	SCENE_INVENTORY_ON_LEFT
} LayoutValues;

bool setwindowlayout(const Window window, const LayoutValues layout, Rect scenegeom, Rect inventorygeom, const unsigned int inventorywh);

#endif /* LAYOUT_H */
