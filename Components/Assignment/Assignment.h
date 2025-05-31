/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#pragma once
#include "../../Utils/String.h"
#include "../../FileHandlers/AssignmentFileHandler.h"

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