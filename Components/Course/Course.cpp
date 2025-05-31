/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#include "Course.h"

Course::Course(const String& name, const String& password, unsigned ownerId, unsigned id) :
	name(name), 
	hashedPassword(password.reverse()), 
	ownerId(ownerId), 
	id(id),
	studentsCount(0) { }

void Course::incrementStudentsCount() {
	studentsCount++;
}

unsigned  Course::getStudentsCount() const {
	return studentsCount;
}

unsigned Course::getId() const {
	return id;
}

const String& Course::getName() const {
	return name;
}

const String& Course::getHashedPassword() const {
	return hashedPassword;
}

unsigned Course::getOwnerId() const {
	return ownerId;
}