/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#pragma once
#include "FileHandler.h"
class Assignment;

class AssignmentFileHandler: public FileHandler {
public:
	AssignmentFileHandler() = default;
	AssignmentFileHandler(const String& str);

	Assignment* readAssignment();
	Assignment* getAssignment(unsigned id);
	void saveAssignment(const Assignment& assignment);
	int findAssignment(unsigned id);
};