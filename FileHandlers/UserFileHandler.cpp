/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#include "UserFileHandler.h"
#include "../Users/User.h"
#include "../Users/UserFactory.h"
#include "../Utils/Config.h"
#include "../System/System.h"

UserFileHandler::UserFileHandler(const String& str) : FileHandler(str) {
	if(findUserWithPassword(Config::adminId, Config::adminPassword().reverse()) == -1) {
		User* newUser = UserFactory::createUser(UserType::Admin);
		saveUser(newUser, *this);
		delete newUser;
	}
}

void UserFileHandler::saveUser(const User* user, FileHandler& fs) {
	if(user == nullptr) throw std::invalid_argument("User can not be null pointer");
	if(!fs.isOpen()) throw std::runtime_error("file can not be opened");
	UserType type = user->getRole();

	fs.file.write((const char*)& type, sizeof(UserType));
	fs.write(user->getFirstName());
	fs.write(user->getLastName());
	fs.write(user->getHashedPassword());
	unsigned id = user->getId();
	fs.file.write((const char*)& id, sizeof(unsigned));
	fs.file.flush();
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
		throw std::runtime_error("User was not found.");
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
	updateUserMatcher(id, nullptr);
}

void UserFileHandler::updateUser(unsigned id, const User* updatedUser) {
	updateUserMatcher(id, updatedUser);
}

void UserFileHandler::updateUserMatcher(unsigned id, const User* updatedUser) {
	FileHandler output(Config::fileNames(6).c_str());
	if(!output.isOpen()) throw std::runtime_error("Failed to open temporary file for writing");

	int index = setAtBeginning();
	int bytes = 0;
	User* tempUser = readUser(bytes);

	while(file) {
		if(tempUser->getId() != id) {
			copyBytes(output.file, bytes);
		} else {
			if(updatedUser != nullptr) {
				saveUser(updatedUser, output);
			}
		}
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

void UserFileHandler::messageCourse(const String& text, unsigned courseId) {
	messageGroup(text, Group::Course, courseId);
}

void UserFileHandler::messageAll(const String& text) {
	messageGroup(text, Group::All, -1);
}

void UserFileHandler::messageGroup(const String& text, Group groupType, unsigned id) {
	if(!isOpen()) throw std::runtime_error("file cannot be opened");
	if(getFileSize() == 0) return;

	int index = setAtBeginning();
	User* tempUser = readUser();
	System& system = System::getInstance();
	
	while(!file.eof()) {
		if(tempUser->getId() != system.getUserId()) {
			if(groupType == Group::All) {
				system.messageUser(tempUser->getId(), text);
			} else if (groupType == Group::Course) {
				Course* course = system.courseFileHandler.getCourse(id);
				if(course->getOwnerId() != system.getUserId()) {
					throw std::runtime_error("You are not the owner of this course");
				}
				if(system.courseFileHandler.findStudentId(id, tempUser->getId(), course->getStudentsCount())) {
					system.messageUser(tempUser->getId(), text);
				}
				delete course;
			}
		}

		delete tempUser;
		tempUser = readUser();
	}

	file.clear();
	file.seekg(index);
	delete tempUser;
}