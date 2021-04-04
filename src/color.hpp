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

#endif