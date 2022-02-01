#pragma once

class MessageBridgeBase
{
public:
	virtual uint8_t Initialize() = 0;
	virtual uint8_t Finalize() = 0;
	virtual uint8_t SendMessage(const char* message) = 0;
};