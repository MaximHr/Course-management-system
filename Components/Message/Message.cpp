/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#include "Message.h"

Message::Message(unsigned id, const String& text, unsigned recieverId, unsigned senderId) : 
	id(id), text(text), recieverId(recieverId), senderId(senderId) 
{
	setTime();
}

const String& Message::getText() const {
	return text;
}

unsigned Message::getSenderId() const {
	return senderId;
}

unsigned Message::getRecieverId() const {
	return recieverId;
}

unsigned Message::getId() const {
	return id;
}

const String& Message::getFormattedTime() const {
	return formattedTime;
}

void Message::setTime() {
	time_t now;
	time(&now);
	formattedTime = ctime(&now);
	formattedTime = formattedTime.remove(16, 3); //removes the seconds
}

std::ostream& operator<<(std::ostream& output, const Message& message) {
	output<< message.getFormattedTime() 
				<< message.getText()
				<< "\n______________________\n";
				 
	return output;
}