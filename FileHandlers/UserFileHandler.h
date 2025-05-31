/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#pragma once
#include "../Utils/Config.h"
#include "FileHandler.h"
#include "../Utils/String.h"
#include <exception>
#include <iostream>
class User;

enum class Group {
	All,
	Course
};

class UserFileHandler: public FileHandler {
private:
	User* getUserMatcher(unsigned id, const String& hashedPassword, bool shouldCheckForPassword);
	int findUserMatcher(unsigned id, const String& hashedPassword, bool shouldCheckPassword);
	void updateUserMatcher(unsigned id, const User* updatedUser);
	void messageGroup(const String& text, Group groupType, unsigned id);
public:
	UserFileHandler() = default;
	~UserFileHandler() = default;
	UserFileHandler(const String& str);
	
	void saveUser(const User* user, FileHandler& fs);
	User* readUser();
	User* readUser(int& sizeInBytes);
	User* getUser(unsigned id);
	User* getUserByPassword(unsigned id, const String& hashedPassword);
	int findUser(unsigned id);
	int findUserWithPassword(unsigned id, const String& hashedPassword);
	void deleteUser(unsigned id);
	void updateUser(unsigned id, const User* updatedUser);
	void messageCourse(const String& text, unsigned courseId);
	void messageAll(const String& text);
};