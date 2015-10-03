#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include <Arduino.h>
#include <Tlc5940.h>
#include "Color.h"

#define LEDS 24

#define RED_MAX 255
#define GREEN_MAX 100
#define BLUE_MAX 70

static const uint8_t pinR[LEDS] = {68, 70, 9, 27, 6, 44, 20, 54, 65, 52, 31, 63, 28, 13, 49, 40, 38, 18, 12, 2, 32, 35, 43, 41};
static const uint8_t pinG[LEDS] = {60, 62, 26, 15, 7, 42, 10, 59, 51, 56, 1, 64, 34, 53, 47, 61, 45, 22, 23, 30, 25, 67, 29, 21};
static const uint8_t pinB[LEDS] = {71, 69, 8, 11, 4, 14, 17, 57, 66, 58, 46, 33, 3, 50, 55, 36, 48, 37, 16, 5, 24, 39, 0, 19};

class LedControl
{
public:
	LedControl(uint8_t _pinWhite);

	void Init();

	void SetWhiteBrightness(uint8_t level);
	void SetRGBBrightness(uint8_t level);

	void SetRGBLed(uint8_t led, const Color& color);
	void SetRGBBackground(const Color& color);

	void Update() const;

private:
	uint8_t pinWhite;

	uint8_t brightnessWhite;
	uint8_t brightnessRGB;

	Color RGBColorData[LEDS];
};

#endif
