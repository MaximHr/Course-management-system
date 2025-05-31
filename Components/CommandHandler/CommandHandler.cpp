/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#include "CommandHandler.h"

CommandHandler::CommandHandler() : system(System::getInstance()) {}

namespace {
	template <typename T>
	T getValidInfo() {
		T number;
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

	template <>
	String getValidInfo<String>() {
		String str;
		do {
			std::cin >> str;
		} while(str.getSize() == 0);
		return str;
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
		} else if(command == "submit_homework") {
			submitHomework();
		} else if(command == "view_homeworks") {
			viewHomework();
		} else if(command == "grade_homework") {
			gradeHomework();
		} else if(command == "view_grades") {
			system.viewGrades();
		} else if(command == "message") {
			messageUser();
		} else if(command == "message_all") {
			messageAll();
		} else if(command == "message_students") {
			messageCourse();
		} else if(command == "mailbox") {
			system.viewMessages();
		} else if(command == "clear_mailbox") {
			system.deleteMessages();
		} else if(command == "change_password") {
			changePassword();
		}
	} catch(const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}

void CommandHandler::login() {
	unsigned id;
	String pass;

	std::cout << "Id: ";
	id = getValidInfo<unsigned>();
	std::cout << "Password: ";
	pass = getValidInfo<String>();

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
	firstName = getValidInfo<String>();
	std::cout << "last name: ";
	lastName = getValidInfo<String>();
	std::cout << "password: ";
	password = getValidInfo<String>();

	unsigned id = system.addUser(type, firstName, lastName, password);
	std::cout << "Added " << strType << ' ' << firstName << ' ' << lastName << " with ID " << id << '\n'; 
}

void CommandHandler::deleteUser() {
	std::cout << "id: ";
	unsigned id = getValidInfo<unsigned>();
	system.deleteUser(id);
}

void CommandHandler::help() {
	std::cout << "login" << '\n';
	std::cout << "add_user | Admin only" << '\n';
	std::cout << "delete_user | Admin only" << '\n';
	std::cout << "add_course | Teacher only" << '\n';
	std::cout << "enroll | Teacher or Student" << '\n';
	std::cout << "assign_homework | Teacher only" << '\n';
	std::cout << "submit_homework | Student only" << '\n';
	std::cout << "view_homeworks | Teacher only" << '\n';
	std::cout << "grade_homework | Teacher only" << '\n';
	std::cout << "view_grades | Student only" << '\n';
	std::cout << "mailbox" << '\n';
	std::cout << "clear_mailbox" << '\n';
	std::cout << "message" << '\n';
	std::cout << "message_all | Admin only" << '\n';
	std::cout << "message_students | Teacher only" << '\n';
	std::cout << "change_password | Teacher or Student" << '\n';
	std::cout << "logout" << '\n';
	std::cout << "exit" << '\n';
}

void CommandHandler::addCourse() {
	String name, password;
	std::cout << "name: ";
	name = getValidInfo<String>();
	std::cout << "password: ";
	password = getValidInfo<String>();

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
	courseId = getValidInfo<unsigned>();
	std::cout << "Course password: ";
	coursePassword = getValidInfo<String>();

	system.enrollStudent(courseId, coursePassword);
	std::cout << "You have succefully enrolled in this course!" << '\n';
};

void CommandHandler::enrollWithoutPassword() {
	unsigned courseId, studentId;

	std::cout << "Course id: ";
	courseId = getValidInfo<unsigned>();
	std::cout << "Student id: ";
	studentId = getValidInfo<unsigned>();

	system.enrollStudent(studentId, courseId);
	std::cout << "Student succefully added to course. " << '\n';
};

void CommandHandler::assignHomework() {
	unsigned courseId;
	String name;

	std::cout << "Course id: ";
	courseId = getValidInfo<unsigned>();
	std::cout << "Homework name: ";
	name = getValidInfo<String>();

	unsigned id = system.addAssignment(courseId, name);
	std::cout << "Assignment with id of " << id << " added." << '\n';
}

void CommandHandler::submitHomework() {
	unsigned assignmentId;
	String homework;

	std::cout << "Assignment id: ";
	assignmentId = getValidInfo<unsigned>();
	std::cout << "Homework: ";
	homework = getValidInfo<String>();
	unsigned id = system.addHomework(assignmentId, homework);
	std::cout << "Homework with id of " << id << " added." << '\n';
}

void CommandHandler::viewHomework() {
	unsigned assignmentId;

	std::cout << "Assignment id: ";
	assignmentId = getValidInfo<unsigned>();
	system.printSubmissions(assignmentId);
}

void CommandHandler::gradeHomework() {
	unsigned submissionId;
	double grade;

	std::cout << "Homework id: ";
	submissionId = getValidInfo<unsigned>();
	std::cout << "Grade: ";
	grade = getValidInfo<double>();

	system.gradeSubmission(submissionId, grade);
	std::cout << "Homework graded." << '\n';
}

void CommandHandler::messageUser() {
	unsigned recieverId;
	String text;

	std::cout << "Reciever id: ";
	recieverId = getValidInfo<unsigned>();
	std::cout << "Message: ";
	text = getValidInfo<String>();

	system.messageUser(recieverId, text);
	std::cout << "Message sent succefully" << '\n';
}

void CommandHandler::messageAll() {
	String text;
	std::cout << "Message: ";
	text = getValidInfo<String>();

	system.messageAll(text);
	std::cout << "Message sent succefully" << '\n';
}

void CommandHandler::messageCourse() {
	unsigned courseId;
	String text;
	std::cout << "Course id: ";
	courseId = getValidInfo<unsigned>();
	std::cout << "Message: ";
	text = getValidInfo<String>();

	system.messageCourse(courseId, text);
	std::cout << "Message sent succefully" << '\n';
}

void CommandHandler::changePassword() {
	String pass;
	std::cout << "New password: ";
	pass = getValidInfo<String>();
	system.changePassword(pass);
	std::cout << "Password changed succefully" << '\n';
}