#pragma once
#include "String.h"
#include "User.h"
#include <iostream>
#include <fstream>
#include <ctime>

class Message {
	String text;
	const User* sender;
	void setTime();
	String formattedTime;
	int recieverId;
public:
	Message() = default;
	Message(const User* sender);
	Message(const String& text, const User* sender);
	const String& getText() const;
	const String& getFormattedTime() const;
	const User* getSender() const;
	friend std::istream& operator>>(std::istream& input, Message& message);
};

std::istream& operator>>(std::istream& input, Message& message);
std::ostream& operator<<(std::ostream& output, const Message& message);