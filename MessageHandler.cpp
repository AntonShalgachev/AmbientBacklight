#include "MessageHandler.h"

MessageHandler::MessageHandler(uint8_t msgBegin)
{
	_data = NULL;
	_msg = 0;
	_len = 0;
	_handled = true;
	_msgBegin = msgBegin;
}

bool MessageHandler::Update()
{
	if(_handled)
	{
		if(_msg == 0) // Waiting for the message
		{
			if(Serial.available() >= 3)
			{
				if(Serial.read() == _msgBegin)
				{
					_msg = Serial.read();
					_len = Serial.read();

					if(_data)
					{
						delete[] _data;
						_data = NULL;
					}

					if(_len > 0)
					{
						_data = new uint8_t[_len];
					}
					else
					{
						_handled = false;
					}
				}
			}
		}
		else // Message received, retrieving data
		{
			if(Serial.available() >= _len && _data != NULL)
			{
				Serial.readBytes(_data, _len);
				_handled = false;
			}
		}
	}

	return (_handled == false);
}

uint8_t MessageHandler::GetMessageDataLength() const
{
	return _len;
}

void MessageHandler::GetMessage(uint8_t* msg, uint8_t* data)
{
	*msg = _msg;
	if(data && _data)
		memcpy(data, _data, _len);

	if(_data)
	{
		delete[] _data;
		_data = NULL;
	}
	_msg = 0;
	_len = 0;
	_handled = true;
}

void MessageHandler::SendMessage(uint8_t msg, uint8_t len, uint8_t* data)
{
	uint8_t query[] = {_msgBegin, msg, len};
	Serial.write(query, sizeof(query) / sizeof(uint8_t));

	if(len > 0 && data)
	{
		Serial.write(data, len);
	}
}
