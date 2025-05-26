#pragma once
#include "../Utils/Config.h"
#include "../Utils/String.h"
#include "../Users/User.h"
#include "../Users/UserFactory.h"
#include "../IdManager/IdContainer.h"
#include "../FileHandlers/UserFileHandler.h"
#include "../FileHandlers/CourseFileHandler.h"
#include "../FileHandlers/AssignmentFileHandler.h"
#include "../FileHandlers/SubmissionFileHandler.h"
#include "../FileHandlers/MessageFileHandler.h"
#include "SystemVerifier.h"
#include "../Components/Course/Course.h"
#include "../Components/Submission/Submission.h"
#include "../Components/Message/Message.h"
#include <exception>

class System {
	IdContainer idContainer;
	UserFileHandler userFileHandler;
	CourseFileHandler courseFileHandler;
	AssignmentFileHandler assignmentFileHandler;
	SubmissionFileHandler submissionFileHandler;
	MessageFileHandler messageFileHandler;
	User* user;
	SystemVerifier verifier;
	
	System();
	System(const System& other) = delete;
	System& operator=(const System& other) = delete;

public:
	static System& getInstance();
	~System();
	unsigned addUser(UserType type, const String& firstName, const String& lastName, const String& password);
	void deleteUser(unsigned id);
	void login(unsigned id, const String& password);
	void logout();
	unsigned addCourse(const String& name, const String& password);
	bool getEnrollType() const;
	void enrollStudent(unsigned studentId, unsigned courseId);
	void enrollStudent(unsigned courseId, const String& coursePassword);
	unsigned addAssignment(unsigned courseId, const String& name);
	unsigned addHomework(unsigned assignmentId, const String& homework);
	void printSubmissions(unsigned assignmentId);
	void gradeSubmission(unsigned submissionId, double newGrade);
	void viewGrades();
	void messageAll(const String& text);
	void messageCourse(unsigned courseId, const String& text);
	void messageUser(unsigned recieverId, const String& text);
	void viewMessages();
	void deleteMessages();
};