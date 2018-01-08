#include "layout.h"


bool setLayout(const Window *const w, const LayoutValues l, Rect *const sg, Rect *const ig, const unsigned int d) {
	const size_t winw = getWindowWidth(w), winh = getWindowHeight(w);
	switch(l) {
		case SCENE_ONLY:
			if(ig) {
				*ig = rect(0, 0, 0, 0);
			}
			*sg = rect(winw, winh, 0, 0);
			return true;
		case SCENE_INVENTORY_ABOVE:
			// TODO
			return false;
		case SCENE_INVENTORY_BELOW:
			if(d > winh)
				return false;
			*ig = rect(winw, d, 0, winh - d); //ig->x = 0, ig->y = winh - d, ig->w = winw, ig->h = d;
			*sg = rect(winw, winw - d, 0, 0); //sg->x = sg->y = 0, sg->w = winw, sg->h = winw - d;
			return true;
		case SCENE_INVENTORY_ON_LEFT:
			if(d > winw)
				return false;
			*ig = rect(d, winh, 0, 0); //ig->x = ig->y = 0, ig->w = d, ig->h = winh;
			*sg = rect(winw - d, winh, 0, 0); //sg->x = d, sg->y = 0, sg->w = winw - d, sg->h = winh;
			return true;
		case SCENE_INVENTORY_ON_RIGHT:
			// TODO
			return false;
		default: break;
	}
	return false;
}
