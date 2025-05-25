#pragma once
#include "FileHandler.h"
class Assignment;

class AssignmentFileHandler: public FileHandler {
public:
	Assignment* readAssignment();
	AssignmentFileHandler() = default;
	~AssignmentFileHandler() = default;
	AssignmentFileHandler(const String& str);
	void saveAssignment(const Assignment& assignment);
	int findAssignment(unsigned id);
};