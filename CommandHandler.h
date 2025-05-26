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
	void addCourse();
	void enroll();
	void enrollWithPassword();
	void enrollWithoutPassword();
	void assignHomework();
	void submitHomework();
	void viewHomework();
	void gradeHomework();

public:
	void start();
	CommandHandler() = default;
};