/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#include "SubmissionFileHandler.h"
#include "../Components/Submission/Submission.h"

SubmissionFileHandler::SubmissionFileHandler(const String& str) : FileHandler(str) {}

Submission* SubmissionFileHandler::readSubmission() {
	if(!isOpen()) throw std::runtime_error("file can not be opened");
	Submission* submission = new Submission();

	file.read((char *)& submission->id, sizeof(submission->id));
	file.read((char *)& submission->studentId, sizeof(submission->studentId));
	file.read((char *)& submission->assignmentId, sizeof(submission->assignmentId));
	read(submission->answer);
	file.read((char *)& submission->grade, sizeof(submission->grade));

	return submission;
}

Submission* SubmissionFileHandler::readSubmission(int& sizeInBytes) {
	int start = file.tellg();
	Submission* submission = readSubmission();
	sizeInBytes = (int)file.tellg() - start;

	return submission;
}

Submission* SubmissionFileHandler::getSubmission(unsigned id) {
	int pos = findSubmission(id);
	if(pos == -1)  {
		throw std::runtime_error("Submission with that id was not found");
	}

	int current = file.tellg();
	file.seekg(pos);
	Submission* submission = readSubmission();
	file.seekg(current);

	return submission;
}

void SubmissionFileHandler::saveSubmission(const Submission& submission, FileHandler& fs) {
	if(!fs.isOpen()) throw std::runtime_error("file can not be opened");

	unsigned id = submission.getId();
	unsigned studentId = submission.getStudentId();
	unsigned assignmentId = submission.getAssignmentId();
	double grade = submission.getGrade();

	fs.file.write((const char *)& id, sizeof(id));
	fs.file.write((const char *)& studentId, sizeof(studentId));
	fs.file.write((const char *)& assignmentId, sizeof(assignmentId));
	fs.write(submission.getAnswer());
	fs.file.write((const char *)& grade, sizeof(grade));
}

int SubmissionFileHandler::findSubmission(unsigned id) {
	if(!isOpen()) throw std::runtime_error("file cannot be opened");
	if(getFileSize() == 0) return -1;

	int index = setAtBeginning();
	Submission* submission = readSubmission();
	int result = 0;

	while(submission->getId() != id) {
		if(!file) {
			file.clear();
			delete submission;
			return -1;
		}
		result = file.tellg();
		delete submission;
		submission = readSubmission();
	}

	file.clear();
	file.seekg(index);
	delete submission;

	return result;
}

void SubmissionFileHandler::printHomework(const Submission* submission) {
	std::cout << "| Id: " << submission->getId() << " | Answer: " << submission->getAnswer() << " | Grade: ";
	if(!submission->isGraded()) {
		std::cout << "not graded" << '\n';
	} else {
		std::cout << submission->getGrade() << '\n';
	}
}

void SubmissionFileHandler::viewSubmissions(unsigned searchedId, bool isViewingAsParticipant) {
	if(!isOpen()) throw std::runtime_error("file cannot be opened");
	if(getFileSize() == 0) {
		std::cout << "There are no submited homeworks yet." << '\n';
		return;
	};

	int index = setAtBeginning();
	Submission* submission = readSubmission();
	bool containsSubmissions = false;
	
	while(!file.eof()) {
		if(!isViewingAsParticipant && (submission->getAssignmentId() == searchedId) ||
			 isViewingAsParticipant && (submission->getStudentId() == searchedId) ) {
			containsSubmissions = true;
			printHomework(submission);
		}
		delete submission;
		submission = readSubmission();
	}
	if(!containsSubmissions) {
		std::cout << "There are no submited homeworks yet." << '\n';
	}

	file.clear();
	file.seekg(index);
	delete submission;
}

void SubmissionFileHandler::updateSubmission(Submission& submission) {
	FileHandler output(Config::fileNames(6).c_str());
	if(!output.isOpen()) throw std::runtime_error("Failed to open temporary file for writing");

	int index = setAtBeginning();
	int bytes = 0;
	Submission* tempSubmission = readSubmission(bytes);

	while(file) {
		if(tempSubmission->getId() != submission.getId()) {
			copyBytes(output.file, bytes);
		} else {
			saveSubmission(submission, output);
		}
		delete tempSubmission;
		tempSubmission = readSubmission(bytes);
	}

	output.close();
	changeFile(Config::fileNames(6).c_str(), Config::fileNames(2).c_str());
	if(index < getFileSize()) {
		file.seekg(index);
	}
	delete tempSubmission;
}