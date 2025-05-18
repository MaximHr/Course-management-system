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

class CommandHandler {
	static UserFileHandler userFileHandler;
	static MessageFileHandler messageFileHandler;
	User* user;
	void copyDynamic(const CommandHandler& other);
	void freeDynamic();
public:
	CommandHandler();
	~CommandHandler();
	CommandHandler(const CommandHandler& other);
	CommandHandler& operator=(const CommandHandler& other);
	unsigned addUser(UserType type, const String& firstName, const String& lastName, const String& password);
	void deleteUser(unsigned id);
	void login(unsigned id, const String& password);
	void logout();
};