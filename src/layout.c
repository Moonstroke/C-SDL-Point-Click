#include "layout.h"


bool setLayout(const Window *const w, const LayoutValues l, Rect *const sg, Rect *const ig, const unsigned int d) {
	const size_t winw = getWindowWidth(w), winh = getWindowHeight(w);
	switch(l) {
		case SCENE_ONLY:
			if(ig) {
				ig->x = ig->y = ig->w = ig->h = 0;
			}
			sg->x = sg->y = 0, sg->w = winw, sg->h = winh;
			return true;
		case SCENE_INVENTORY_ABOVE:
			// TODO
			return false;
		case SCENE_INVENTORY_BELOW:
			if(d > winh)
				return false;
			ig->x = 0, ig->y = winh - d, ig->w = winw, ig->h = d;
			sg->x = sg->y = 0, sg->w = winw, sg->h = winw - d;
			return true;
		case SCENE_INVENTORY_ON_LEFT:
			if(d > winw)
				return false;
			ig->x = ig->y = 0, ig->w = d, ig->h = winh;
			sg->x = d, sg->y = 0, sg->w = winw - d, sg->h = winh;
			return true;
		case SCENE_INVENTORY_ON_RIGHT:
			// TODO
			return false;
	}
	return false;
}
