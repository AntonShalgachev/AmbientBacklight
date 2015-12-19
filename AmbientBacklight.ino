#include <Tlc5940.h>
#include "Color.h"
#include "LedControl.h"
#include "BrightnessControl.h"
#include "MessageHandler.h"

#define BAUD_RATE 9600

#define NUM_POT_READINGS 50

// Serial communication bytes
#define MSG_BEGIN 189

#define MSG_HANDSHAKE 253
#define MSG_SETLED 72
#define MSG_SETBACKGROUND 36
#define MSG_SETCOLORDATA 10
#define MSG_OK 29
#define MSG_WRONG_MSG 54
#define MSG_WRONG_LENDATA 55
#define MSG_FAIL 90

LedControl control(5);
BrightnessControl brightnessWhite(0, NUM_POT_READINGS);
BrightnessControl brightnessRGB(1, NUM_POT_READINGS);
MessageHandler handler(MSG_BEGIN);

void MsgHandshake(uint8_t len, uint8_t* data);
void MsgSetLED(uint8_t len, uint8_t* data);
void MsgSetBackground(uint8_t len, uint8_t* data);
void MsgSetColorData(uint8_t len, uint8_t* data);

void setup()
{
	Serial.begin(BAUD_RATE);

	control.Init();

	delay(100);

	// Init
	control.SetWhiteBrightness(0x00);
	control.Update();

	/*const Color initColors[] = {Color::Red, Color::Green, Color::Blue, Color::White};
	for(uint8_t i = 0; i < sizeof(initColors) / sizeof(*initColors); ++i)
	{
		const Color& col = initColors[i];
		control.SetRGBBackground(col);

		int16_t br = 0;
		int8_t delta = 5;

		while(br >= 0)
		{
			control.SetRGBBrightness(br);
			control.Update();

			br += delta;
			if(br > 255)
			{
				br = 255;
				delta = -delta;
			}

			delay(1);
		}
	}*/
	//int16_t r, g, b;
	//r = 0xFF;
	//g = 0x00;
	//b = 0x00;
	//int8_t delta = 2;

	//for(; g <= 0xFF; g += delta)
	//{
	//	control.SetRGBBackground(Color(r, g, b));
	//	control.Update();
	//	delay(1);
	//}
	//g = 0xFF;

	//for(; r >= 0x00; r -= delta)
	//{
	//	control.SetRGBBackground(Color(r, g, b));
	//	control.Update();
	//	delay(1);
	//}
	//r = 0x00;

	//for(; b <= 0xFF; b += delta)
	//{
	//	control.SetRGBBackground(Color(r, g, b));
	//	control.Update();
	//	delay(1);
	//}
	//b = 0xFF;

	//for(; g >= 0x00; g -= delta)
	//{
	//	control.SetRGBBackground(Color(r, g, b));
	//	control.Update();
	//	delay(1);
	//}
	//g = 0x00;

	//for(; r <= 0xFF; r += delta)
	//{
	//	control.SetRGBBackground(Color(r, g, b));
	//	control.Update();
	//	delay(1);
	//}
	//r = 0xFF;

	//for(; b >= 0x00; b -= delta)
	//{
	//	control.SetRGBBackground(Color(r, g, b));
	//	control.Update();
	//	delay(1);
	//}
	//b = 0x00;

	//for(; r >= 0x00; r -= delta)
	//{
	//	control.SetRGBBackground(Color(r, g, b));
	//	control.Update();
	//	delay(1);
	//}
	//r = 0x00;

	control.SetRGBBackground(Color::Cyan);
}

void loop()
{
	control.SetWhiteBrightness(brightnessWhite.GetNewReading());
	control.SetRGBBrightness(brightnessRGB.GetNewReading());

	control.Update();

	if(handler.Update())
	{
		control.SetRGBBackground(Color::Cyan);

		uint8_t len = handler.GetMessageDataLength();

		uint8_t msg;
		uint8_t* data = NULL;

		if(len > 0)
			data = new uint8_t[len];

		handler.GetMessage(&msg, data);

		switch(msg)
		{
		case MSG_HANDSHAKE:
			MsgHandshake(len, data);
			break;
		case MSG_SETLED:
			MsgSetLED(len, data);
			break;
		case MSG_SETBACKGROUND:
			MsgSetBackground(len, data);
			break;
		case MSG_SETCOLORDATA:
			MsgSetColorData(len, data);
			break;
		default:
			handler.SendMessage(MSG_WRONG_MSG, 0, NULL);
			break;
		}

		if(data)
		{
			delete[] data;
			data = NULL;
		}
	}

	delayMicroseconds(100);
}

void MsgHandshake(uint8_t len, uint8_t* data)
{
	if(len == 2 && data)
	{
		uint8_t responseData[2] = {data[1], data[0]};
		handler.SendMessage(MSG_HANDSHAKE, 2, responseData);
	}
	else
	{
		handler.SendMessage(MSG_WRONG_LENDATA, 0, NULL);
	}
}

void MsgSetLED(uint8_t len, uint8_t* data)
{
	if(len == 4 && data)
	{
		control.SetRGBLed(data[0], Color(data[1], data[2], data[3]));

		handler.SendMessage(MSG_OK, 0, NULL);
	}
	else
	{
		handler.SendMessage(MSG_WRONG_LENDATA, 0, NULL);
	}
}

void MsgSetBackground(uint8_t len, uint8_t* data)
{
	if(len == 3 && data)
	{
		control.SetRGBBackground(Color(data[0], data[1], data[2]));

		handler.SendMessage(MSG_OK, 0, NULL);
	}
	else
	{
		handler.SendMessage(MSG_WRONG_LENDATA, 0, NULL);
	}
}

void MsgSetColorData(uint8_t len, uint8_t* data)
{
	if(data)
	{
		for(uint8_t led = 0; led < len / 3; ++led)
		{
			Color col(data[3 * led + 0], data[3 * led + 1], data[3 * led + 2]);
			control.SetRGBLed(led, col);
		}

		handler.SendMessage(MSG_OK, 0, NULL);
	}
	else
	{
		handler.SendMessage(MSG_WRONG_LENDATA, 0, NULL);
	}
}
