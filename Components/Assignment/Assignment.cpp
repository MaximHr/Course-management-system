/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#include "Assignment.h"

Assignment::Assignment(const String& name, unsigned id, unsigned courseId) 
	: name(name), id(id), courseId(courseId) {}

const String& Assignment::getName() const {
	return name;
}

unsigned Assignment::getCourseId() const {
	return courseId;
}

unsigned Assignment::getId() const {
	return id;
}