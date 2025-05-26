#include "../Utils/Config.h"
#include "System.h"

System::System() : 
	user(nullptr), 
	verifier(user),
	userFileHandler(Config::fileNames(0)),
	courseFileHandler(Config::fileNames(3)),
	assignmentFileHandler(Config::fileNames(4)),
	submissionFileHandler(Config::fileNames(2)),
	idContainer(Config::fileNames(1), Config::fileNames(), Config::numberOfFiles) 
{ }

System& System::getInstance() {
	static System instance;
	return instance;
}

unsigned System::addUser(UserType type, const String& firstName, const String& lastName, const String& password) {
	verifier.requireAdmin();

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
	verifier.requireLoggedOut();
	user = userFileHandler.getUserByPassword(id, password.reverse());
}

void System::deleteUser(unsigned id) {
	verifier.requireAdmin();
	
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
	verifier.requireTeacher();

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
	verifier.requireStudent();
	Course* course = courseFileHandler.getCourse(courseId, coursePassword.reverse());

	if(courseFileHandler.findStudentId(courseId, user->getId(), course->getStudentsCount())) {
		delete course;
		throw std::runtime_error("You have already enrolled in this course.");
	}

	courseFileHandler.addStudentId(*course, user->getId());
	delete course;
}

void System::enrollStudent(unsigned studentId, unsigned courseId) {
	verifier.requireTeacher();
	
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

unsigned System::addAssignment(unsigned courseId, const String& name) {
	verifier.requireTeacher();

	Course* course = courseFileHandler.getCourse(courseId);
	if(course->getOwnerId() != user->getId()) {
		delete course;
		throw std::runtime_error("Access denied.");
	}
	unsigned id = idContainer.getId(Config::fileNames(4));
	if(assignmentFileHandler.findAssignment(id) != -1) {
		delete course;
		throw std::runtime_error("Assignment with that id already exists");
	}

	Assignment assignment(name, id, courseId);
	assignmentFileHandler.saveAssignment(assignment);
	idContainer.increment(Config::fileNames(4));
	delete course;

	return assignment.getId();
}

unsigned System::addHomework(unsigned assignmentId, const String& homework) {
	verifier.requireStudent();

	unsigned id = idContainer.getId(Config::fileNames(2));
	if(submissionFileHandler.findSubmission(id) != -1) {
		throw std::runtime_error("Submission with that id already exists");
	}

	Assignment* assignment = assignmentFileHandler.getAssignment(assignmentId);
	Course* course = courseFileHandler.getCourse(assignment->getCourseId());
	if(!courseFileHandler.findStudentId(course->getId(), user->getId(), course->getStudentsCount())) {
		delete assignment;
		delete course;
		throw std::runtime_error("Access denied.");
	}

	Submission submission(id, user->getId(), assignmentId, homework);

	submissionFileHandler.saveSubmission(submission, submissionFileHandler);
	submissionFileHandler.file.flush();
	idContainer.increment(Config::fileNames(2));
	delete assignment;
	delete course;

	return id;
}

void System::printSubmissions(unsigned assignmentId) {
	verifier.requireTeacher();

	Assignment* assignment = assignmentFileHandler.getAssignment(assignmentId);
	Course* course = courseFileHandler.getCourse(assignment->getCourseId());
	if(user->getId() != course->getOwnerId()) {
		delete assignment;
		delete course;
		throw std::runtime_error("Access denied");
	}
	std::cout << "Assignment " << assignment->getName() << " for course " << course->getName() << " : \n";
	submissionFileHandler.printSubmissions(assignmentId);

	delete assignment;
	delete course;
}

void System::gradeSubmission(unsigned submissionId, double newGrade) {
	verifier.requireTeacher();

	Submission* submission = nullptr;
  Assignment* assignment = nullptr;
  Course* course = nullptr;

	try {
		submission = submissionFileHandler.getSubmission(submissionId);
		assignment = assignmentFileHandler.getAssignment(submission->getAssignmentId());
		course = courseFileHandler.getCourse(assignment->getCourseId());

		if(course->getOwnerId() != user->getId()) {
			throw std::runtime_error("Access denied");
		}

		submission->setGrade(newGrade);
		submissionFileHandler.updateSubmission(*submission);
		delete submission;
		delete assignment;
		delete course;

	} catch(const std::exception& e) {
		delete submission;
		delete assignment;
		delete course;
		throw std::runtime_error(e.what());
	}
}

void System::viewGrades() {
	verifier.requireStudent();
	
}

void System::logout() {
	delete user;
	user = nullptr;
}

System::~System() {
	delete user;
	user = nullptr;
}