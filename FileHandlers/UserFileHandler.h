#pragma once
#include "../Utils/Config.h"
#include "FileHandler.h"
#include "../Utils/String.h"
#include <exception>
#include <iostream>
class User;

class UserFileHandler: public FileHandler {
private:
	User* getUserMatcher(unsigned id, const String& hashedPassword, bool shouldCheckForPassword);
	int findUserMatcher(unsigned id, const String& hashedPassword, bool shouldCheckPassword);
public:
	UserFileHandler() = default;
	~UserFileHandler() = default;
	UserFileHandler(const String& str);
	
	void saveUser(const User* user);
	User* readUser();
	User* readUser(int& sizeInBytes);
	User* getUser(unsigned id);
	User* getUserByPassword(unsigned id, const String& hashedPassword);
	int findUser(unsigned id);
	int findUserWithPassword(unsigned id, const String& hashedPassword);
	void deleteUser(unsigned id);
};