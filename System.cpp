#include "System.h"
String usersFileName = "users.dat";
String messagesFileName = "messages.dat";
String coursesFileName = "courses.dat";
String tempFileName = "temp.dat";

unsigned System::userIdCounter = 100;
UserFileHandler System::userFileHandler(usersFileName, userIdCounter);
MessageFileHandler System::messageFileHandler(messagesFileName);

System::System() { }

unsigned System::addUser(UserType type, const String& firstName, const String& lastName, const String& password) {
	if(user == nullptr || user->getRole() != UserType::Admin) {
		throw std::runtime_error("Access denied.");
	}
	User* newUser = UserFactory::createUser(type, firstName, lastName, password, userIdCounter);
	userIdCounter++;
	if(userFileHandler.findUser(newUser->getId(), newUser->getHashedPassword(), true) != -1) {
		delete newUser;
		throw std::runtime_error("User with that id already exists");
	}
	userFileHandler.saveUser(newUser);
	unsigned id = newUser->getId();
	delete newUser;

	return id;
}

void System::login(unsigned id, const String& password) {
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

void System::deleteUser(unsigned id) {
	if(user == nullptr || user->getRole() != UserType::Admin) {
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

void System::logout() {
	delete user;
	user = nullptr;
}

void System::copyDynamic(const System& other) {
	user = other.user->clone();
}
void System::freeDynamic() {
	delete user;
	user = nullptr;
}

System::~System() {
	freeDynamic();
}

System::System(const System& other){
	copyDynamic(other);
}

System& System::operator=(const System& other) {
	if(this != &other) {
		freeDynamic();
		copyDynamic(other);
	}
	return *this;
}