#include "UserFileHandler.h"
#include "../Users/User.h"
#include "../Users/UserFactory.h"
#include "../Utils/Config.h"

UserFileHandler::UserFileHandler(const String& str) : FileHandler(str) {
	if(findUserWithPassword(Config::adminId, Config::adminPassword().reverse()) == -1) {
		User* newUser = UserFactory::createUser(UserType::Admin);
		saveUser(newUser);
		delete newUser;
	}
}

void UserFileHandler::saveUser(const User* user) {
	if(!isOpen()) throw std::runtime_error("file can not be opened");
	UserType type = user->getRole();

	file.write((const char*)& type, sizeof(UserType));
	write(user->getFirstName());
	write(user->getLastName());
	write(user->getHashedPassword());
	unsigned id = user->getId();
	file.write((const char*)& id, sizeof(unsigned));
	file.flush();
}

User* UserFileHandler::readUser() {
	UserType role;

	file.read((char*)& role, sizeof(UserType));
	User* newUser = UserFactory::createUser(role);
	read(newUser->firstName);
	read(newUser->lastName);
	read(newUser->hashedPassword);
	file.read((char*)& newUser->id, sizeof(unsigned));

	return newUser;
}

User* UserFileHandler::getUserMatcher(unsigned id, const String& hashedPassword, bool shouldCheckForPassword) {
	int pos = -1;
	if(!shouldCheckForPassword) {
		pos = findUser(id);
	} else {
		pos = findUserWithPassword(id, hashedPassword);
	}
	if(pos == -1)  {
		throw std::runtime_error("User with that id was not found");
	}

	int current = file.tellg();
	file.seekg(pos);
	User* user = readUser();
	file.seekg(current);
	return user;
}

User* UserFileHandler::getUser(unsigned id) {
	return getUserMatcher(id, "", false);
}

User* UserFileHandler::getUserByPassword(unsigned id, const String& hashedPassword) {
	return getUserMatcher(id, hashedPassword, true);
}

User* UserFileHandler::readUser(int& sizeInBytes) {
	int start = file.tellg();
	User* user = readUser();
	sizeInBytes = (int)file.tellg() - start;

	return user;
}

int UserFileHandler::findUser(unsigned id) {
	return findUserMatcher(id, "", false);
}

int UserFileHandler::findUserWithPassword(unsigned id, const String& hashedPassword) {
	return findUserMatcher(id, hashedPassword, true);
}

int UserFileHandler::findUserMatcher(unsigned id, const String& hashedPassword, bool shouldCheckPassword) {
	if(!isOpen()) throw std::runtime_error("file cannot be opened");
	if(getFileSize() == 0) return -1;

	int index = setAtBeginning();
	User* tempUser = readUser();
	int result = 0;

	while (
		(shouldCheckPassword && (tempUser->getId() != id || tempUser->getHashedPassword() != hashedPassword))
		|| (!shouldCheckPassword && (tempUser->getId() != id))
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

void UserFileHandler::deleteUser(unsigned id) {
	std::fstream output(Config::fileNames(6).c_str(), std::ios::binary | std::ios::out);
	if(!output.is_open()) throw std::runtime_error("Failed to open temporary file for writing");

	int index = setAtBeginning();
	int bytes = 0;
	User* tempUser = readUser(bytes);

	while(file) {
		if(tempUser->getId() != id) {
			copyBytes(output, bytes);
		};
		delete tempUser;
		tempUser = readUser(bytes);
	}

	output.close();
	changeFile(Config::fileNames(6).c_str(), Config::fileNames(0).c_str());
	if(index < getFileSize()) {
		file.seekg(index);
	}
	delete tempUser;
}