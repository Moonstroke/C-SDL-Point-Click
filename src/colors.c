#include "colors.h"

#include "libmisc.h" /* for min and max */



extern uint32_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
extern uint32_t rgb(uint8_t r, uint8_t g, uint8_t b);

extern Color icolor(uint32_t color);
extern Color colora(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
extern Color color(uint8_t r, uint8_t g, uint8_t b);


Color blendColors(const Color *const c1, const Color *const c2, const MergeMode m) {
	Color res = {0};
	if(m & MERGE_BLEND_ALPHA) {
		const double a1 = c1->a, a2 = c2->a;
		const uint8_t r1 = c1->r * (a1 / 255.),
		              g1 = c1->g * (a1 / 255.),
		              b1 = c1->b * (a1 / 255.),
		              r2 = c2->r * (a2 / 255.),
		              g2 = c2->g * (a2 / 255.),
		              b2 = c2->b * (a2 / 255.);
		switch(m & ~MERGE_BLEND_ALPHA) {
			case MERGE_ADD:
				res.r = max(r1 + r2, 255);
				res.g = max(g1 + g2, 255);
				res.b = max(b1 + b2, 255);
				res.a = max((uint8_t)a1 + (uint8_t)a2, 255);
				break;
			case MERGE_MUL:
				res.r = max(r1 * r2, 255);
				res.g = max(g1 * g2, 255);
				res.b = max(b1 * b2, 255);
				res.a = max((uint8_t)a1 * (uint8_t)a2, 255);
				break;
			case MERGE_SUB:
				res.r = max(r1 - r2, 255);
				res.g = max(g1 - g2, 255);
				res.b = max(b1 - b2, 255);
				res.a = max((uint8_t)a1 - (uint8_t)a2, 255);
				break;
			default: break;
		}
	} else {
		switch(m) {
			case MERGE_ADD:
				res.r = max(c1->r + c2->r, 255);
				res.g = max(c1->g + c2->g, 255);
				res.b = max(c1->b + c2->b, 255);
				res.a = max(c1->a + c2->a, 255);
				break;
			case MERGE_MUL:
				res.r = max(c1->r * c2->r, 255);
				res.g = max(c1->g * c2->g, 255);
				res.b = max(c1->b * c2->b, 255);
				res.a = max(c1->a * c2->a, 255);
				break;
			case MERGE_SUB:
				res.r = max(c1->r - c2->r, 255);
				res.g = max(c1->g - c2->g, 255);
				res.b = max(c1->b - c2->b, 255);
				res.a = max(c1->a - c2->a, 255);
				break;
			default: break;
		}
	}
	return res;
}
