#pragma once
#include "CommandHandler.h"

class System {
	static CommandHandler commandHandler;
	void addUser();
	void deleteUser();
	void help();
	void login();
	void callCommand(const String& str);
public:
	void start();
	System() = default;
};