#include "UserFileHandler.h"
#include "User.h"
#include "CommandHandler.h"
#include "UserFactory.h"

UserFileHandler::UserFileHandler(const String& str):FileHandler(str) { }

void UserFileHandler::saveUser(const User* user) {
	if(!isOpen()) throw std::runtime_error("file can not be opened");
	UserType type = user->getRole();

	write((const char*)& type, sizeof(UserType));
	write(user->getFirstName());
	write(user->getLastName());
	write(user->getHashedPassword());
	unsigned id = user->getId();
	write((const char*)& id, sizeof(unsigned));
}

User* UserFileHandler::readUser() {
	UserType role = UserType::Admin;
	read((char*)& role, sizeof(UserType));
	User* newUser = UserFactory::createUser(role);

	read(newUser->firstName);
	read(newUser->lastName);
	read(newUser->hashedPassword);
	read((char*)& newUser->id, sizeof(unsigned));

	return newUser;
}

User* UserFileHandler::readUser(int& sizeInBytes) {
	int start = file.tellg();
	User* user = readUser();
	sizeInBytes = (int)file.tellg() - start;

	return user;
}

int UserFileHandler::findUser(unsigned id, const String& hashedPassword, bool searchForIdOnly) {
	if(!isOpen()) throw std::runtime_error("file can not be opened");
	if(getFileSize() == 0) return -1;

	int index = file.tellg();
	file.seekg(0);
	User* tempUser = readUser();
	int result = 0;
	while (
    (searchForIdOnly && tempUser->getId() != id) ||
    (!searchForIdOnly && (tempUser->getId() != id || tempUser->getHashedPassword() != hashedPassword))
	) {
		if(file.eof()) {
			file.clear();
			delete tempUser;
			return -1;
		}
		result = file.tellg();
		delete tempUser;
		tempUser = readUser();
	}

	file.clear();
	file.seekg(index);
	delete tempUser;
	return result;
}

void UserFileHandler::deleteUser(unsigned userId) {
	std::ofstream ofs(tempFileName.c_str(), std::ios::binary);
	if(!ofs.is_open()) throw std::runtime_error("Failed to open temporary file for writing");

	int index = file.tellg();
	file.seekg(0);

	int bytes = 0;
	User* tempUser = readUser(bytes);
	while(file) {
		if(tempUser->getId() != userId) {
			copyBytes(ofs, bytes);
		};
		delete tempUser;
		tempUser = readUser(bytes);
	}

	ofs.close();
	changeFile(tempFileName.c_str(), usersFileName.c_str());
	if(index < getFileSize()) {
		file.seekg(index);
	}
	delete tempUser;
}

int UserFileHandler::getLastId() {
	int lastId = 100;

	return lastId;
}
