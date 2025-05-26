#pragma once
#include "../Utils/String.h"
#include "FileHandler.h"
class Message;

struct MessageFileHandler:FileHandler {
	MessageFileHandler() = default;
	MessageFileHandler(const String& str);
	void sendTo(int recieverId, const Message& message);
	// void sentToCourse(, const Message& message);
	void viewMessage(int recieverId);
	void sentToEveryone(const Message& message);
};