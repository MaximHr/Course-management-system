#include "CommandHandler.h"

System CommandHandler::system;

int getValidatedInt() {
	int number;
	while(true) {
		std::cin >> number;
		if(std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
		} else {
			std::cin.ignore();
			return number;
		}
	}
}

void CommandHandler::start() {
	std::cout << "Welcome to CourseHub" << '\n';
	std::cout << "Type help to view all commands" << '\n';
	String str;
	do {
		std::cin >> str;
		callCommand(str);
	} while(str != "exit");
}

void CommandHandler::callCommand(const String& str) {
	String trimmed = str.trim();
	try {
		if(trimmed == "help") {
			help();
		} else if(trimmed == "add_user") {
			addUser();
		} else if(trimmed == "delete_user") {
			deleteUser();
		} else if(trimmed == "login") {
			login();
		} else if(trimmed == "logout") {
			system.logout();
		}
	} catch(const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}

void CommandHandler::login() {
	unsigned id;
	String pass;
	std::cout << "Id: ";
	id = getValidatedInt();
	std::cout << "Password: ";
	std::cin >> pass;
	system.login(id, pass);
	std::cout << "Login succefull!" << std::endl;

}

void CommandHandler::addUser() {
	String firstName, lastName, password, strType;
	UserType type;
	bool isValidType = false;
	do {
		std:: cout << "Choose role for the user (student or teacher): ";
		std::cin >> strType;
		if(strType == "student") {
			type = UserType::Student;
			isValidType = true;
		} else if(strType == "teacher") {
			type = UserType::Teacher;
			isValidType = true;
		}
	} while(!isValidType);
	std::cout << "first name: ";
	std::cin >> firstName;
	std::cout << "last name: ";
	std::cin >> lastName;
	std::cout << "password: ";
	std::cin >> password;
	unsigned id = system.addUser(type, firstName, lastName, password);
	std::cout << "Added " << strType << ' ' << firstName << ' ' << lastName << " with ID " << id << '\n'; 
}

void CommandHandler::deleteUser() {
	std::cout << "id: ";
	unsigned id = getValidatedInt();
	system.deleteUser(id);
}

void CommandHandler::help() {
	std::cout << "login" << '\n';
	std::cout << "logout" << '\n';
	std::cout << "add_user | Admin only" << '\n';
	std::cout << "delete_user | Admin only" << '\n';
	std::cout << "exit" << '\n';
}

