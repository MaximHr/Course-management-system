#pragma once
#include "Config.h"
#include "String.h"
#include "User.h"
#include "UserFactory.h"
#include <exception>
#include "IdContainer.h"
#include "UserFileHandler.h"
#include "CourseFileHandler.h"
#include "AssignmentFileHandler.h"
#include "SubmissionFileHandler.h"
#include "SystemVerifier.h"
#include "Course.h"
#include "Submission.h"

class System {
	static IdContainer idContainer;
	static UserFileHandler userFileHandler;
	static CourseFileHandler courseFileHandler;
	static AssignmentFileHandler assignmentFileHandler;
	static SubmissionFileHandler submissionFileHandler;
	User* user;
	void copyDynamic(const System& other);
	void freeDynamic();

public:
	System();
	~System();
	System(const System& other);
	System& operator=(const System& other);
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
};