#include "Color.h"

Color::Color()
{
	SetColor(0, 0, 0);
}

Color::Color(uint8_t _r, uint8_t _g, uint8_t _b) : r(_r), g(_g), b(_b)
{
	SetColor(_r, _g, _b);
}

Color::Color(uint32_t color)
{
	SetColor(color);
}

Color::Color(const Color& color)
{
	SetColor(color);
}

void Color::SetColor(uint8_t _r, uint8_t _g, uint8_t _b)
{
	r = _r;
	g = _g;
	b = _b;
}

void Color::SetColor(uint32_t color)
{
	SetColor((color >> 16) & 0xFF, (color >> 8) & 0xFF, (color)& 0xFF);
}

void Color::SetColor(const Color& color)
{
	SetColor(color.r, color.g, color.b);
}

const Color Color::Red = Color(0xFF0000);
const Color Color::Green = Color(0x00FF00);
const Color Color::Blue = Color(0x0000FF);
const Color Color::White = Color(0xFFFFFF);
const Color Color::Black = Color(0x000000);
const Color Color::Magenta = Color(0xFF00FF);
const Color Color::Cyan = Color(0x00FFFF);
const Color Color::Yellow = Color(0xFFFF00);
