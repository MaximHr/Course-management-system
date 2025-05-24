#include "UserFileHandler.h"
#include "User.h"
#include "UserFactory.h"
#include "Config.h"

UserFileHandler::UserFileHandler(const String& str):FileHandler(str, false) {
	if(findUser(Config::adminId, Config::adminPassword().reverse(), false) == -1) {
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
	std::cout << newUser->firstName << ' ' << newUser->hashedPassword << ' ' << newUser->id << '\n';
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
	file.clear();
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

void UserFileHandler::deleteUser(unsigned id) {
	std::ofstream ofs(Config::fileNames(6).c_str(), std::ios::binary);
	if(!ofs.is_open()) throw std::runtime_error("Failed to open temporary file for writing");

	int index = file.tellg();
	file.seekg(0);

	int bytes = 0;
	User* tempUser = readUser(bytes);
	while(file) {
		if(tempUser->getId() != id) {
			copyBytes(ofs, bytes);
		};
		delete tempUser;
		tempUser = readUser(bytes);
	}

	ofs.close();
	changeFile(Config::fileNames(6).c_str(), Config::fileNames(0).c_str());
	if(index < getFileSize()) {
		file.seekg(index);
	}
	delete tempUser;

}