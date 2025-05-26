#pragma once
#include "FileHandler.h"
class Submission;

class SubmissionFileHandler: public FileHandler {

public:
	SubmissionFileHandler() = default;
	~SubmissionFileHandler() = default;
	SubmissionFileHandler(const String& str);

	Submission* readSubmission();
	Submission* readSubmission(int& bytes);
	Submission* getSubmission(unsigned id);
	void saveSubmission(const Submission& submission, FileHandler& fs);
	int findSubmission(unsigned id);
	void printSubmissions(unsigned assignmentId);
	void updateSubmission(Submission& submission);
};