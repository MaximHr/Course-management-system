/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#include "MessageFileHandler.h"
#include "../Components/Message/Message.h"

MessageFileHandler::MessageFileHandler(const String& str) : FileHandler(str) { }

void MessageFileHandler::saveMessage(const Message& message, FileHandler& fs) {
	if(!fs.isOpen()) throw std::runtime_error("file can not be opened");

	unsigned id = message.getId();
	unsigned recieverId = message.getRecieverId();
	unsigned senderId = message.getSenderId();

	fs.file.write((const char *)& id, sizeof(id));
	fs.file.write((const char *)& recieverId, sizeof(recieverId));
	fs.file.write((const char *)& senderId, sizeof(senderId));
	fs.write(message.getText());
	fs.write(message.getFormattedTime());
}

void MessageFileHandler::deleteMessages(unsigned recieverId) {
	std::fstream output(Config::fileNames(6).c_str(), std::ios::binary | std::ios::out);
	if(!output.is_open()) throw std::runtime_error("Failed to open temporary file for writing");

	int index = setAtBeginning();
	int bytes = 0;
	Message* message = readMessage(bytes);

	while(file) {
		if(message->getRecieverId() != recieverId) {
			copyBytes(output, bytes);
		};
		delete message;
		message = readMessage(bytes);
	}

	output.close();
	changeFile(Config::fileNames(6).c_str(), Config::fileNames(5).c_str());
	if(index < getFileSize()) {
		file.seekg(index);
	}
	delete message;
}

void MessageFileHandler::printMessages(unsigned recieverId) {
	if(!isOpen()) throw std::runtime_error("file cannot be opened");
	if(getFileSize() == 0) {
		std::cout << "There are no messages yet." << '\n';
		return;
	};

	int index = setAtBeginning();
	Message* message = readMessage();
	bool containsSubmissions = false;
	
	while(!file.eof()) {
		if(message->getRecieverId() == recieverId) {
			containsSubmissions = true;
			std::cout << *message;
		}
		delete message;
		message = readMessage();
	}
	if(!containsSubmissions) {
		std::cout << "There are no messages yet." << '\n';
	}

	file.clear();
	file.seekg(index);
	delete message;
}

int MessageFileHandler::findMessage(unsigned id) {
	if(!isOpen()) throw std::runtime_error("file cannot be opened");
	if(getFileSize() == 0) return -1;

	int index = setAtBeginning();
	Message* message = readMessage();
	int result = 0;

	while(message->getId() != id) {
		if(!file) {
			file.clear();
			delete message;
			return -1;
		}
		result = file.tellg();
		delete message;
		message = readMessage();
	}

	file.clear();
	file.seekg(index);
	delete message;

	return result;
}

Message* MessageFileHandler::readMessage() {
	if(!isOpen()) throw std::runtime_error("file can not be opened");

	Message* message = new Message();
	file.read((char *)& message->id, sizeof(message->id));
	file.read((char *)& message->recieverId, sizeof(message->recieverId));
	file.read((char *)& message->senderId, sizeof(message->senderId));
	read(message->text);
	read(message->formattedTime);

	return message;
}

Message* MessageFileHandler::readMessage(int& bytes) {
	int start = file.tellg();
	Message* message = readMessage();
	bytes = (int)file.tellg() - start;

	return message;
}