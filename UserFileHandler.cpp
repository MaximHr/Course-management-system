#include "UserFileHandler.h"
#include "User.h"
#include "System.h"
#include "UserFactory.h"

UserFileHandler::UserFileHandler(const String& str, unsigned& userIdCounter):FileHandler(str) { 
	try {
		if(findUser(0, "0000", false) == -1) {
			User* admin = new Admin();
			saveUser(admin);
			delete admin;
		} else {
			// userIdCounter = getLastId();
			std::cout << userIdCounter << '\n';
		}
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void UserFileHandler::saveUser(const User* user) {
	if(!isOpen()) throw std::runtime_error("file can not be opened u9");
	UserType type = user->getRole();
	std::cout << "SAVE USER" << '\n';
	write((const char*)& type, sizeof(UserType));
	write(user->getFirstName());
	write(user->getLastName());
	write(user->getHashedPassword());
	unsigned id = user->getId();
	std::cout << "Write:" << user->getId() << ' ' << user->getHashedPassword() <<  '\n';
	write((const char*)& id, sizeof(unsigned));
}

User* UserFileHandler::readUser() {
	UserType role;
	read((char*)& role, sizeof(UserType));
	std::cout << "ROLE" << (int)role << '\n';
	User* newUser = UserFactory::createUser(role);
	read(newUser->firstName);
	std::cout << newUser->firstName << '\n';
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
	if(!isOpen()) throw std::runtime_error("file can not be opened u42");
	if(getFileSize() == 0) return -1;
	int index = file.tellg();
	file.seekg(0);
	User* tempUser = nullptr;
	int result = 0;
	do {
		if(file.eof()) {
			file.clear();
			if (tempUser != nullptr) {
				delete tempUser;
			}
			return -1;
		}
		result = file.tellg();
		tempUser = readUser();
		delete tempUser;
	} while (
    (searchForIdOnly && tempUser->getId() != id) ||
    (!searchForIdOnly && (tempUser->getId() != id || tempUser->getHashedPassword() != hashedPassword))
	);

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
	if(!isOpen()) throw std::runtime_error("file can not be opened u108");

	int largestId = 100;
	if(getFileSize() == 0) return largestId;
	int index = file.tellg();
	file.seekg(0);

	User* tempUser;
	do {
		std::cout << "do()" << '\n';
		tempUser = readUser();
		std::cout << tempUser->getFirstName() << ' ' << tempUser->getId() << '\n';
		if(tempUser->getId() >= largestId) {
			largestId = tempUser->getId() + 1;
		}
		delete tempUser;
	} while(file);

	file.clear();
	file.seekg(index);
	
	return largestId;
}
