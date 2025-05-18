#pragma once
#include "User.h"
#include "Admin.h"
#include "Teacher.h"
#include "Student.h"
#include <exception>

class UserFactory {
public:
	UserFactory() = delete;

	static User* createUser(UserType type);
	static User* createUser(UserType type, const String& firstName, const String& lastName, const String& password);
};