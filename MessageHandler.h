#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <Arduino.h>

class MessageHandler
{
public:
	MessageHandler(uint8_t msgBegin);

	bool Update(); // Check for any messages and return TRUE only if message is completely received
	uint16_t GetMessageDataLength() const;
	void GetMessage(uint8_t* msg, uint8_t* data);

	void SendMessage(uint8_t msg, uint16_t len, uint8_t* data);

private:
	uint8_t* _data;
	uint8_t _msg;
	uint16_t _len;
	bool _handled;
	uint8_t _msgBegin;
};

#endif
