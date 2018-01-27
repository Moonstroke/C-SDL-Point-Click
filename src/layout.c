#include "layout.h"


bool setLayout(const Window *const w, const LayoutValues l, Rect *const sg, Rect *const ig, const unsigned int d) {
	const size_t winw = getWindowWidth(w), winh = getWindowHeight(w);
	switch(l) {
		case SCENE_ONLY:
			if(ig) {
				*ig = posRect(0, 0, 0, 0);
			}
			*sg = posRect(winw, winh, 0, 0);
			return true;
		case SCENE_INVENTORY_ABOVE:
			// TODO
			return false;
		case SCENE_INVENTORY_BELOW:
			if(d > winh)
				return false;
			*ig = posRect(winw, d, 0, winh - d);
			*sg = posRect(winw, winh - d, 0, 0);
			return true;
		case SCENE_INVENTORY_ON_LEFT:
			if(d > winw)
				return false;
			*ig = posRect(d, winh, 0, 0);
			*sg = posRect(winw - d, winh, 0, 0);
			return true;
		case SCENE_INVENTORY_ON_RIGHT:
			// TODO
			return false;
		default: break;
	}
	return false;
}
