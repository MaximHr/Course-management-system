#pragma once
#include "FileHandler.h"
class Submission;

class SubmissionFileHandler: public FileHandler {
	void printGrade(const Submission* submission);
	void printHomework(const Submission* submission);
public:
	SubmissionFileHandler() = default;
	SubmissionFileHandler(const String& str);

	Submission* readSubmission();
	Submission* readSubmission(int& bytes);
	Submission* getSubmission(unsigned id);
	void saveSubmission(const Submission& submission, FileHandler& fs);
	int findSubmission(unsigned id);
	void viewSubmissions(unsigned searchedId, bool isViewingAsParticipant);
	void updateSubmission(Submission& submission);
};