#pragma once
#include "System.h"
#include "String.h"

class CommandHandler {
	static System system;
	void addUser();
	void deleteUser();
	void help();
	void login();
	void callCommand(const String& str);
public:
	void start();
	CommandHandler() = default;
};