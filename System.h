#pragma once
#include "Config.h"
#include "String.h"
#include "User.h"
#include "UserFactory.h"
#include <exception>
#include "IdContainer.h"
#include "UserFileHandler.h"

class System {
	static IdContainer idContainer;
	static UserFileHandler userFileHandler;
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