#ifndef BRIGHTNESS_CONTROL_H
#define BRIGHTNESS_CONTROL_H

#include <Arduino.h>

class BrightnessControl
{
public:
	BrightnessControl(uint8_t _potPin, uint8_t _numReadings);
	~BrightnessControl();

	uint8_t GetNewReading();

private:
	uint8_t potPin;
	uint8_t numReadings;

	uint8_t* readings;
	uint8_t index;
	uint16_t sum;
};

#endif
