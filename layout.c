#include "layout.h"

bool setwindowlayout(const Window w, const LayoutValues l, Rect sg, Rect ig, const unsigned int d) {
	const int winw = getwindoww(w), winh = getwindowh(w);
	switch(l) {
		case SCENE_ONLY:
			ig->x = ig->y = ig->w = ig->h = 0;
			sg->x = sg->y = 0, sg->w = winw, sg->h = winh;
			break;
		case SCENE_ABOVE_INVENTORY:
			if(d > winh)
				return false;
			ig->x = 0, ig->y = winh - d, ig->w = winw, ig->h = d;
			sg->x = sg->y = 0, sg->w = winw, sg->h = winw - d;
			break;
		case SCENE_INVENTORY_ON_LEFT:
			if(d > winw)
				return false;
			ig->x = ig->y = 0, ig->w = d, ig->h = winh;
			sg->x = d, sg->y = 0, sg->w = winw - d, sg->h = winh;
			break;
		default:
			return false;
	}
	return true;
}
