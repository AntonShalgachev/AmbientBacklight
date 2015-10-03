#include "LedControl.h"

LedControl::LedControl(uint8_t _pinWhite) : pinWhite(_pinWhite)
{
	SetWhiteBrightness(0xFF);
	SetRGBBrightness(0xFF);

	SetRGBBackground(Color::Black);
}

void LedControl::Init()
{
	pinMode(pinWhite, OUTPUT);
	Tlc.init(0);
}

void LedControl::SetWhiteBrightness(uint8_t level)
{
	brightnessWhite = level;
}

void LedControl::SetRGBBrightness(uint8_t level)
{
	brightnessRGB = level;
}

void LedControl::SetRGBLed(uint8_t led, const Color& color)
{
	if(led >= 0 && led < LEDS)
		RGBColorData[led].SetColor(color);
}

void LedControl::SetRGBBackground(const Color& color)
{
	for(uint8_t led = 0; led < LEDS; ++led)
		SetRGBLed(led, color);
}

void LedControl::Update() const
{
	analogWrite(pinWhite, brightnessWhite);

	for(uint8_t led = 0; led < LEDS; ++led)
	{
		//Tlc.set(pinR[led], map(static_cast<long>(brightnessRGB)* RGBColorData[led].r * RED_MAX / 255, 0L, 255L * 255L, 0L, 4095L));
		//Tlc.set(pinG[led], map(static_cast<long>(brightnessRGB)* RGBColorData[led].g * GREEN_MAX / 255, 0L, 255L * 255L, 0L, 4095L));
		//Tlc.set(pinB[led], map(static_cast<long>(brightnessRGB)* RGBColorData[led].b * BLUE_MAX / 255, 0L, 255L * 255L, 0L, 4095L));

		Tlc.set(pinR[led], (4095ULL * brightnessRGB * RGBColorData[led].r * RED_MAX) / (255UL * 255 * 255));
		Tlc.set(pinG[led], (4095ULL * brightnessRGB * RGBColorData[led].g * GREEN_MAX) / (255UL * 255 * 255));
		Tlc.set(pinB[led], (4095ULL * brightnessRGB * RGBColorData[led].b * BLUE_MAX) / (255UL * 255 * 255));
	}
	Tlc.update();
}
