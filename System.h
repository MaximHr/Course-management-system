#pragma once
#include "String.h"
#include "UserFileHandler.h"
#include "MessageFileHandler.h"
#include "User.h"
#include "UserFactory.h"
#include <exception>

extern String usersFileName;
extern String messagesFileName;
extern String coursesFileName;
extern String tempFileName;

class System {
	static UserFileHandler userFileHandler;
	static MessageFileHandler messageFileHandler;
	static unsigned userIdCounter;
	User* user;
	void copyDynamic(const System& other);
	void freeDynamic();
public:
	System();
	~System();
	System(const System& other);
	System& operator=(const System& other);
	unsigned addUser(UserType type, const String& firstName, const String& lastName, const String& password);
	void deleteUser(unsigned id);
	void login(unsigned id, const String& password);
	void logout();
};