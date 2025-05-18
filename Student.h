#pragma once
#include "User.h"

class Student: public User {
public:
	Student() = default;
	Student(const String& firstName, const String& lastName, const String& password);
	UserType getRole() const override;
	User* clone() const override;
};