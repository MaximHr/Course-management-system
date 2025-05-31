/*
	Name: Maksim Hristov
	FN: 4MI0600466
*/

#include "Teacher.h"

UserType Teacher::getRole() const {
	return UserType::Teacher;
}

Teacher::Teacher(const String& firstName, const String& lastName, const String& password, unsigned idCounter) : 
	User(firstName, lastName, password, idCounter) { }

User* Teacher::clone() const {
	return new Teacher(*this);
}