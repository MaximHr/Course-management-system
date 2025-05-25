#include "Config.h"
#include "System.h"

UserFileHandler System::userFileHandler(Config::fileNames(0));
CourseFileHandler System::courseFileHandler(Config::fileNames(3));

IdContainer System::idContainer(Config::fileNames(1), Config::fileNames(), Config::numberOfFiles);

System::System() {};

unsigned System::addUser(UserType type, const String& firstName, const String& lastName, const String& password) {
	if(user == nullptr || user->getRole() != UserType::Admin) {
		throw std::runtime_error("Access denied.");
	}

	unsigned id = idContainer.getId(Config::fileNames(0));
	if(userFileHandler.findUserWithPassword(id, password.reverse()) != -1) {
		throw std::runtime_error("User with that id already exists");
	}

	User* newUser = UserFactory::createUser(type, firstName, lastName, password, id);
	userFileHandler.saveUser(newUser);
	idContainer.increment(Config::fileNames(0));
	delete newUser;

	return id;
}

void System::login(unsigned id, const String& password) {
	if(user != nullptr) {
		throw std::runtime_error("You must logout first, in order to log in.");
	}
	
	user = userFileHandler.getUserByPassword(id, password.reverse());
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
		std::cout << "No user with that id found. " << '\n';
	}
}

unsigned System::addCourse(const String& name, const String& password) {
	if(user == nullptr || user->getRole() != UserType::Teacher) {
		throw std::runtime_error("Access denied.");
	}

	unsigned id = idContainer.getId(Config::fileNames(3));
	const Course course(name, password, user->getId(), id);

	if(courseFileHandler.findCourse(id) != -1) {
		throw std::runtime_error("Course with that id already exists.");	
	}

	courseFileHandler.saveCourse(course, courseFileHandler);
	courseFileHandler.file.flush();
	idContainer.increment(Config::fileNames(3));

	return id;
}

bool System::getEnrollType() const {
	if(user->getRole() == UserType::Teacher) {
		return 0; // enroll without course password
	}
	return 1; //enroll with course password
}

void System::enrollStudent(unsigned courseId, const String& coursePassword) {
	if(user == nullptr || user->getRole() != UserType::Student) {
		throw std::runtime_error("Access denied.");
	}

	Course* course = courseFileHandler.getCourse(courseId, coursePassword.reverse());

	if(courseFileHandler.findStudentId(courseId, user->getId(), course->getStudentsCount())) {
		delete course;
		throw std::runtime_error("You have already enrolled in this course.");
	}

	courseFileHandler.addStudentId(*course, user->getId());
	delete course;
}

void System::enrollStudent(unsigned studentId, unsigned courseId) {
	if(user == nullptr || user->getRole() != UserType::Teacher) {
		throw std::runtime_error("Access denied.");
	}
	
	Course* course = courseFileHandler.getCourse(courseId);
	User* newUser = userFileHandler.getUser(studentId);

	if(newUser->getRole() != UserType::Student) {
		delete course;
		delete newUser;
		throw std::runtime_error("Only students can be enrolled.");
	}
	if(user->getId() != course->getOwnerId()) {
		delete course;
		delete newUser;
		throw std::runtime_error("Access denied.");
	}

	if(courseFileHandler.findStudentId(courseId, studentId, course->getStudentsCount())) {
		delete course;
		delete newUser;
		throw std::runtime_error("Student has already enrolled");
	}

	courseFileHandler.addStudentId(*course, studentId);
	delete newUser;
	delete course;
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