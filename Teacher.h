#pragma once
#include "User.h"

class Teacher:public User {
public:
	Teacher() = default;
	Teacher(const String& firstName, const String& lastName, const String& password);
	UserType getRole() const override;
	User* clone() const override;
};