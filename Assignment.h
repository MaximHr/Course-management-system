#pragma once
#include "String.h"
#include "AssignmentFileHandler.h"

class Assignment {
	String name;
	unsigned id;
	unsigned courseId;
	friend Assignment* AssignmentFileHandler::readAssignment();
public:
	Assignment() = default;
	Assignment(const String& name, unsigned id, unsigned courseId);
	const String& getName() const;
	unsigned getCourseId() const;
	unsigned getId() const;
};