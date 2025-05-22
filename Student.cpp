#include "Student.h"

UserType Student::getRole() const {
	return UserType::Student;
}

Student::Student(const String& firstName, const String& lastName, const String& password, unsigned idCounter):User(firstName, lastName, password, idCounter) {

}

User* Student::clone() const {
	return new Student(*this);
}