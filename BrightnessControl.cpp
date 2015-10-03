#include "BrightnessControl.h"

BrightnessControl::BrightnessControl(uint8_t _potPin, uint8_t _numReadings)
{
	potPin = _potPin;
	numReadings = _numReadings;

	readings = new uint8_t[numReadings];
	for(uint8_t i = 0; i < numReadings; ++i)
		readings[i] = 0;

	sum = 0;
	index = 0;
}

BrightnessControl::~BrightnessControl()
{
	delete[] readings;
}

uint8_t BrightnessControl::GetNewReading()
{
	sum -= readings[index];
	readings[index] = map(analogRead(potPin), 0, 1023, 0, 255);
	sum += readings[index];

	index = (index + 1) % numReadings;

	return sum / numReadings;
}
