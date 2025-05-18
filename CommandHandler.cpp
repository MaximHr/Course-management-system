#include "CommandHandler.h"
String usersFileName = "users.dat";
String messagesFileName = "messages.dat";
String coursesFileName = "courses.dat";
String tempFileName = "temp.dat";
UserFileHandler CommandHandler::userFileHandler(usersFileName);
MessageFileHandler CommandHandler::messageFileHandler(messagesFileName);

CommandHandler::CommandHandler() {
	try {
		if(userFileHandler.findUser(0, "0000", false) == -1) {
			User* admin = new Admin();
			userFileHandler.saveUser(admin);
			delete admin;
		}
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

unsigned CommandHandler::addUser(UserType type, const String& firstName, const String& lastName, const String& password) {
	if(user->getRole() != UserType::Admin) {
		throw std::runtime_error("Access denied.");
	}
	User* newUser = UserFactory::createUser(type, firstName, lastName, password);
	if(userFileHandler.findUser(newUser->getId(), newUser->getHashedPassword(), true) != -1) {
		throw std::runtime_error("User with that id already exists");
	}
	userFileHandler.saveUser(newUser);
	unsigned id = newUser->getId();
	delete newUser;

	return id;
}

void CommandHandler::login(unsigned id, const String& password) {
	if(user != nullptr) {
		throw std::runtime_error("You must logout first, in order to log in.");
	}
	String hashedPass = password.reverse();
	int pos = userFileHandler.findUser(id, hashedPass, false);
	if(pos == -1) {
		throw std::runtime_error("Invalid credentials");
	}
	int current = userFileHandler.file.tellg();
	userFileHandler.file.seekg(pos);
	user = userFileHandler.readUser();
	userFileHandler.file.seekg(current);
}

void CommandHandler::deleteUser(unsigned id) {
	if(user->getRole() != UserType::Admin) {
		throw std::runtime_error("Access denied.");
	}
	if(user->getId() == id) {
		throw std::runtime_error("Admin can not be deleted.");
	}
	int fileSize = userFileHandler.getFileSize();
	userFileHandler.deleteUser(id);
	if(fileSize != userFileHandler.getFileSize()) {
		std::cout << "User deleted succefully!" << '\n';
	} else {
		std::cout << "No user found with that id. " << '\n';
	}
}

void CommandHandler::logout() {
	delete user;
	user = nullptr;
}

void CommandHandler::copyDynamic(const CommandHandler& other) {
	user = other.user->clone();
}
void CommandHandler::freeDynamic() {
	delete user;
	user = nullptr;
}

CommandHandler::~CommandHandler() {
	freeDynamic();
}

CommandHandler::CommandHandler(const CommandHandler& other){
	copyDynamic(other);
}

CommandHandler& CommandHandler::operator=(const CommandHandler& other) {
	if(this != &other) {
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}