#pragma once
#include "../../Users/Student/Student.h"
#include "../Assignment/Assignment.h"
#include "../../Utils/String.h"
#include "../../FileHandlers/SubmissionFileHandler.h"

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