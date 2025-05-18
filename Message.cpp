#include "Message.h"

const String& Message::getText() const {
	return text;
}

const User* Message::getSender() const {
	return sender;
}

const String& Message::getFormattedTime() const {
	return formattedTime;
}

void Message::setTime() {
	time_t now;
	time(&now);
	formattedTime = ctime(&now);
	formattedTime = formattedTime.remove(16, 3); //removes the seconds
	formattedTime.pop();
}

Message::Message(const User* user):sender(user) {
	setTime();
};

Message::Message(const String& text, const User* user):text(text), sender(sender) { 
	setTime();
}

std::istream& operator>>(std::istream& input, Message& message) {
	std::cout << "Type your message: ";
	input >> message.text;
	message.setTime();

	return input;
}

std::ostream& operator<<(std::ostream& output, const Message& message) {
	output << message.getFormattedTime() << " | "
				 << message.getSender()->getFirstName() << " " 
				 << message.getSender()->getLastName() << ": " 
				 << message.getText() << '\n';
				 
	return output;
}