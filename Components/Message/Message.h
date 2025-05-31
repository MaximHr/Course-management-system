/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#pragma once
#include "../../Utils/String.h"
#include "../../Users/User.h"
#include "../../FileHandlers/MessageFileHandler.h"
#include <iostream>
#include <fstream>
#include <ctime>

class Message {
	String text;
	String formattedTime;
	unsigned id;
	unsigned recieverId;
	unsigned senderId;
	
	friend Message* MessageFileHandler::readMessage();
	void setTime();
public:
	Message() = default;
	Message(unsigned id, const String& text, unsigned recieverId, unsigned senderId);
	const String& getText() const;
	const String& getFormattedTime() const;
	unsigned getSenderId() const;
	unsigned getRecieverId() const;
	unsigned getId() const;
};

std::ostream& operator<<(std::ostream& output, const Message& message);