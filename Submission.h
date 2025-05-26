#pragma once
#include "Student.h"
#include "Assignment.h"
#include "String.h"
#include "SubmissionFileHandler.h"

class Submission {
	unsigned id;
	unsigned studentId;
	unsigned assignmentId;
	String answer;
	double grade;
	friend Submission* SubmissionFileHandler::readSubmission();

public:
	Submission();
	Submission(unsigned id, unsigned studentId, unsigned assignmentId, const String& answer);
	double getGrade() const;
	double getStudentId() const;
	double getId() const;
	bool isGraded() const;
	double getAssignmentId() const;
	const String& getAnswer() const;
	void setGrade(double grade);
};