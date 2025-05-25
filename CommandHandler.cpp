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
	String command = str.trim();
	try {
		if(command == "help") {
			help();
		} else if(command == "add_user") {
			addUser();
		} else if(command == "delete_user") {
			deleteUser();
		} else if(command == "login") {
			login();
		} else if(command == "logout") {
			system.logout();
		} else if(command == "add_course") {
			addCourse();
		} else if(command == "enroll") {
			enroll();
		} else if(command == "assign_homework") {
			assignHomework();
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
	std::cout << "add_course | Teacher only" << '\n';
	std::cout << "enroll | Teacher or Student" << '\n';
	std::cout << "assign_homework | Teacher only" << '\n';
	std::cout << "exit" << '\n';
}

void CommandHandler::addCourse() {
	String name, password;
	std::cout << "name: ";
	std::cin >> name;
	std::cout << "password: ";
	std::cin >> password;
	unsigned id = system.addCourse(name, password);
	std::cout << "Course " << name << " with id of " << id << " added successfully" << '\n';
}

void CommandHandler::enroll() {
	bool shouldEnrollWithPassword = system.getEnrollType();
	if(shouldEnrollWithPassword) {
		enrollWithPassword();
	} else {
		enrollWithoutPassword();
	}
}

void CommandHandler::enrollWithPassword() {
	unsigned courseId;
	String coursePassword;

	std::cout << "Course id: ";
	courseId = getValidatedInt();
	std::cout << "Course password: ";
	std::cin >> coursePassword;

	system.enrollStudent(courseId, coursePassword);
	std::cout << "You have succefully enrolled this!" << '\n';
};

void CommandHandler::enrollWithoutPassword() {
	unsigned courseId, studentId;

	std::cout << "Course id: ";
	courseId = getValidatedInt();
	std::cout << "Student id: ";
	studentId = getValidatedInt();

	system.enrollStudent(studentId, courseId);
	std::cout << "Student succefully added to course. " << '\n';
	
};

void CommandHandler::assignHomework() {
	unsigned courseId;
	String name;

	std::cout << "Course id: ";
	courseId = getValidatedInt();
	std::cout << "Homework name: ";
	std::cin >> name;

	unsigned id = system.addAssignment(courseId, name);
	std::cout << "Homework with id of " << id << " added." << '\n';
}