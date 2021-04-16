#ifndef _COLOR_H_
#define _COLOR_H_

#include <cstdint>

class Color { // Make Color Manipulation easy 
public:
	Color();
	Color(uint8_t, uint8_t, uint8_t, uint8_t);
	~Color();
	uint8_t r, g, b, a;
	// overload color equality 
	inline bool operator==(const Color &c){return this->r == c.r && this->g == c.g && this->b == c.b && this->a == c.a;}
	// overload color inequality 
	inline bool operator!=(const Color &c){return this->r != c.r || this->g != c.g || this->b != c.b || this->a != c.a;}
};

const Color CYAN = Color(0, 255, 255, 255);
const Color BLUE = Color(0, 0, 255, 255);
const Color ORANGE = Color(255, 165, 0, 255);
const Color YELLOW = Color(255, 255, 0, 255);
const Color GREEN = Color(0, 255, 0, 255);
const Color PURPLE = Color(128, 0, 128, 255);
const Color RED = Color(255, 0, 0, 255);
const Color BLACK = Color(0, 0, 0, 255);
const Color WHITE = Color(255, 255, 255, 255);
const Color GREY = Color(120, 120, 120, 255);

#endif
