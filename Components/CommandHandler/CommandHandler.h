#pragma once
#include "../../System/System.h"
#include "../../Utils/String.h"

class CommandHandler {
	System& system;
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
	void messageUser();
	void messageAll();
	void messageCourse();

public:
	void start();
	CommandHandler();
};