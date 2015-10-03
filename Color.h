#ifndef COLOR_H
#define COLOR_H

#include "Arduino.h"

class Color
{
public:
	Color();
	Color(uint8_t _r, uint8_t _g, uint8_t _b);
	Color(uint32_t color);
	Color(const Color& color);

	void SetColor(uint8_t _r, uint8_t _g, uint8_t _b);
	void SetColor(uint32_t color);
	void SetColor(const Color& color);

public:
	static const Color Red, Green, Blue, White, Black, Magenta, Cyan, Yellow;

public:
	uint8_t r, g, b;
};

#endif
