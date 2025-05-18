#include "Teacher.h"

UserType Teacher::getRole() const {
	return UserType::Teacher;
}

Teacher::Teacher(const String& firstName, const String& lastName, const String& password):User(firstName, lastName, password) {

}

User* Teacher::clone() const {
	return new Teacher(*this);
}