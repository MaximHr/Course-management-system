#pragma once
#include "Config.h"
#include "FileHandler.h"
#include "String.h"
#include <exception>
#include <iostream>
class User;

class UserFileHandler: public FileHandler {
public:
	UserFileHandler() = default;
	~UserFileHandler() = default;
	UserFileHandler(const String& str);
	void saveUser(const User* user);
	User* readUser();
	User* readUser(int& sizeInBytes);
	int findUser(unsigned id);
	User* getUser(unsigned id);
	User* getUserByPassword(unsigned id, const String& hashedPassword);;
	int findUserWithPassword(unsigned id, const String& hashedPassword);
	void deleteUser(unsigned id);
};