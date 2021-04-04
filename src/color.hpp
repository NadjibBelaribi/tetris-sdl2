#ifndef _COLOR_H
#define _COLOR_H

class Color ;
#include <cstdint>

class Color {
public:
	Color();
	Color(uint8_t, uint8_t, uint8_t, uint8_t);
	~Color();
	bool operator==(const Color &)   ;
	bool operator!=(const Color &)   ;
private :
	uint8_t r, g, b, a;
};

// Colors used 
const Color BLACK = Color(0, 0, 0, 255);
const Color WHITE = Color(255, 255, 255, 255);
const Color GREY = Color(120, 120, 120, 255);

const Color CYAN = Color(0, 255, 255, 255);
const Color BLUE = Color(0, 0, 255, 255);
const Color ORANGE = Color(255, 165, 0, 255);
const Color YELLOW = Color(255, 255, 0, 255);
const Color GREEN = Color(0, 255, 0, 255);
const Color PURPLE = Color(128, 0, 128, 255);
const Color RED = Color(255, 0, 0, 255);


#endif